/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "symbol_table_stack.h"
#include "symbol_not_found_exception.h"

namespace pascal {
	namespace intermediate {

		symbol_table_stack::symbol_table_stack(int level_) : level(level_)
		{
			symbol_table t(level_);
			tables.push_back(t);
		}

		int symbol_table_stack::currentLevel() const
		{
			return level;
		}

		bool symbol_table_stack::localLookupContainsSymbol(std::string const & entry) const
		{
			return tables[level].containsSymbol(entry);
		}
			
		bool symbol_table_stack::lookupContainsSymbol(std::string const & entry) const
		{
			for(std::vector<symbol_table>::const_iterator i = tables.begin(); i != tables.end(); ++i){
				if( (*i).containsSymbol(entry) ){
					return true;
				}
			}

			return false;
		}

		const symbol_table_entry& symbol_table_stack::localLookup(std::string const & entry) const
		{
			return tables[level].lookup(entry);
		}

		symbol_table_entry& symbol_table_stack::lookup(std::string const & entry) 
		{
			for(std::vector<symbol_table>::iterator i = tables.begin(); i != tables.end(); ++i){
				if( (*i).containsSymbol(entry) ){
					return (*i).lookup(entry);
				}
			}

			throw symbol_not_found_exception();
		}

		const symbol_table_entry& symbol_table_stack::lookup(std::string const & entry) const
		{
			for(std::vector<symbol_table>::const_iterator i = tables.begin(); i != tables.end(); ++i){
				if( (*i).containsSymbol(entry) ){
					return (*i).lookup(entry);
				}
			}

			throw symbol_not_found_exception();
		}

		void symbol_table_stack::addNewLevel()
		{
			tables.push_back(symbol_table(++level));
		}

		void symbol_table_stack::addLocalSymbol(symbol_table_entry const & entry)
		{
			return tables[level].addSymbol(entry);
		}

		void symbol_table_stack::removeLevel()
		{
			tables.pop_back();
		}

	}
}