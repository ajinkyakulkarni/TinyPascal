/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "reserved_words_table.h"
#include <algorithm>

reserved_words_table::reserved_words_table() {
    words["do"] = DO;
    words["if"] = IF;
    words["in"] = IN;
    words["of"] = OF;
    words["or"] = OR;
    words["to"] = TO;
    words["and"] = AND;
    words["div"] = DIV;
    words["end"] = END;
    words["for"] = FOR;
    words["mod"] = MOD;
    words["nill"] = NIL;
    words["not"] = NOT;
    words["set"] = SET;
    words["var"] = VAR;
    words["case"] = CASE;
    words["else"] = ELSE;
    words["file"] = FFILE;
    words["goto"] = GOTO;
    words["then"] = THEN;
    words["type"] = TYPE;
    words["with"] = WITH;
    words["array"] = ARRAY;
    words["begin"] = BEGIN;
    words["const"] = CONST;
    words["label"] = LABEL;
    words["until"] = UNTIL;
    words["while"] = WHILE;
    words["downto"] = DOWNTO;
    words["packed"] = PACKED;
    words["record"] = RECORD;
    words["repeat"] = REPEAT;
    words["program"] = PROGRAM;
    words["function"] = FUNCTION;
    words["procedure"] = PROCEDURE;
}

struct word_to_lower_functor {
    void operator()(char& c) {
        c = tolower(c);
    }
};

token_type reserved_words_table::operator[] (string const & word) const {
    word_to_lower_functor f;

    string temp = word;
    std::for_each(temp.begin(), temp.end(), f);

    map<string, token_type>::const_iterator result = words.find(temp);
    if (result == words.end())
        return NO_TOKEN;

    return result->second;
}
