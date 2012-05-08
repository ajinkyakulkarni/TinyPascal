#include "token.h"

using std::string;

token::token(token_type const & type) : type_(type)
{
}

token::token(token_type const & type, string const & text) : type_(type), text_(text)
{
}

token::token(token const & other) : type_(other.type_), text_(other.text_)
{
}

token& token::operator = (token const & other)
{
    if (this == &other) return *this;

    this->text_ = other.text_;
    this->type_ = other.type_;

    return *this;

}

bool token::validToken() const
{
    return !((type_ == END_OF_FILE) || (type_ == ERROR));
}

token_type token::getType() const
{
    return type_;
}

std::string token::getText() const
{
    return text_;
};

std::string token::getTypeAsString() const{
    switch (getType())
    {
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