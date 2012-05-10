#include "syntax_exception.h"


syntax_exception::syntax_exception(const char *message) : exception(message) {
}

syntax_exception::~syntax_exception() {
}
