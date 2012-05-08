#include "scanner.h"
#include "character_table.h"
#include "file_buffer.h"

using std::string;
using std::shared_ptr;

class scanner_impl {
public:
    scanner_impl(string const & filename) : filename_(filename), buffer_(filename, 10) {

    }

    shared_ptr<token> getNextToken() {
        while (moreCharactersAvailable()) {

            extractCharacter();

            switch (getCurrentCharCategory()) {
                case LETTER:
                    return processWord();
                case DIGIT:
                    return processNumber();
                case SPACE:
                    processSpace();
                    break;
                case QUOTE:
                    return processString();
                case NEWLINE:
                    currentCharacter_ = ' ';
                    processSpace();
                    incrementLine();
                    break;
                case TAB:
                    convertToSpace();
                    processSpace();
                    break;
                default:
                    return processSpecial();
            }
        }
        return shared_ptr<token>(new token(END_OF_FILE));
    }

private:


    inline bool moreCharactersAvailable() {
        return static_cast<bool>(buffer_.canPeek());
    }

    inline const char currentCharacter() {
        return currentCharacter_;
    }

    inline const char currentPeekCharacter() {
        return buffer_.peek();
    }

    const inline character_category getCurrentCharCategory() {
        table_[currentCharacter()];
    }

    const inline character_category getPeekCharCategory() {
        return table_[currentPeekCharacter()];
    }

    inline void extractCharacter() {
        currentCharacter_ = buffer_.getCharacter();
    }

    inline void pushTokenText() {
        currentTokenText_ += currentCharacter_;
    }

    inline void incrementLine() {
        currentLine_++;
    }

    inline void extractAndPush() {
        extractCharacter();
        pushTokenText();
    }

    void returnCurrentCharacter() {
        buffer_.returnCharacter(currentCharacter_);
    }

    shared_ptr<token> getTokenAndFlush(token_type type) {
        shared_ptr<token> result(new token(type, currentTokenText_));
        currentTokenText_ = "";
        return result;
    }

    void processSpace() {
        while (getPeekCharCategory() == SPACE) {
            currentCharacter_ = buffer_.getCharacter();
        }
    }

    shared_ptr<token> processString() {
        currentTokenText_ += currentCharacter_;
        currentCharacter_ = buffer_.peek();
        while (currentCharacter_ != '\'' && currentCharacter_) {
            extractAndPush();
        }

        return getTokenAndFlush(STRING);
    }

    shared_ptr<token> processNumber() {
        pushTokenText();

        while (getPeekCharCategory() == DIGIT) {
            extractAndPush();
        }

        if (getPeekCharCategory() == DOT) {
            extractAndPush();
            if (getPeekCharCategory() == DIGIT) {
                while (getPeekCharCategory() == DIGIT) {
                    extractAndPush();
                }
            } else {
                returnCurrentCharacter();
                return getTokenAndFlush(ERROR);
            }
        }

        return getTokenAndFlush(NUMBER);
    }

    shared_ptr<token> processWord() {
        pushTokenText();
        while (getPeekCharCategory() == DIGIT || getPeekCharCategory() == LETTER) {
            extractAndPush();
        }

        return getTokenAndFlush(IDENTIFIER);
    }

    shared_ptr<token> processSpecial() {
        pushTokenText();
        switch (currentCharacter()) {
            case '^':
                return getTokenAndFlush(UPARROW);
            case '*':
                return getTokenAndFlush(STAR);
            case '(':
                return getTokenAndFlush(LPAREN);
            case ')':
                return getTokenAndFlush(RPAREN);
            case '-':
                return getTokenAndFlush(MINUS);
            case '+':
                return getTokenAndFlush(PLUS);
            case '=':
                return getTokenAndFlush(EQUAL);
            case '[':
                return getTokenAndFlush(LBRACKET);
            case ']':
                return getTokenAndFlush(RBRACKET);
            case ';':
                return getTokenAndFlush(SEMICOLON);
            case ',':
                return getTokenAndFlush(COMMA);
            case '/':
                return getTokenAndFlush(SLASH);
            case ':':
                if (buffer_.canPeek() && buffer_.peek() == '=') {
                    extractAndPush();
                    return getTokenAndFlush(COLONEQUAL);
                } else {
                    return getTokenAndFlush(COLON);
                }
            case '<':
                if (buffer_.canPeek() && buffer_.peek() == '=') {
                    extractAndPush();
                    return getTokenAndFlush(LE);
                } else {
                    return getTokenAndFlush(LT);
                }
            case '>':
                if (buffer_.canPeek() && buffer_.peek() == '=') {
                    extractAndPush();
                    return getTokenAndFlush(GE);
                } else {
                    return getTokenAndFlush(GT);
                }
            case '.':
                if (buffer_.canPeek() && buffer_.peek() == '.') {
                    extractAndPush();
                    return getTokenAndFlush(DOTDOT);
                } else {
                    return getTokenAndFlush(PERIOD);
                }
            default:
                return getTokenAndFlush(ERROR);

        }
    }


private:
    string filename_;
    file_buffer buffer_;
    character_table table_;
    int currentLine_;
    char currentCharacter_;
    string currentTokenText_;


    void convertToSpace() {
        currentCharacter_ = ' ';
    }

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


