/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <boost/noncopyable.hpp>
#include <sstream>
#include "scanner.h"
#include "character_table.h"
#include "file_buffer.h"
#include "reserved_words_table.h"
#include "pascal_exceptions.h"
#include "identifier_token.h"
#include "special_character_token.h"
#include "string_literal_token.h"
#include "no_token.h"
#include "integral_literal_token.h"
#include "real_literal_token.h"
#include "eof_token.h"
#include "reserved_word_token.h"
#include "invalid_real_number_exception.h"
#include "reserved_word_to_token_converter.h"

using std::string;
using std::shared_ptr;

namespace pascal {
    namespace frontend {
        class scanner_impl;

        class token_processor : boost::noncopyable {
        public:
            token_processor(scanner_impl& scanner);
            virtual ~token_processor() = 0;

            virtual shared_ptr<token> processToken() = 0;
            void configure();

        protected:
            scanner_impl& scanner_;
        };

        class start_processor : public token_processor {
        public:
            start_processor(scanner_impl& scanner);
            shared_ptr<token> processToken();
        };

        class identifier_processor : public token_processor {
        public:
            identifier_processor(scanner_impl& scanner);
            shared_ptr<token> processToken();
        };

        class numeric_processor : public token_processor {
        public:
            numeric_processor(scanner_impl& scanner);
            shared_ptr<token> processToken();
        };

        class special_character_processor : public token_processor {
        public:
            special_character_processor(scanner_impl& scanner);
            shared_ptr<token> processToken();
        };

        class whitespace_processor : public token_processor {
        public:
            whitespace_processor(scanner_impl& scanner);
            shared_ptr<token> processToken();
        };

        class string_processor : public token_processor {
        public:
            string_processor(scanner_impl& scanner);
            shared_ptr<token> processToken();
        };

        class scanner_impl : boost::noncopyable {
        public:
            scanner_impl(string const & filename)
            : filename_(filename), buffer_(filename, 10), current_(0), line_(1) {
                processor_ = shared_ptr<token_processor>(new start_processor(*this));
				token_ = shared_ptr<token>(new eof_token("",-1));
            }

            bool empty() const {
                return !(buffer_.canPeek());
            }

            bool eof() const {
                return buffer_.eof();
            }

            char current() const {
                return current_;
            }

            char peek() const {
                return buffer_.peek();
            }

            int lineNumber() const {
                return line_;
            }

            void read() {
                current_ = buffer_.character();

                if (current_ == '\n') { // strip newlines
                    line_++;
                    current_ = ' ';
                    return;
                }

                if (current_ == '\t') { // strip tabs
                    current_ = ' ';
                    return;
                }

                if (current_ == '{') { // strip comments
                    bool matched = false;
                    while (canPeek()) {
                        current_ = buffer_.character();
                        if (current_ == '}') {
                            matched = true;
                            break;
                        }
                    }

                    if (!matched) {
                        string error("Unable to match the terminating comment brace on line: " + lineNumber());
                        throw unexpected_token_exception(error.c_str());
                    }

                    current_ = ' ';
                    return;
                }
            }

            void undo() {
                buffer_.rewind();
            }

            bool canPeek() const{
                return buffer_.canPeek();
            }

            character::character_category peekType() {
                return character_table_[buffer_.peek()];
            }

            character::character_category currentType() {
                return character_table_[current()];
            }

            reserved_words::reserved_word_type getReservedWordToken(string const& text) {
                return reserved_words_table_[text];
            }

            void consume() 
			{

                if (this->empty()){
                    token_ = shared_ptr<token>(new eof_token("", lineNumber()));
					return;
				}

                while (true) 
				{
                    read();

                    if (this->eof()){
                        token_ =  shared_ptr<token>(new eof_token("", lineNumber()));
						return;
					}

                    processor_->configure();

                    shared_ptr<token> result = processor_->processToken();
                    if (result->getType() != tokens::NO_TOKEN){
                        token_ =  result;
						return;
					}
                }

                token_ = shared_ptr<token>(new no_token("", lineNumber()));
            }

			std::shared_ptr<token> currentToken() const{
				return token_;
			}

            void assignIdentifierProcessor() {
                processor_ = shared_ptr<token_processor>(new identifier_processor(*this));
            }

            void assignNumericProcessor() {
                processor_ = shared_ptr<token_processor>(new numeric_processor(*this));
            }

            void assignWhitespaceProcessor() {
                processor_ = shared_ptr<token_processor>(new whitespace_processor(*this));
            }

            void assignStringProcessor() {
                processor_ = shared_ptr<token_processor>(new string_processor(*this));
            }

            void assignSpecialCharacterProcessor() {
                processor_ = shared_ptr<token_processor>(new special_character_processor(*this));
            }

        private:
            string filename_;
            file_buffer buffer_;
            character_table character_table_;
            reserved_words_table reserved_words_table_;
            shared_ptr<token_processor> processor_;
            char current_;
            int line_;
			shared_ptr<token> token_;
        };

        scanner::scanner(std::string const & filename) {
            impl_ = new scanner_impl(filename);
        }

        scanner::~scanner() {
            delete impl_;
        }

        std::shared_ptr<token> scanner::current() const {
			return impl_->currentToken();
        }

		void scanner::consume(){
			impl_->consume();
		}

        token_processor::token_processor(scanner_impl& scanner) : scanner_(scanner) {

        }

        token_processor::~token_processor() {

        };

        void token_processor::configure() {
            switch (scanner_.currentType()) {
                case character::LETTER:
                    scanner_.assignIdentifierProcessor();
                    break;
                case character::DIGIT:
                    scanner_.assignNumericProcessor();
                    break;
                case character::SPACE:
                    scanner_.assignWhitespaceProcessor();
                    break;
                case character::QUOTE:
                    scanner_.assignStringProcessor();
                    break;
                default:
                    scanner_.assignSpecialCharacterProcessor();
            }
        }

        start_processor::start_processor(scanner_impl& scanner) : token_processor(scanner) {

        }

        shared_ptr<token> start_processor::processToken() {
            return shared_ptr<token>(new no_token("", scanner_.lineNumber()));
        }

        identifier_processor::identifier_processor(scanner_impl& scanner) : token_processor(scanner) {

        }

        shared_ptr<token> identifier_processor::processToken() {
            string currentTokenText("");
            currentTokenText.push_back(scanner_.current());

            while (scanner_.canPeek() && (scanner_.peekType() == character::DIGIT || scanner_.peekType() == character::LETTER)) {
                scanner_.read();
                currentTokenText.push_back(scanner_.current());
            }

            reserved_words::reserved_word_type reserved = scanner_.getReservedWordToken(currentTokenText);
            if (reserved != reserved_words::NOT_RESERVED_WORD)
			{
				reserved_word_to_token_converter converter;
				tokens::token_type type = converter[reserved];
                return shared_ptr<token>(new reserved_word_token(type, currentTokenText, scanner_.lineNumber()));
			}

            return shared_ptr<token>(new identifier_token(currentTokenText, scanner_.lineNumber()));
        }

        numeric_processor::numeric_processor(scanner_impl& scanner) : token_processor(scanner) {

        }

        shared_ptr<token> numeric_processor::processToken() {
            string currentTokenText("");
            currentTokenText.push_back(scanner_.current());

            while (scanner_.canPeek() && (scanner_.peekType() == character::DIGIT)) {
                scanner_.read();
                currentTokenText.push_back(scanner_.current());
            }

            if (scanner_.canPeek() && scanner_.peekType() == character::DOT) {
                scanner_.read();
                currentTokenText.push_back(scanner_.current());
                if (scanner_.canPeek() && scanner_.peekType() == character::DIGIT) {
                    while (scanner_.canPeek() && scanner_.peekType() == character::DIGIT) {
                        scanner_.read();
                        currentTokenText.push_back(scanner_.current());
                    }
                    if (scanner_.canPeek() && (scanner_.peekType() ==character:: DOT)) {
                        currentTokenText.push_back(scanner_.peek());
                        string message("Invalid real number: " + currentTokenText);
                        message.append(" on line ");
                        std::ostringstream osstream;
                        osstream << scanner_.lineNumber();
                        message.append(osstream.str());
                        throw invalid_real_number_exception(message);
                    }
                } else {
                    currentTokenText.push_back(scanner_.peek());
                    string message("Invalid real number: " + currentTokenText);
                    message.append(" on line ");
                    std::ostringstream osstream;
                    osstream << scanner_.lineNumber();
                    message.append(osstream.str());
                    scanner_.undo();
                    throw invalid_real_number_exception(message);
                }

                return shared_ptr<token>(new real_literal_token(currentTokenText, scanner_.lineNumber()));

            } else {
                return shared_ptr<token>(new integer_literal_token(currentTokenText, scanner_.lineNumber()));
            }
        }

        special_character_processor::special_character_processor(scanner_impl& scanner) : token_processor(scanner) {

        }

        shared_ptr<token> special_character_processor::processToken() {

            string currentTokenText("");
            currentTokenText.push_back(scanner_.current());

            switch (scanner_.current()) {
                case '^':
                    return shared_ptr<token>(new special_character_token(tokens::UP_ARROW, currentTokenText, scanner_.lineNumber()));
                case '*':
                    return shared_ptr<token>(new special_character_token(tokens::STAR, currentTokenText, scanner_.lineNumber()));
                case '(':
                    return shared_ptr<token>(new special_character_token(tokens::LEFT_PAREN, currentTokenText, scanner_.lineNumber()));
                case ')':
                    return shared_ptr<token>(new special_character_token(tokens::RIGHT_PAREN, currentTokenText, scanner_.lineNumber()));
                case '-':
                    return shared_ptr<token>(new special_character_token(tokens::MINUS, currentTokenText, scanner_.lineNumber()));
                case '+':
                    return shared_ptr<token>(new special_character_token(tokens::PLUS, currentTokenText, scanner_.lineNumber()));
                case '=':
                    return shared_ptr<token>(new special_character_token(tokens::EQUALS, currentTokenText, scanner_.lineNumber()));
                case '[':
                    return shared_ptr<token>(new special_character_token(tokens::LEFT_BRACKET, currentTokenText, scanner_.lineNumber()));
                case ']':
                    return shared_ptr<token>(new special_character_token(tokens::RIGHT_BRACKET, currentTokenText, scanner_.lineNumber()));
                case ';':
                    return shared_ptr<token>(new special_character_token(tokens::SEMICOLON, currentTokenText, scanner_.lineNumber()));
                case ',':
                    return shared_ptr<token>(new special_character_token(tokens::COMMA, currentTokenText, scanner_.lineNumber()));
                case '/':
                    return shared_ptr<token>(new special_character_token(tokens::SLASH, currentTokenText, scanner_.lineNumber()));
                case ':':
                    if (scanner_.canPeek() && scanner_.peek() == '=') {
                        scanner_.read();
                        currentTokenText.push_back(scanner_.current());

                        return shared_ptr<token>(new special_character_token(tokens::COLON_EQUALS, currentTokenText, scanner_.lineNumber()));
                    } else {
                        return shared_ptr<token>(new special_character_token(tokens::COLON, currentTokenText, scanner_.lineNumber()));
                    }
                case '<':
                    if (scanner_.canPeek() && scanner_.peek() == '=') {
                        scanner_.read();
                        currentTokenText.push_back(scanner_.current());

                        return shared_ptr<token>(new special_character_token(tokens::LESS_EQUALS, currentTokenText, scanner_.lineNumber()));
                    } else {
                        return shared_ptr<token>(new special_character_token(tokens::LESS_THAN, currentTokenText, scanner_.lineNumber()));
                    }
                case '>':
                    if (scanner_.canPeek() && scanner_.peek() == '=') {
                        scanner_.read();
                        currentTokenText.push_back(scanner_.current());

                        return shared_ptr<token>(new special_character_token(tokens::GREATER_EQUALS, currentTokenText, scanner_.lineNumber()));
                    } else {
                        return shared_ptr<token>(new special_character_token(tokens::GREATER_THAN, currentTokenText, scanner_.lineNumber()));
                    }
                case '.':
                    if (scanner_.canPeek() && scanner_.peek() == '.') {
                        scanner_.read();
                        currentTokenText.push_back(scanner_.current());

                        return shared_ptr<token>(new special_character_token(tokens::DOT_DOT, currentTokenText, scanner_.lineNumber()));
                    } else {
                        return shared_ptr<token>(new special_character_token(tokens::DOT, currentTokenText, scanner_.lineNumber()));
                    }
                default:
                    string message("Unrecongised token: " + currentTokenText);
                    message.append(" on line ");
                    std::ostringstream osstream;
                    osstream << scanner_.lineNumber();
                    message.append(osstream.str());
                    throw unexpected_token_exception(message);
            }
        }

        whitespace_processor::whitespace_processor(scanner_impl& scanner) : token_processor(scanner) {

        }

        shared_ptr<token> whitespace_processor::processToken() {
            string currentTokenText("");
            currentTokenText.push_back(scanner_.current());

            while (scanner_.canPeek() && scanner_.peekType() == character::SPACE) {
                scanner_.read();
                currentTokenText.push_back(scanner_.current());
            }

            return shared_ptr<token>(new no_token(currentTokenText, scanner_.lineNumber()));
        }

        string_processor::string_processor(scanner_impl& scanner) : token_processor(scanner) {

        }

        shared_ptr<token> string_processor::processToken() {
            string currentTokenText("");

            while (scanner_.canPeek()) {

                scanner_.read();
                if (scanner_.currentType() == character::QUOTE) {
                    if (scanner_.peekType() != character::QUOTE)
                        return shared_ptr<token>(new string_literal_token(currentTokenText, scanner_.lineNumber()));
                    currentTokenText.push_back(scanner_.current());
                }
                currentTokenText.push_back(scanner_.current());
            }

            throw unclosed_quote_literal_exception("Unclosed quote literal on line: " + scanner_.lineNumber());
        }
    }
}