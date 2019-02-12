/**
 * CargoEndEffector.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#include <CargoEndEffector.h>
#include <stdio.h>
#include "Ports.h"

CargoEndEffector* CargoEndEffector::INSTANCE = nullptr;

CargoEndEffector::CargoEndEffector() {
    // put initialization code into the constructor
}

void getCargo () {
    printf("Getting Cargo\n");
}

CargoEndEffector* CargoEndEffector::getInstance() {
    if (INSTANCE == nullptr) {
        INSTANCE = new CargoEndEffector();
    }
    return INSTANCE;
}
