/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef __AST_NODE_TYPE_H_
#define __AST_NODE_TYPE_H_

namespace pascal{
	namespace intermediate{
		struct asttypes{
			enum abstract_syntax_tree_node_type{
				PROGRAM,
				PROCEDURE,
				FUNCTION,
				COMPOUND,
				ASSIGN,
				LOOP,
				TEST,
				CALL,
				PARAMETERS,
				IF,
				SELECT,
				SELECT_BRANCH,
				SELECT_CONSTANTS,
				NO_OP,
				EQ,
				NE,
				LT,
				LE,
				GT,
				GE,
				NOT,
				ADD,
				SUBTRACT,
				OR,
				NEGATE,
				MULTIPLY,
				INTEGER_DIVIDE,
				FLOAT_DIVIDE,
				MOD,
				AND,
				VARIABLE,
				SUBSCRIPTS,
				FIELD,
				INTEGER_CONSTANT,
				REAL_CONSTANT,
				STRING_CONSTANT,
				BOOLEAN_CONSTANT
			};
		};
	}
}

#endif
