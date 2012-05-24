/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef _PARSER_BASE_H_
#define _PARSER_BASE_H_

#include <string>
#include <boost/noncopyable.hpp>
#include <memory>
#include "token_type.h"
#include "token.h"

#ifdef _WIN32
#include "../intermediate/abstract_syntax_tree_node.h"
#else
#include "abstract_syntax_tree_node.h"
#include "scanner.h"
#endif

namespace pascal{
	namespace frontend{
		class parser_base : public boost::noncopyable{
		public:
			parser_base(scanner& lexer_);
			virtual ~parser_base() = 0;
			virtual std::unique_ptr<pascal::intermediate::abstract_syntax_tree_node> parse(std::shared_ptr<token>& token) = 0;

        public:
            scanner& lexer;
		};
	}
}
#endif