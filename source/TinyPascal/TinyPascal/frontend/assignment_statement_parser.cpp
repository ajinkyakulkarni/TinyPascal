/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "assignment_statement_parser.h"
#include "expression_parser.h"
#include "unexpected_token_exception.h"

#ifdef _WIN32
#include "../intermediate/symbol_table_entry.h"
#else
#include "symbol_table_entry.h"
#endif

namespace pascal{
	namespace frontend{

		typedef pascal::intermediate::abstract_syntax_tree_node astnode;
		typedef std::unique_ptr<astnode> unode;

		assignment_statement_parser::assignment_statement_parser(pascal::frontend::scanner& lexer_, pascal::intermediate::symbol_table_stack& stable_) : statement_parser(lexer_, stable_)
		{

		}
			
		assignment_statement_parser::~assignment_statement_parser()
		{

		}

		std::unique_ptr<pascal::intermediate::abstract_syntax_tree_node> assignment_statement_parser::parse(std::shared_ptr<token>& token)
		{

			unode assign_node(new astnode(pascal::intermediate::asttypes::ASSIGN));

			if(stable.lookupContainsSymbol(token->getText()))
			{
				pascal::intermediate::symbol_table_entry& entry = stable.lookup(token->getText());
				entry.appendLineNumber(token->getLine());

			}else{
				pascal::intermediate::symbol_table_entry entry(token->getText());
				entry.appendLineNumber(token->getLine());
				stable.addLocalSymbol(entry);
			}

			token = lexer.getNextToken(); //consum colon equals token

			unode variable_node(new astnode(pascal::intermediate::asttypes::VARIABLE));

			assign_node->addChild(variable_node);

			if (token->getType() != tokens::COLON_EQUALS) 
			{
				throw unexpected_token_exception(":= expected in assignment statement");
			}

			expression_parser exp(lexer,stable);
			assign_node->addChild(exp.parse(token));

			return assign_node;
		}
	}
}