/*
Copyright (c) 2011 Blair Davidson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "file_buffer.h"

using std::string;
using std::ifstream;

namespace pascal {
    namespace frontend {

        file_buffer::file_buffer(string const & filename, int bufferSize) : filename_(filename), bufferSize_(bufferSize), stream_(filename) {

        }

        file_buffer::~file_buffer() {

        }

        bool file_buffer::canPeek() {
            return static_cast<bool>(stream_.peek());
        }

        bool file_buffer::eof() {
            return stream_.eof();
        }

        char file_buffer::peek() {
            return stream_.peek();
        }

        char file_buffer::character() {
            return stream_.get();
        }

        void file_buffer::rewind() {
            stream_.unget();
        }
    }
}


