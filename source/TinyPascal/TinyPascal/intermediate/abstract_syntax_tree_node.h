/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef __AST_NODE_H_
#define __AST_NODE_H_

#include <memory>
#include <vector>
#include <map>
#include <string>
#include "abstract_syntax_tree_node_type.h"
#include "abstract_syntax_tree_attribute.h"
#include "abstract_syntax_tree_node_attribute_type.h"

namespace pascal{
    namespace intermediate{
        class abstract_syntax_tree_node {
        public:
			explicit abstract_syntax_tree_node(asttypes::abstract_syntax_tree_node_type type_);

            size_t const size() const;
            bool const hasChildren() const;
            std::string toString() const;
            std::vector<std::unique_ptr<abstract_syntax_tree_node> > const & getChildren() const;
            std::shared_ptr<abstract_syntax_tree_attribute>& getAttribute(astattrtypes::abstract_syntax_tree_node_attribute_type type) ;

            void addChild(std::unique_ptr<abstract_syntax_tree_node>& node);
            void setAttribute(astattrtypes::abstract_syntax_tree_node_attribute_type type, std::shared_ptr<abstract_syntax_tree_attribute> const& attribute);

        private:
            asttypes::abstract_syntax_tree_node_type type;
            std::vector<std::unique_ptr<abstract_syntax_tree_node> > children;
			std::map<astattrtypes::abstract_syntax_tree_node_attribute_type, std::shared_ptr<abstract_syntax_tree_attribute> > attributes;
        };
    }
}

#endif
