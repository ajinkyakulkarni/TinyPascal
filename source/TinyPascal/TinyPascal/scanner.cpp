#include "scanner.h"
#include "scanner_state.h"

using std::string;
using std::map;
using std::ifstream;
using std::shared_ptr;



class scanner_impl {
public:
    scanner_impl(string const & filename) : filename_(filename) {

    }

    shared_ptr<token> getNextToken() {
        for (; ;) {
            if (state_->canProcess())
                return state_->processScannerStream();
        }
        return shared_ptr<token>(new token(END_OF_FILE));
    }

private:
    string filename_;
    shared_ptr<scanner_state> state_;
};


scanner::scanner(std::string const & filename) {
    impl_ = new scanner_impl(filename);
}

scanner::~scanner() {
    delete impl_;
}

shared_ptr<token> scanner::getNextToken() {
    return impl_->getNextToken();
}


