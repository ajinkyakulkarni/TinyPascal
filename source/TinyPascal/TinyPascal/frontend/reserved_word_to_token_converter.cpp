/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "reserved_word_to_token_converter.h"

namespace pascal {
	namespace frontend {
		tokens::token_type reserved_word_to_token_converter::operator[](reserved_words::reserved_word_type word){
			switch(word){
				case reserved_words::DO: 
					return tokens::DO;
				case reserved_words::IF: 
					return tokens::IF;
				case reserved_words::IN: 
					return tokens::IN;
				case reserved_words::OF: 
					return tokens::OF;
				case reserved_words::OR: 
					return tokens::OR;
				case reserved_words::TO: 
					return tokens::TO;
				case reserved_words::AND: 
					return tokens::AND;
				case reserved_words::DIV: 
					return tokens::DIV;
				case reserved_words::END: 
					return tokens::END;
				case reserved_words::FOR: 
					return tokens::FOR;
				case reserved_words::MOD: 
					return tokens::MOD;
				case reserved_words::NIL: 
					return tokens::NIL;
				case reserved_words::NOT: 
					return tokens::NOT;
				case reserved_words::SET: 
					return tokens::SET;
				case reserved_words::VAR: 
					return tokens::VAR;
				case reserved_words::CASE: 
					return tokens::CASE;
				case reserved_words::ELSE: 
					return tokens::ELSE;
				case reserved_words::FILE: 
					return tokens::FILE;
				case reserved_words::GOTO: 
					return tokens::GOTO;
				case reserved_words::THEN: 
					return tokens::THEN;
				case reserved_words::TYPE: 
					return tokens::TYPE;
				case reserved_words::WITH: 
					return tokens::WITH;
				case reserved_words::ARRAY: 
					return tokens::ARRAY;
				case reserved_words::BEGIN: 
					return tokens::BEGIN;
				case reserved_words::CONST: 
					return tokens::CONST;
				case reserved_words::LABEL: 
					return tokens::LABEL;
				case reserved_words::UNTIL: 
					return tokens::UNTIL;
				case reserved_words::WHILE: 
					return tokens::WHILE;
				case reserved_words::DOWNTO: 
					return tokens::DOWNTO;
				case reserved_words::PACKED: 
					return tokens::PACKED;
				case reserved_words::RECORD: 
					return tokens::RECORD;
				case reserved_words::REPEAT: 
					return tokens::REPEAT;
				case reserved_words::PROGRAM: 
					return tokens::PROGRAM;
				case reserved_words::FUNCTION: 
					return tokens::FUNCTION;
				case reserved_words::PROCEDURE: 
					return tokens::PROCEDURE;
				default:
					return tokens::NO_TOKEN;
			}
		}
	}
}