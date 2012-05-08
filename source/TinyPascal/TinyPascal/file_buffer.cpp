#include "file_buffer.h"

using std::string;
using std::ifstream;

file_buffer::file_buffer(string const & filename, int bufferSize) : filename_(filename), bufferSize_(bufferSize), index_(0), buffer_(""), stream_(filename.c_str()) {
    //fillBuffer();
}

file_buffer::~file_buffer() {
    if (stream_.is_open()) {
        stream_.close();
    }
}

bool file_buffer::canPeek() {
    return 0;
}

char file_buffer::peek() {
    return 0;
}

char file_buffer::getCharacter() {
    return 0;
}

void file_buffer::returnCharacter(char i) {

}



