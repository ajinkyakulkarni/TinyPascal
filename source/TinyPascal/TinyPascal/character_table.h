#ifndef _CHAR_TABLE_H_
#define _CHAR_TABLE_H_

#include <map>
#include "character_category.h"
#include <boost/noncopyable.hpp>

class character_table : boost::noncopyable{
public:

    character_table();
    character_category operator[](char value);

private:
    std::map<char, character_category > map_;
};

#endif
