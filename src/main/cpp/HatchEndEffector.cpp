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
    hatchEjectorSolenoid.Set(frc::DoubleSolenoid::kOff);
}

void HatchEndEffector::hatchDeploy() {
    hatchEjectorSolenoid.Set(frc::DoubleSolenoid::kForward); 
}

void HatchEndEffector::hatchRetract() {
    hatchEjectorSolenoid.Set(frc::DoubleSolenoid::kReverse); 
}

void HatchEndEffector::hatchOff() {
    hatchEjectorSolenoid.Set(frc::DoubleSolenoid::kOff); 
}

HatchEndEffector* HatchEndEffector::getInstance() {
    if (INSTANCE == nullptr) {
        INSTANCE = new HatchEndEffector();
    }
    return INSTANCE;
}

