#ifndef _CHARACTER_TABLE_H_
#define _CHARACTER_TABLE_H_

#include <map>
#include "character_category.h"


class character_table {
public:

    character_table();

    const inline character_category operator[](char value) const;

private:

    character_table(character_table const &);

    character_table& operator = (character_table);

private:
    std::map<char, character_category > map_;
};

#endif
