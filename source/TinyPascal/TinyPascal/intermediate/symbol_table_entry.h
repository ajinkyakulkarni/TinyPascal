/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef SYMBOL_TABLE_ENTRY
#define SYMBOL_TABLE_ENTRY

#include <string>
#include <vector>
#include <map>
#include "symbol_table_key.h"
#include "symbol_table_attribute.h"
#include <memory>

namespace pascal {
	namespace intermediate {
		class symbol_table_entry{
		public:
			symbol_table_entry(std::string const & name_);

			std::string const & getName() const;
			bool containsAttribute(symbol_table_key key) const;
			symbol_table_attribute const & getAttribute(symbol_table_key key) const;
			std::vector<int> const& getLineNumbers() const;

			void setAttribute(symbol_table_key key, std::shared_ptr<symbol_table_attribute> const & attr);
			void appendLineNumber(int line);
			

		private:
			std::string name;
			std::vector<int> lineNumbers;
			std::map<symbol_table_key, std::shared_ptr<symbol_table_attribute> > attributes;
		};
	}
}
#endif