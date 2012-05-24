#include "syntax_exception.h"

namespace pascal {
    namespace frontend {
        syntax_exception::syntax_exception(string const & message) : std::runtime_error(message) {
        }

        syntax_exception::~syntax_exception() {
        }  
    }
}