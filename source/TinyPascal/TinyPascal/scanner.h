#ifndef _SCANNER_
#define _SCANNER_

#include "token.h"
#include <string>
#include <memory>

class scanner_impl;


class scanner {
public:

    scanner(std::string const & filename_);
    ~scanner();

    std::shared_ptr<token> getNextToken();

private:

    scanner(scanner const & other);
    scanner& operator = (scanner const & other);

    scanner_impl *impl_;

};

#endif