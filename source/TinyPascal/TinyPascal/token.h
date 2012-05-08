#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>
#include "token_type.h"

class token {
    public:
    token(token_type const & type);
    token(token_type const & type, std::string const & text);
    token(token const & other);
    token& operator = (token const & other);
    bool validToken() const;
    token_type getType() const;
    std::string getText() const;
    std::string getTypeAsString() const;
    private:
    token_type type_;
    std::string text_;
};

#endif
