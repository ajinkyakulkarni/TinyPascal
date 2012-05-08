#include "character_table.h"

character_table::character_table() {
    for (int i = 0; i <= 255; i++) {
        map_[(char) i] = SPECIAL;
    }

    for (int i = 'a'; i <= 'z'; i++) {
        map_[(char) i] = LETTER;
    }

    for (int i = 'A'; i <= 'Z'; i++) {
        map_[(char) i] = LETTER;
    }

    for (int i = '0'; i <= '9'; i++) {
        map_[(char) i] = DIGIT;
    }

    map_['.'] = DOT;
    map_[' '] = SPACE;
    map_['\''] = QUOTE;
    map_['\n'] = NEWLINE;
    map_['\t'] = TAB;
}

const inline character_category character_table::operator[](char value) const {
    character_category category = map_.at(value);
    return category;
}