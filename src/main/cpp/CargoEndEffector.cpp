/**
 * CargoEndEffector.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#include <frc/DoubleSolenoid.h>
#include <frc/DigitalInput.h>
#include <CargoEndEffector.h>
#include <stdio.h>
#include "Ports.h"

CargoEndEffector* CargoEndEffector::INSTANCE = nullptr;

CargoEndEffector::CargoEndEffector() {
    // put initialization code into the constructor
    CargoIntakeSolenoid.Set(frc::DoubleSolenoid::kOff);
    CargoEndEffector::cargoLS = new frc::DigitalInput(RobotPorts::kBallIntakeLimSw);
}

void CargoEndEffector::intakeMovement(Direction direction, double speed) {
    switch (direction) {
        case INTAKE :
            m_IntakeMotor.Set(speed);
        break;
        case EJECT :
            m_IntakeMotor.Set(speed);
        break;
        case OFF:
            m_IntakeMotor.Set(0.0);
        break;
        default:
            m_IntakeMotor.Set(0.0);          
    } 
}

void CargoEndEffector::intakeDeploy() {
    CargoIntakeSolenoid.Set(frc::DoubleSolenoid::kForward); 
}

void CargoEndEffector::intakeOff() {
    CargoIntakeSolenoid.Set(frc::DoubleSolenoid::kOff); 
}

void CargoEndEffector::intakeRetract() {
    CargoIntakeSolenoid.Set(frc::DoubleSolenoid::kReverse); 
}


CargoEndEffector* CargoEndEffector::getInstance() {
    if (INSTANCE == nullptr) {
        INSTANCE = new CargoEndEffector();
    }
    return INSTANCE;
}
