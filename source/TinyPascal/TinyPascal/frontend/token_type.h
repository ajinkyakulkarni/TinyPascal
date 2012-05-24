/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef _TOKEN_TYPE_H_
#define _TOKEN_TYPE_H_

namespace pascal {
	namespace frontend {
		struct tokens{
			enum token_type{
				AND, ARRAY, BEGIN, CASE, CONST, DIV, DO, DOWNTO, ELSE, END,
				FILE, FOR, FUNCTION, GOTO, IF, IN, LABEL, MOD, NIL, NOT,
				OF, OR, PACKED, PROCEDURE, PROGRAM, RECORD, REPEAT, SET,
				THEN, TO, TYPE, UNTIL, VAR, WHILE, WITH,PLUS, MINUS, STAR, 
				SLASH, COLON_EQUALS,DOT, COMMA, SEMICOLON, COLON, QUOTE,
				EQUALS, NOT_EQUALS, LESS_THAN, LESS_EQUALS,	GREATER_EQUALS, 
				GREATER_THAN, LEFT_PAREN, RIGHT_PAREN,LEFT_BRACKET, RIGHT_BRACKET, 
				LEFT_BRACE, RIGHT_BRACE,UP_ARROW, DOT_DOT,IDENTIFIER, INTEGER, REAL, 
				STRING,END_OF_FILE, WHITESPACE,NO_TOKEN
			};
		};
	}
}

#endif