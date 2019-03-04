/**
 * LiftEndEffector.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#include <LiftEndEffector.h>
#include <frc/DigitalInput.h>
#include <frc/Timer.h>
#include "Ports.h"

LiftEndEffector* LiftEndEffector::INSTANCE = nullptr;

// If cargo is extended, then we're dealing with hatches
// if cargo is retracted, then were dealing with cargo

LiftEndEffector::LiftEndEffector() {
  // put initialization code into the constructor
  LiftEndEffector::liftLS = new frc::DigitalInput(RobotPorts::kLiftLimSw);
  LiftEndEffector::bottomLS = new frc::DigitalInput(RobotPorts::kBottomLimSw);
  LiftEndEffector::liftPos = BOTTOM;
  LiftEndEffector::liftTimer = new frc::Timer();

}

void LiftEndEffector::liftTimerReset() {
  LiftEndEffector::liftTimer->Reset();
}

void LiftEndEffector::liftTimerStart() {
  LiftEndEffector::liftTimer->Start();
}

void LiftEndEffector::liftUp(int numSwitches, bool disableSensor) {
  // without the sensor, this does nothing
  if (!disableSensor) {
    // We need to track the number of sensor clicks
    while (!(liftLS->Get())) {
      frc::Wait(0.2);  // check every .2 seconds
    }
  }
}

void LiftEndEffector::liftDown(int numSwitches, bool disableSensor) {
  // without the sensor, this does nothing
  if (!disableSensor) {
    // we need to track the number of senso clicks
    while (!(liftLS->Get())) {
      frc::Wait(0.2);  // check every .2 seconds
    }
  }
}

void LiftEndEffector::bottomPos(bool disableSensor) {
  // without the sensor, this does nothing
  int numSwitchesToGo = 0;
  if (!disableSensor) {
    if (LiftEndEffector::liftPos > BOTTOM) {
      numSwitchesToGo = LiftEndEffector::liftPos;  // This is the number of switches to go
      if (!disableSensor) {
        // we need to track the number of sensor clicks
        while (!(liftLS->Get())) {
          frc::Wait(0.2);  // check every .2 seconds
        }
      }
    }
  }
}

void LiftEndEffector::cargoPos(int numSwitches, bool disableSensor) {
  // without the sensor, this does nothing
  if (!disableSensor) {
    if (LiftEndEffector::liftPos < CARGOBAY) {
      // we need to go up
    }
    if (LiftEndEffector::liftPos > CARGOBAY) {
      // we need to go down
    }
  }
}

void LiftEndEffector::manualLiftUp() {
  m_LiftMotor.Set(-LiftEndEffector::liftMotorSpeed);
  printf("Liftup\n");
}

void LiftEndEffector::manualLiftDown() {
  m_LiftMotor.Set(LiftEndEffector::liftMotorSpeed);
  printf("LiftDown\n");
}

void LiftEndEffector::manualLiftStop() {
  printf("LiftStop\n");
  m_LiftMotor.Set(0.0);
}

LiftEndEffector* LiftEndEffector::getInstance() {
  if (INSTANCE == nullptr) {
    INSTANCE = new LiftEndEffector();
  }
  return INSTANCE;
}