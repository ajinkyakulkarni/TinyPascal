/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "reserved_words_table.h"
#include <algorithm>

namespace pascal {
    namespace frontend {
        reserved_words_table::reserved_words_table() {
            words["do"] = reserved_words::DO;
            words["if"] = reserved_words::IF;
            words["in"] = reserved_words::IN;
            words["of"] = reserved_words::OF;
            words["or"] = reserved_words::OR;
            words["to"] = reserved_words::TO;
            words["and"] = reserved_words::AND;
            words["div"] = reserved_words::DIV;
            words["end"] = reserved_words::END;
            words["for"] = reserved_words::FOR;
            words["mod"] = reserved_words::MOD;
            words["nill"] = reserved_words::NIL;
            words["not"] = reserved_words::NOT;
            words["set"] = reserved_words::SET;
            words["var"] = reserved_words::VAR;
            words["case"] = reserved_words::CASE;
            words["else"] = reserved_words::ELSE;
            words["file"] = reserved_words::FILE;
            words["goto"] = reserved_words::GOTO;
            words["then"] = reserved_words::THEN;
            words["type"] = reserved_words::TYPE;
            words["with"] = reserved_words::WITH;
            words["array"] = reserved_words::ARRAY;
            words["begin"] = reserved_words::BEGIN;
            words["const"] = reserved_words::CONST;
            words["label"] = reserved_words::LABEL;
            words["until"] = reserved_words::UNTIL;
            words["while"] = reserved_words::WHILE;
            words["downto"] = reserved_words::DOWNTO;
            words["packed"] = reserved_words::PACKED;
            words["record"] = reserved_words::RECORD;
            words["repeat"] = reserved_words::REPEAT;
            words["program"] = reserved_words::PROGRAM;
            words["function"] = reserved_words::FUNCTION;
            words["procedure"] = reserved_words::PROCEDURE;
        }

        struct word_to_lower_functor {
            void operator()(char& c) {
                c = tolower(c);
            }
        };

        reserved_words::reserved_word_type reserved_words_table::operator[] (string const & word) const {
            word_to_lower_functor f;

            string temp = word;
            std::for_each(temp.begin(), temp.end(), f);

            map<string, reserved_words::reserved_word_type>::const_iterator result = words.find(temp);
            if (result == words.end())
                return reserved_words::NOT_RESERVED_WORD;

            return result->second;
        }
    }
    
}