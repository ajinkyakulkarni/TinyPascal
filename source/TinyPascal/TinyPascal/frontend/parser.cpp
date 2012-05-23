/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "parser.h"
#include "eof_token.h"
#include <memory>

namespace pascal{
    namespace frontend{

        parser::parser(pascal::frontend::scanner& lexer_, pascal::intermediate::symbol_table_stack& symbol_table_stack_ ) : lexer(lexer_), stable(symbol_table_stack_)
        {
        }

        void parser::parse()
        {
            std::shared_ptr<token> t = lexer.getNextToken();

            eof_token* ptr = dynamic_cast<eof_token*>(t.get() );

            while(!ptr){
                t->print();
                t = lexer.getNextToken();
                ptr = dynamic_cast<eof_token*>(t.get() );
            }
        }

    }
}