/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "abstract_syntax_tree_printer.h"
#include <iostream>


namespace pascal {
    namespace intermediate {

        void node_print(abstract_syntax_tree_node const & node, int level);

        void abstract_syntax_tree_printer::print(abstract_syntax_tree const & ast) const {
            node_print(ast.getRoot(), 0);
        }

        void node_print(abstract_syntax_tree_node const & node, int level) {
            if (!node.hasChildren()) return;

            std::string output;

            if (level > 0)
                output.append(level, ' ');

            output.append(node.toString());

            std::cout << "Node: " << output << std::endl;

            for(std::vector<std::unique_ptr<abstract_syntax_tree_node> >::const_iterator i = node.getChildren().begin(); i != node.getChildren().end(); ++i)
            {
                node_print(*(i->get()),(level + 1));
            }

        }
    }
}



