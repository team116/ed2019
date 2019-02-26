/**
 * LiftEndEffector.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#include <frc/DigitalInput.h>
#include <LiftEndEffector.h>
#include "Ports.h"

LiftEndEffector* LiftEndEffector::INSTANCE = nullptr;

LiftEndEffector::LiftEndEffector() {
    // put initialization code into the constructor
    LiftEndEffector::liftLS = new frc::DigitalInput(RobotPorts::kLiftLimSw);
    LiftEndEffector::bottomLS = new frc::DigitalInput(RobotPorts::kBottomLimSw);
    LiftEndEffector::liftPos = BOTTOM;
}

LiftEndEffector* LiftEndEffector::getInstance() {
    if (INSTANCE == nullptr) {
        INSTANCE = new LiftEndEffector();
    }
    return INSTANCE;
}