#include <iostream>
#include "token.h"
#include "scanner.h"

using namespace std;

int main(int argc, const char *argv[]) {

    cout << "File supplied for scanning is: " << argv[1] << endl;

    std::string file(argv[1]);
    scanner s(file);

    shared_ptr<token> t = s.getNextToken();

    while (t->validToken()) {
        cout << "Processed token: " << t->getTypeAsString() << " - " << t->getText() << endl;
        t = s.getNextToken();
    }

    return 0;
}