#ifndef _FILE_BUFFER_H_
#define _FILE_BUFFER_H_

#include <string>
#include <fstream>
#include <boost/iostreams/stream_buffer.hpp>

class file_buffer {
public:

    file_buffer(std::string const & filename, int bufferSize);

    ~file_buffer();

    bool canPeek();

    char peek();

    char getCharacter();

    void returnCharacter(char i);

private:


    file_buffer(file_buffer const &);

    file_buffer& operator = (file_buffer);

private:
    const std::string filename_;
    const int bufferSize_;
    int index_;
    std::string buffer_;
    std::ifstream stream_;


};

#endif
