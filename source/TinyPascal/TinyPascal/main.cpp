/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <iostream>
#include "frontend\token.h"
#include "frontend\scanner.h"
#include "frontend\eof_token.h"


using namespace std;
using namespace pascal::frontend;

int main(int argc, const char *argv[]) {

    string file(argv[1]);
    scanner s(file);

    shared_ptr<token> t = s.getNextToken();

    try {

        eof_token* ptr = dynamic_cast<eof_token*>(t.get() );

        while(!ptr){
            t->print();
            t = s.getNextToken();
            ptr = dynamic_cast<eof_token*>(t.get() );
        }

    } catch(std::runtime_error& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    return 0;
}