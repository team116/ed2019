/**
 * TipperEndEffector.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#include <TipperEndEffector.h>
#include "Ports.h"

TipperEndEffector* TipperEndEffector::INSTANCE = nullptr;

TipperEndEffector::TipperEndEffector() {
    // put initialization code into the constructor
}

TipperEndEffector* TipperEndEffector::getInstance() {
    if (INSTANCE == nullptr) {
        INSTANCE = new TipperEndEffector();
    }
    return INSTANCE;
}
