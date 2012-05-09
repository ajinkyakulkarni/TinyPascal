/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "scanner.h"
#include "character_table.h"
#include "file_buffer.h"
#include <boost/noncopyable.hpp>

using std::string;
using std::shared_ptr;

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

class scanner_impl : boost::noncopyable {
public:
    scanner_impl(string const & filename)
    : filename_(filename), buffer_(filename, 10), current_(0), line_(1) {
        processor_ = shared_ptr<token_processor>(new start_processor(*this));
    }

    bool empty() {
        return !(buffer_.canPeek());
    }

    char current() {
        return current_;
    }

    char peek() {
        return buffer_.peek();
    }

    void read() {
        current_ = buffer_.character();
    }

    void undo() {
        buffer_.rewind();
    }

    bool canPeek() {
        return buffer_.canPeek();
    }

    character_category peekType() {
        return table_[buffer_.peek()];
    }

    character_category currentType() {
        return table_[current()];
    }

    shared_ptr<token> getNextToken() {

        if (this->empty())
            return shared_ptr<token>(new token(END_OF_FILE));

        while (true) {

            read();
            processor_->configure();

            shared_ptr<token> result = processor_->processToken();

            if (!result->isNoToken())
                return result;
        }

        return shared_ptr<token>(new token(END_OF_FILE));
    }

    void assignIndentifierProcessor() {
        processor_ = shared_ptr<token_processor>(new identifier_processor(*this));
    }

    void assignNumericProcessor() {
        processor_ = shared_ptr<token_processor>(new numeric_processor(*this));
    }

    void assignWhitespaceProcessor() {
        processor_ = shared_ptr<token_processor>(new whitespace_processor(*this));
    }

    void assignStringProcessor() {
        processor_ = shared_ptr<token_processor>(new identifier_processor(*this));
    }

    void assignNewLineProcessor() {
        processor_ = shared_ptr<token_processor>(new identifier_processor(*this));
    }

    void assignTabProcessor() {
        processor_ = shared_ptr<token_processor>(new identifier_processor(*this));
    }

    void assignSpecialCharacterProcessor() {
        processor_ = shared_ptr<token_processor>(new special_character_processor(*this));
    }

private:
    string filename_;
    file_buffer buffer_;
    character_table table_;
    shared_ptr<token_processor> processor_;
    char current_;
    int line_;
};

scanner::scanner(std::string const & filename) {
    impl_ = new scanner_impl(filename);
}

scanner::~scanner() {
    delete impl_;
}

shared_ptr<token> scanner::getNextToken() {
    return impl_->getNextToken();
}

token_processor::token_processor(scanner_impl& scanner) : scanner_(scanner) {

}

token_processor::~token_processor() {

};

void token_processor::configure() {
    switch (scanner_.currentType()) {
        case LETTER:
            scanner_.assignIndentifierProcessor();
            break;
        case DIGIT:
            scanner_.assignNumericProcessor();
            break;
        case SPACE:
            scanner_.assignWhitespaceProcessor();
            break;
        case QUOTE:
            scanner_.assignStringProcessor();
            break;
        case NEWLINE:
            scanner_.assignNewLineProcessor();
            break;
        case TAB:
            scanner_.assignTabProcessor();
            break;
        default:
            scanner_.assignSpecialCharacterProcessor();
    }
}

start_processor::start_processor(scanner_impl& scanner) : token_processor(scanner) {

}

shared_ptr<token> start_processor::processToken() {
    return shared_ptr<token>(new token(NO_TOKEN, ""));
}

identifier_processor::identifier_processor(scanner_impl& scanner) : token_processor(scanner) {

}

shared_ptr<token> identifier_processor::processToken() {
    string currentTokenText("");
    currentTokenText.push_back(scanner_.current());

    while (scanner_.canPeek() && (scanner_.peekType() == DIGIT || scanner_.peekType() == LETTER)) {
        scanner_.read();
        currentTokenText.push_back(scanner_.current());
    }

    return shared_ptr<token>(new token(IDENTIFIER, currentTokenText));
}

numeric_processor::numeric_processor(scanner_impl& scanner) : token_processor(scanner) {

}

shared_ptr<token> numeric_processor::processToken() {
    string currentTokenText;
    currentTokenText.push_back(scanner_.current());

    while (scanner_.canPeek() && (scanner_.peekType() == DIGIT)) {
        scanner_.read();
        currentTokenText.push_back(scanner_.current());
    }

    if (scanner_.canPeek() && scanner_.peekType() == DOT) {
        scanner_.read();
        currentTokenText.push_back(scanner_.current());
        if (scanner_.canPeek() && scanner_.peekType() == DIGIT) {
            while (scanner_.canPeek() && scanner_.peekType() == DIGIT) {
                scanner_.read();
                currentTokenText.push_back(scanner_.current());
            }
        } else {
            shared_ptr<token> result(new token(ERROR, currentTokenText));
            scanner_.undo();
            return result;
        }
    }

    return shared_ptr<token>(new token(IDENTIFIER, currentTokenText));
}

special_character_processor::special_character_processor(scanner_impl& scanner) : token_processor(scanner) {

}

shared_ptr<token> special_character_processor::processToken() {

    string currentTokenText;
    currentTokenText.push_back(scanner_.current());

    switch (scanner_.current()) {
        case '^':
            return shared_ptr<token>(new token(UPARROW, currentTokenText));
        case '*':
            return shared_ptr<token>(new token(STAR, currentTokenText));
        case '(':
            return shared_ptr<token>(new token(LPAREN, currentTokenText));
        case ')':
            return shared_ptr<token>(new token(RPAREN, currentTokenText));
        case '-':
            return shared_ptr<token>(new token(MINUS, currentTokenText));
        case '+':
            return shared_ptr<token>(new token(PLUS, currentTokenText));
        case '=':
            return shared_ptr<token>(new token(EQUAL, currentTokenText));
        case '[':
            return shared_ptr<token>(new token(LBRACKET, currentTokenText));
        case ']':
            return shared_ptr<token>(new token(RBRACKET, currentTokenText));
        case ';':
            return shared_ptr<token>(new token(SEMICOLON, currentTokenText));
        case ',':
            return shared_ptr<token>(new token(COMMA, currentTokenText));
        case '/':
            return shared_ptr<token>(new token(SLASH, currentTokenText));
        case ':':
            if (scanner_.canPeek() && scanner_.peek() == '=') {
                scanner_.read();
                currentTokenText.push_back(scanner_.current());

                return shared_ptr<token>(new token(COLONEQUAL, currentTokenText));
            } else {
                return shared_ptr<token>(new token(COLON, currentTokenText));
            }
        case '<':
            if (scanner_.canPeek() && scanner_.peek() == '=') {
                scanner_.read();
                currentTokenText.push_back(scanner_.current());

                return shared_ptr<token>(new token(LE, currentTokenText));
            } else {
                return shared_ptr<token>(new token(LT, currentTokenText));
            }
        case '>':
            if (scanner_.canPeek() && scanner_.peek() == '=') {
                scanner_.read();
                currentTokenText.push_back(scanner_.current());

                return shared_ptr<token>(new token(GE, currentTokenText));
            } else {
                return shared_ptr<token>(new token(GT, currentTokenText));
            }
        case '.':
            if (scanner_.canPeek() && scanner_.peek() == '.') {
                scanner_.read();
                currentTokenText.push_back(scanner_.current());

                return shared_ptr<token>(new token(DOTDOT, currentTokenText));
            } else {
                return shared_ptr<token>(new token(PERIOD, currentTokenText));
            }
        default:
            return shared_ptr<token>(new token(ERROR, currentTokenText));

    }
}

whitespace_processor::whitespace_processor(scanner_impl& scanner) : token_processor(scanner) {

}

shared_ptr<token> whitespace_processor::processToken() {
    string currentTokenText;
    currentTokenText.push_back(scanner_.current());

    while (scanner_.canPeek() && scanner_.peekType() == SPACE) {
        scanner_.read();
        currentTokenText.push_back(scanner_.current());
    }

    return shared_ptr<token>(new token(NO_TOKEN, currentTokenText));
}


