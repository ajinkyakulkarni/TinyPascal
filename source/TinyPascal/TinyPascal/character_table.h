#ifndef _CHAR_TABLE_H_
#define _CHAR_TABLE_H_

#include <map>
#include "character_category.h"

class character_table {
public:

    character_table();
    character_category operator[](char value);

private:

    character_table(character_table const &);
    character_table& operator = (character_table);
    std::map<char, character_category > map_;
};

#endif
