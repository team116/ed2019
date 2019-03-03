/**
 * TipperEndEffector.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#include <frc/DigitalInput.h>

#include <OI.h>
#include <TipperEndEffector.h>
#include "Ports.h"

TipperEndEffector* TipperEndEffector::INSTANCE = nullptr;

TipperEndEffector::TipperEndEffector() {
  // put initialization code into the constructor
  Tipper1EjectorSolenoid.Set(frc::DoubleSolenoid::kOff);
  Tipper2EjectorSolenoid.Set(frc::DoubleSolenoid::kOff);
  TipperEndEffector::elevatorLS =
      new frc::DigitalInput(RobotPorts::kElevatorLimSw);
}

void TipperEndEffector::tipClimb(double speed, bool disableSensor) {
  m_TipperMotor.Set(speed);
  if (!disableSensor) {
    while (!(elevatorLS->Get())) {
      frc::Wait(0.2);  // check every .2 seconds
    }
  }
}

void TipperEndEffector::tipLower(double speed) { m_TipperMotor.Set(-speed); }

void TipperEndEffector::tipStop() { m_TipperMotor.Set(0.0); }

void TipperEndEffector::tipOff() {
  Tipper1EjectorSolenoid.Set(frc::DoubleSolenoid::kOff);
  Tipper2EjectorSolenoid.Set(frc::DoubleSolenoid::kOff);
}
void TipperEndEffector::tipDeploy() {
  Tipper1EjectorSolenoid.Set(frc::DoubleSolenoid::kReverse);
  Tipper2EjectorSolenoid.Set(frc::DoubleSolenoid::kReverse);
}

void TipperEndEffector::tipRetract() {
  Tipper1EjectorSolenoid.Set(frc::DoubleSolenoid::kForward);
  Tipper2EjectorSolenoid.Set(frc::DoubleSolenoid::kForward);
}

TipperEndEffector* TipperEndEffector::getInstance() {
  if (INSTANCE == nullptr) {
    INSTANCE = new TipperEndEffector();
  }
  return INSTANCE;
}
