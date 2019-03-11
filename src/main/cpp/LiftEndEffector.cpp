/**
 * LiftEndEffector.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#include <LiftEndEffector.h>

#ifdef EDV21
WPI_VictorSPX* m_LiftMotor;
#else
WPI_TalonSRX* m_LiftMotor;
#endif

LiftEndEffector* LiftEndEffector::INSTANCE = nullptr;
frc::DigitalInput* bottomLS;
frc::DigitalInput* liftLS;
frc::Timer* liftTimer;
sem_t lifterSem;
int numClicks = 0;
bool threadIsActive = false;
bool movementComplete = false;
bool abortThreadIteration = false;

#if defined(__linux__)
static void LifterThread() {
  while (true) {
    sem_wait(&lifterSem);               // Wait until we're needed
    while (numClicks > 0) {             // If we have clicks to go
      if (!abortThreadIteration) {      // Check to see if we need to bail out
        while (!(liftLS->Get())) {      // Check to see if switch is triggered
          if (!abortThreadIteration) {  // Check to see if we need to bail out
            frc::Wait(0.2);             // check every .2 seconds
          } else {
            LiftEndEffector::manualLiftStop();  // We got abort so stop the lift
            numClicks = 0;  // Let's bail out of looking for clicks
            break;
          }
        }
        numClicks--;  // decrement the click counter
      } else {
        LiftEndEffector::manualLiftStop();  // We got abort so stop the lift
        numClicks = 0;
        break;
      }
    }
  }
}
#endif

// If cargo is extended, then we're dealing with hatches
// if cargo is retracted, then were dealing with cargo

LiftEndEffector::LiftEndEffector() {
  // put initialization code into the constructor
  liftLS = new frc::DigitalInput(RobotPorts::kLiftLimSw);
  bottomLS = new frc::DigitalInput(RobotPorts::kBottomLimSw);
  LiftEndEffector::liftPos = BOTTOM;
  liftTimer = new frc::Timer();

  try {
    liftEF = LiftEndEffector::getInstance();
  } catch (std::exception& e) {
    frc::DriverStation::ReportError("Error initializing OI object");
    frc::DriverStation::ReportError(e.what());
  }

#if defined(__linux__)
  std::thread lifterThread(LifterThread);
  lifterThread.detach();
#else
  wpi::errs() << "Vision only available on Linux.\n";
  wpi::errs().flush();
#endif

#ifdef EDV21
  m_LiftMotor = new WPI_VictorSPX(RobotPorts::kLiftChannel);
#else
  m_LiftMotor = new WPI_TalonSRX(RobotPorts::kLiftChannel);
#endif
}

void LiftEndEffector::liftTimerReset() { liftTimer->Reset(); }

void LiftEndEffector::liftTimerStart() { liftTimer->Start(); }

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
      numSwitchesToGo =
          LiftEndEffector::liftPos;  // This is the number of switches to go
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
  m_LiftMotor->Set(-LiftEndEffector::liftMotorSpeed);
  printf("Liftup\n");
}

void LiftEndEffector::manualLiftDown() {
  m_LiftMotor->Set(LiftEndEffector::liftMotorSpeed);
  printf("LiftDown\n");
}

void LiftEndEffector::manualLiftStop() {
  printf("LiftStop\n");
  m_LiftMotor->Set(0.0);
}

LiftEndEffector* LiftEndEffector::getInstance() {
  if (INSTANCE == nullptr) {
    INSTANCE = new LiftEndEffector();
  }
  return INSTANCE;
}