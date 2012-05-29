/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "statement_parser.h"
#include "compound_statement_parser.h"
#include "assignment_statement_parser.h"
#include "unexpected_token_exception.h"

namespace pascal{
	namespace frontend{

		typedef pascal::intermediate::abstract_syntax_tree_node astnode;
		typedef std::unique_ptr<astnode> unode;

		using std::shared_ptr;


		statement_parser::statement_parser(pascal::frontend::scanner& lexer_, pascal::intermediate::symbol_table_stack& stable_) : parser_base(lexer_, stable_)
		{

		}

		statement_parser::~statement_parser()
		{

		}

		std::unique_ptr<pascal::intermediate::abstract_syntax_tree_node> statement_parser::parse()
		{

			shared_ptr<token> current = lexer.current();

			if(current->getType() == tokens::BEGIN){
				compound_statement_parser cps(lexer, stable);
				return cps.parse();
			}else if(current->getType() == tokens::IDENTIFIER){
				assignment_statement_parser asp(lexer, stable);
				return asp.parse();
			}else{
				unode no_op_node(new astnode(pascal::intermediate::asttypes::NO_OP));
				return no_op_node;
			}

		}

        void statement_parser::parseStatementList(std::unique_ptr<pascal::intermediate::abstract_syntax_tree_node>& compoundNode)
        {
            while(lexer.current()->getType() != tokens::END_OF_FILE && lexer.current()->getType() != tokens::END)
            {
                std::unique_ptr<pascal::intermediate::abstract_syntax_tree_node> statementNode = parse();
                compoundNode->addChild(statementNode);

				lexer.consume();

                if (lexer.current()->getType() == tokens::SEMICOLON){
                    lexer.consume(); // consume ;
                }else if (lexer.current()->getType() == tokens::END)
                {
                    lexer.consume();; // consume END
                }else{
                    throw unexpected_token_exception("expected ; or END");
                }

            }

            if (lexer.current()->getType() != tokens::END){
                throw unexpected_token_exception("expected END");
            }

            lexer.consume();

        }
	}
}