/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "abstract_syntax_tree_node.h"

namespace pascal{
	namespace intermediate{
		abstract_syntax_tree_node::abstract_syntax_tree_node(asttypes::abstract_syntax_tree_node_type type_) : type(type_)
		{

		}

		size_t const abstract_syntax_tree_node::size() const
		{
			return children.size();
		}

		std::vector<std::unique_ptr<abstract_syntax_tree_node> > const & abstract_syntax_tree_node::getChildren() const
		{
			return children;
		}

        std::shared_ptr<abstract_syntax_tree_attribute>& abstract_syntax_tree_node::getAttribute(astattrtypes::abstract_syntax_tree_node_attribute_type type) 
		{
			return attributes[type];
		}

        void abstract_syntax_tree_node::addChild(std::unique_ptr<abstract_syntax_tree_node>& node)
		{
			children.push_back(std::move(node));
		}

        void abstract_syntax_tree_node::setAttribute(astattrtypes::abstract_syntax_tree_node_attribute_type type, std::shared_ptr<abstract_syntax_tree_attribute>& attribute)
		{
			attributes[type] = attribute;
		}
	}
}