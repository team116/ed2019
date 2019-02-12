/**
 * HatchEndEffector.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#include <HatchEndEffector.h>
#include "Ports.h"

HatchEndEffector* HatchEndEffector::INSTANCE = nullptr;

HatchEndEffector::HatchEndEffector() {
    // put initialization code into the constructor
}

HatchEndEffector* HatchEndEffector::getInstance() {
    if (INSTANCE == nullptr) {
        INSTANCE = new HatchEndEffector();
    }
    return INSTANCE;
}

