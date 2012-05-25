/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "expression_parser.h"

namespace pascal{
	namespace frontend{
		expression_parser::expression_parser(pascal::frontend::scanner& lexer_, pascal::intermediate::symbol_table_stack& stable_) : parser_base(lexer_, stable_)
		{

		}
			
		expression_parser::~expression_parser()
		{

		}

		std::unique_ptr<pascal::intermediate::abstract_syntax_tree_node> expression_parser::parse(std::shared_ptr<token>& token)
		{
			return 0;
		}
	}
}