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
LiftEndEffector* liftEF;
frc::DigitalInput* bottomLS;
frc::DigitalInput* liftLS;
frc::DigitalInput* threadLSPlaceHolder;
frc::Timer* liftTimer;
sem_t lifterSem;

bool movementComplete = false;
bool abortThreadIteration = false;
bool liftTimeOut = false;

#if defined(__linux__)
static void LifterThread() {
  while (true) {           // repeat forever
    sem_wait(&lifterSem);  // Wait until we're needed
    liftEF->liftIsActive = true;
    liftTimer->Reset();
    liftTimeOut = false;

    if (liftEF->liftDestinationIsBottom) {  // Are we going to the bottom?
      threadLSPlaceHolder = bottomLS;
    } else {
      threadLSPlaceHolder = liftLS;  // Nope we're using the lift LS instead
    }
    liftTimer->Start();
    if (!liftEF->disableSensor) {  // sensor is active
      while (liftEF->numClicks) {
        while ((threadLSPlaceHolder->Get()) &&
               !(liftTimeOut)) {  //  Get() is true is switch is not pushed
          frc::Wait(0.2);         // check every .2 seconds
          if (liftTimer->Get() >
              LiftEndEffector::MAX_TIME_OUT) {  // Whoops!  We timed out
            liftTimeOut = true;
            liftEF->manualLiftStop();  // We got abort so stop the lift
            break;
          }
        }
        if (!liftTimeOut) {
          liftEF->numClicks--;
          if (liftEF->currentDirection ==
              LiftEndEffector::direction::UP) {  // We're going up
            liftEF->liftPos + 1;
          } else {
            if (liftEF->currentDirection ==
                LiftEndEffector::direction::DOWN) {  // We're going down
              liftEF->liftPos - 1;
            }
          }
        } else {
          liftEF->manualLiftStop();  //  make sure the lift is stopped
        }
      }
      liftEF->manualLiftStop();  //  We've arrives so stop the motor
    } else {
      // sensor is disabled so we shouldn't be in the tread at all
      printf("Lift sensor is disabled!  Use Manual Mode!\n");
    }
    liftTimer->Stop();
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
  LiftEndEffector::currentDirection = STOPPED;
  LiftEndEffector::liftMotorSpeed = 1.0;  // set the motorspeed

  liftTimer = new frc::Timer();

  // Initialize the Lifter Thread state variables
  LiftEndEffector::liftIsActive = false;
  LiftEndEffector::numClicks = 0;
  LiftEndEffector::liftDestinationIsBottom = false;
  LiftEndEffector::disableSensor = false;

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
  wpi::errs() << "Lifter Thread only available on Linux.\n";
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

void LiftEndEffector::liftTimerStop() { liftTimer->Stop(); }

void LiftEndEffector::liftUp(int numSwitches, bool disSensor) {
  // without the sensor, this does nothing
  if (!disSensor) {
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
  m_LiftMotor->Set(-(liftEF->liftMotorSpeed));
  printf("Liftup\n");
}

void LiftEndEffector::manualLiftDown() {
  m_LiftMotor->Set(liftEF->liftMotorSpeed);
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