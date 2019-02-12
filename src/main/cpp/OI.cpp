/**
 * OI.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#include <OI.h>
#include "Ports.h"

OI* OI::INSTANCE = nullptr;

OI::OI() {
    // put initialization code into the constructor
}

OI* OI::getInstance() {
    if (INSTANCE == nullptr) {
        INSTANCE = new OI();
    }
    return INSTANCE;
}
