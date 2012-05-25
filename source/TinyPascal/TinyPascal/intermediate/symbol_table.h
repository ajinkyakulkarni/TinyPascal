/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef _SYMBOL_TABLE_H
#define _SYMBOL_TABLE_H

#include <vector>
#include "symbol_table_entry.h"
#include <string>

namespace pascal {
	namespace intermediate {

		class symbol_table{
		public:
			symbol_table(int level_);
			
			bool containsSymbol(std::string const & name) const;
			bool isGlobalSymbolTable() const;
			symbol_table_entry const & lookup(std::string name) const;
			symbol_table_entry& lookup(std::string name);

			void addSymbol(symbol_table_entry const & entry);
		private:
			int level;
			std::vector<symbol_table_entry> symbols;
		};

	}
}
#endif
