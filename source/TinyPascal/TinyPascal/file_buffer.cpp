#include "file_buffer.h"
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>

using std::string;
using std::ifstream;

file_buffer::file_buffer(string const & filename, int bufferSize) : filename_(filename), bufferSize_(bufferSize), buffer_(filename, bufferSize), stream_(&buffer_){
	
}

file_buffer::~file_buffer() {

}

bool file_buffer::canPeek() {
	return stream_.peek();
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



