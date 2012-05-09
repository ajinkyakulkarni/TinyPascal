#ifndef _SCANNER_
#define _SCANNER_

#include "token.h"
#include <string>
#include <memory>
#include <boost/noncopyable.hpp>

class scanner_impl;

class scanner : boost::noncopyable{
public:

    scanner(std::string const & filename_);
    ~scanner();

    std::shared_ptr<token> getNextToken();

private:
    scanner_impl *impl_;
};

#endif