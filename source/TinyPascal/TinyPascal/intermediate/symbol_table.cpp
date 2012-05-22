/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "symbol_table.h"
#include <algorithm>

using std::find_if;



namespace pascal {
	namespace intermediate {

		class symbol_name_predicate{
		public:
			symbol_name_predicate(std::string const & name_) : name(name_){

			}

			bool operator()( symbol_table_entry const & entry){
				return (entry.getName() == name);
			}

		private:
			std::string name;
		};


		symbol_table::symbol_table(int level_) : level(level_)
		{

		}
			
		bool symbol_table::containsSymbol(std::string const & name) const
		{

			symbol_name_predicate pred(name);

			return (find_if(symbols.begin(), symbols.end(),pred) != symbols.end());
		}
			
		bool symbol_table::isGlobalSymbolTable() const
		{
			return level == 0;
		}
			
		symbol_table_entry const & symbol_table::lookup(std::string name) const
		{
			symbol_name_predicate pred(name);

			std::vector<symbol_table_entry>::const_iterator result = find_if(symbols.begin(), symbols.end(),pred);

			return *(result);
		}

		void symbol_table::addSymbol(symbol_table_entry const & entry)
		{
			symbols.push_back(entry);
		}
	}
}
			