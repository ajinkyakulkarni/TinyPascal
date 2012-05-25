/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "parser.h"
#include "statement_parser.h"

#ifdef _WIN32

#include "../intermediate/abstract_syntax_tree.h"

#else

#include "abstract_syntax_tree.h"

#endif


#include <memory>

namespace pascal{
    namespace frontend{

        parser::parser(pascal::frontend::scanner& lexer_, pascal::intermediate::symbol_table_stack& symbol_table_stack_ ) : lexer(lexer_), stable(symbol_table_stack_)
        {
        }

        void parser::parse()
        {
			using pascal::intermediate::abstract_syntax_tree;
            abstract_syntax_tree root;
			
			std::shared_ptr<token> token = lexer.getNextToken();

			if(token->getType() == tokens::BEGIN)
			{
				statement_parser sparser(this->lexer,this->stable);
				root.assign(sparser.parse(token));
			}else{
				// error we should start with begin....
			}

        }

    }
}