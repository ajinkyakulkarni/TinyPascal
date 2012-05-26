//
// Created by blairdavidson on 26/05/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "id_attribute.h"


namespace pascal{
    namespace intermediate{
        id_attribute::id_attribute(std::string const & name_) : name(name_)
        {
        }

        id_attribute::~id_attribute()
        {

        }

        std::string const & id_attribute::getName() const
        {
            return name;
        }


    }
}