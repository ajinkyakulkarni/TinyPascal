#ifndef _FILE_BUFFER_H_
#define _FILE_BUFFER_H_

#include <string>
#include <iostream>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>

class file_buffer {
public:

	file_buffer(std::string const & filename, int bufferSize);
	~file_buffer();

	bool canPeek();
	char peek();
	char character();

	void rewind();

private:

	file_buffer(file_buffer const &);
	file_buffer& operator = (file_buffer);
	
	const std::string filename_;
	const int bufferSize_;
	boost::iostreams::stream_buffer<boost::iostreams::file_sink> buffer_;
	std::istream stream_;
};

#endif
