#ifndef _SCANNER_STATE_H_
#define _SCANNER_STATE_H_

#include "scanner.h"
#include "token.h"
#include <memory>

class scanner_state {
public:

    scanner_state(scanner& scanner);

    virtual ~scanner_state() = 0;

    virtual std::shared_ptr<token> processScannerStream() = 0;

    virtual bool canProcess() = 0;

private:
    scanner& scanner_;

};

#endif
