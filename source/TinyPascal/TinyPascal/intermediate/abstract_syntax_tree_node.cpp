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

        bool const abstract_syntax_tree_node::hasChildren() const
        {
            return children.size() > 0;
        }

        std::string abstract_syntax_tree_node::toString() const
        {
            std::string result;

            switch(type)
            {
                case asttypes::ASSIGN:
                    result.append("ASSIGN");
                    break;
                case asttypes::ADD:
                    result.append("ADD");
                    break;
                case asttypes::AND:
                    result.append("AND");
                    break;
                case asttypes::BOOLEAN_CONSTANT:
                    result.append("BOOLEAN_CONSTANT");
                    break;
                case asttypes::CALL:
                    result.append("CALL");
                    break;
                case asttypes::COMPOUND:
                    result.append("COMPOUND");
                    break;
                case asttypes::EQ:
                    result.append("EQ");
                    break;
                case asttypes::FIELD:
                    result.append("FIELD");
                    break;
                case asttypes::FLOAT_DIVIDE:
                    result.append("FLOAT_DIVIDE");
                    break;
                case asttypes::FUNCTION:
                    result.append("FUNCTION");
                    break;
                case asttypes::GE:
                    result.append("GE");
                    break;
                case asttypes::GT:
                    result.append("GT");
                    break;
                case asttypes::IF:
                    result.append("IF");
                    break;
                case asttypes::INTEGER_CONSTANT:
                    result.append("INTEGER_CONSTANT");
                    break;
                case asttypes::INTEGER_DIVIDE:
                    result.append("INTEGER_DIVIDE");
                    break;
                case asttypes::LE:
                    result.append("LE");
                    break;
                case asttypes::LOOP:
                    result.append("LOOP");
                    break;
                case asttypes::LT:
                    result.append("LT");
                    break;
                case asttypes::MOD:
                    result.append("MOD");
                    break;
                case asttypes::MULTIPLY:
                    result.append("MULTIPLY");
                    break;
                case asttypes::NE:
                    result.append("NE");
                    break;
                case asttypes::NEGATE:
                    result.append("NEGATE");
                    break;
                case asttypes::NO_OP:
                    result.append("NO_OP");
                    break;
                case asttypes::NOT:
                    result.append("NOT");
                    break;
                case asttypes::OR:
                    result.append("OR");
                    break;
                case asttypes::PARAMETERS:
                    result.append("PARAMETERS");
                    break;
                case asttypes::PROCEDURE:
                    result.append("PROCEDURE");
                    break;
                case asttypes::PROGRAM:
                    result.append("PROGRAM");
                    break;
                case asttypes::REAL_CONSTANT:
                    result.append("REAL_CONSTANT");
                    break;
                case asttypes::SELECT:
                    result.append("SELECT");
                    break;
                case asttypes::SELECT_BRANCH:
                    result.append("SELECT_BRANCH");
                    break;
                case asttypes::SELECT_CONSTANTS:
                    result.append("SELECT_CONSTANTS");
                    break;
                case asttypes::STRING_CONSTANT:
                    result.append("STRING_CONSTANT");
                    break;
                case asttypes::SUBSCRIPTS:
                    result.append("SUBSCRIPTS");
                    break;
                case asttypes::SUBTRACT:
                    result.append("SUBTRACT");
                    break;
                case asttypes::TEST:
                    result.append("TEST");
                    break;
                case asttypes::VARIABLE:
                    result.append("VARIABLE");
                    break;
            }

            return result;
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

        void abstract_syntax_tree_node::setAttribute(astattrtypes::abstract_syntax_tree_node_attribute_type type, std::shared_ptr<abstract_syntax_tree_attribute> const& attribute)
		{
			attributes[type] = attribute;
		}
	}
}