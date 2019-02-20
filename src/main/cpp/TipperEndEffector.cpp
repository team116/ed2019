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
    Tipper1EjectorSolenoid.Set(frc::DoubleSolenoid::kOff);
    Tipper2EjectorSolenoid.Set(frc::DoubleSolenoid::kOff);
}

void TipperEndEffector::tipClimb(double speed) {
    m_TipperMotor.Set(speed);
}

void TipperEndEffector::tipOff() {
    Tipper1EjectorSolenoid.Set(frc::DoubleSolenoid::kOff); 
    Tipper2EjectorSolenoid.Set(frc::DoubleSolenoid::kOff); 
}
void TipperEndEffector::tipDeploy() {
    Tipper1EjectorSolenoid.Set(frc::DoubleSolenoid::kForward); 
    Tipper2EjectorSolenoid.Set(frc::DoubleSolenoid::kForward); 
}

void TipperEndEffector::tipRetract() {
    Tipper1EjectorSolenoid.Set(frc::DoubleSolenoid::kReverse); 
    Tipper2EjectorSolenoid.Set(frc::DoubleSolenoid::kReverse); 
}

TipperEndEffector* TipperEndEffector::getInstance() {
    if (INSTANCE == nullptr) {
        INSTANCE = new TipperEndEffector();
    }
    return INSTANCE;
}
