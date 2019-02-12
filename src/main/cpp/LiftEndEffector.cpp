/**
 * LiftEndEffector.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#include <LiftEndEffector.h>
#include "Ports.h"

LiftEndEffector* LiftEndEffector::INSTANCE = nullptr;

LiftEndEffector::LiftEndEffector() {
    // put initialization code into the constructor
}

LiftEndEffector* LiftEndEffector::getInstance() {
    if (INSTANCE == nullptr) {
        INSTANCE = new LiftEndEffector();
    }
    return INSTANCE;
}