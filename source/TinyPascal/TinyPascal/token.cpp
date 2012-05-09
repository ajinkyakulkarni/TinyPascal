/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "token.h"

using std::string;

token::token(token_type const & type) : type_(type) {
}

token::token(token_type const & type, string const & text) : type_(type), text_(text) {
}

token::token(token const & other) : type_(other.type_), text_(other.text_) {
}

token& token::operator = (token const & other) {
    if (this == &other) return *this;

    this->text_ = other.text_;
    this->type_ = other.type_;

    return *this;

}

bool token::eof() const {
    return ((type_ == END_OF_FILE));
}

bool token::isNoToken() const {
    return (type_ == NO_TOKEN);
}

bool token::isError() const {
    return (type_ == ERROR);
}

token_type token::getType() const {
    return type_;
}

std::string token::getText() const {
    return text_;
};

std::string token::getTypeAsString() const {
    switch (getType()) {
        case NO_TOKEN:
            return "No token";
        case END_OF_FILE:
            return "End Of File";
        case IDENTIFIER:
            return "Identifier";
        case NUMBER:
            return "Number";
        case STRING:
            return "String";
        case UPARROW:
            return "Up Arrow";
        case STAR:
            return "Star";
        case LPAREN:
            return "Left Parenthesis";
        case RPAREN:
            return "Right Parenthesis";
        case MINUS:
            return "Minus";
        case PLUS:
            return "Plus";
        case EQUAL:
            return "Equal";
        case LBRACKET:
            return "Left Bracket";
        case RBRACKET:
            return "Right Bracket";
        case COLON:
            return "Colon";
        case SEMICOLON:
            return "Semi Colon";
        case LT:
            return "Less Than";
        case GT:
            return "Greater Than";
        case COMMA:
            return "Comma";
        case PERIOD:
            return "Period";
        case SLASH:
            return "Slash";
        case COLONEQUAL:
            return "Colon Equal";
        case LE:
            return "Less Equal";
        case GE:
            return "Greater Equal";
        case NE:
            return "Not Equal";
        case DOTDOT:
            return "Dot Dot";
        case ERROR:
            return "Error";
        case AND:
            return "And";
        case ARRAY:
            return "Array";
        case BEGIN:
            return "Begin";
        case CASE:
            return "Case";
        case CONST:
            return "Const";
        case DIV:
            return "Div";
        case DO:
            return "Do";
        case DOWNTO:
            return "Down To";
        case ELSE:
            return "Else";
        case END:
            return "End";
        case FFILE:
            return "FFile";
        case FOR:
            return "For";
        case FUNCTION:
            return "Function";
        case GOTO:
            return "Goto";
        case IF:
            return "If";
        case IN:
            return "In";
        case LABEL:
            return "Label";
        case MOD:
            return "Mod";
        case NIL:
            return "Nil";
        case NOT:
            return "Not";
        case OF:
            return "Of";
        case OR:
            return "Or";
        case PACKED:
            return "Packed";
        case PROCEDURE:
            return "Procedure";
        case PROGRAM:
            return "Program";
        case RECORD:
            return "Record";
        case REPEAT:
            return "Repeat";
        case SET:
            return "Set";
        case THEN:
            return "Then";
        case TO:
            return "To";
        case TYPE:
            return "Type";
        case UNTIL:
            return "Until";
        case VAR:
            return "Variable";
        case WHILE:
            return "While";
        case WITH:
            return "With";
        default:
            return "Error";
    }
}