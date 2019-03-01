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

// If cargo is extended, then we're dealing with hatches
// if cargo is retracted, then were dealing with cargo

LiftEndEffector::LiftEndEffector() {
    // put initialization code into the constructor
    LiftEndEffector::liftLS = new frc::DigitalInput(RobotPorts::kLiftLimSw);
    LiftEndEffector::bottomLS = new frc::DigitalInput(RobotPorts::kBottomLimSw);
    LiftEndEffector::liftPos = BOTTOM;
}

  void LiftEndEffector::liftUp(int numSwitches, bool disableSensor) {
      // without the sensor, this does nothing
      if (!disableSensor) {
          // We need to track the number of sensor clicks

      }
  }

  void LiftEndEffector::liftDown(int numSwitches, bool disableSensor) {
      // without the sensor, this does nothing
      if (!disableSensor) {
          // we need to track the number of senso clicks
      }
  }

  void LiftEndEffector::bottomPos(bool disableSensor) {
      // without the sensor, this does nothing
      if (!disableSensor) {
          if (LiftEndEffector::liftPos > BOTTOM) {
              // we need to go down
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
      m_LiftMotor.Set(LiftEndEffector::liftMotorSpeed);
  }

  void LiftEndEffector::manualLiftDown() {
      m_LiftMotor.Set(-LiftEndEffector::liftMotorSpeed);
  }

  void LiftEndEffector::manualLiftStop() {
      m_LiftMotor.Set(0.0);
  }

LiftEndEffector* LiftEndEffector::getInstance() {
    if (INSTANCE == nullptr) {
        INSTANCE = new LiftEndEffector();
    }
    return INSTANCE;
}