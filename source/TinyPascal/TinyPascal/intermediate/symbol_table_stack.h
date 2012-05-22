/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _SYMBOL_TABLE_STACK_H
#define _SYMBOL_TABLE_STACK_H

#include "symbol_table_entry.h"
#include "symbol_table.h"
#include <vector>
#include <string>

namespace pascal{
	namespace intermediate{
		class symbol_table_stack{
		public:
			symbol_table_stack(int level_);

			int currentLevel() const;
			bool localLookupContainsSymbol(std::string const & entry) const;
			bool lookupContainsSymbol(std::string const & entry) const;
			const symbol_table_entry& localLookup(std::string const & entry) const;
			const symbol_table_entry& lookup(std::string const & entry) const;

			void addNewLevel();
			void addLocalSymbol(symbol_table_entry const & entry);

			void removeLevel();
		private:
			int level;
			std::vector<symbol_table> tables;
		};
	}
}

#endif