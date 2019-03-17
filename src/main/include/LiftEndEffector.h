/**
 * LiftEndEffector.h
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#ifndef SRC_LIFTENDEFFECTOR_H_
#define SRC_LIFTENDEFFECTOR_H_

#include <Ports.h>
#include <ctre/Phoenix.h>
#include <frc/DigitalInput.h>
#include <frc/DriverStation.h>
#include <frc/Timer.h>
#include <semaphore.h>

class LiftEndEffector {
 public:
  static LiftEndEffector *getInstance();

  double liftMotorSpeed;

  enum liftPosition {
    BOTTOM,
    LOADER,
    RKTBTMCARGO,
    CARGOBAY,
    RKTMIDHATCH,
    RKTMIDCARGO,
    RKTTOPHATCH,
    RKTTOPCARGO
  };

  enum direction { UP, DOWN, STOPPED };

  direction currentDirection;  // we start the match with no direction on the lift

  liftPosition liftPos;  // Start at the bottom position at the beginning of the match

  bool liftIsActive;
  int numClicks ;
  bool liftDestinationIsBottom;
  bool disableSensor;

  frc::DigitalInput* bottomLS;
  frc::DigitalInput* liftLS;

  static const int MAX_TIME_OUT = 4.0;   // time out for the lift travel

  void liftUp(int numSwitches);
  void liftDown(int numSwitches);
  void manualLiftUp();
  void manualLiftDown();
  void manualLiftStop();
  void bottomPos(int numSwitches);
  void liftTimerReset();
  void liftTimerStart();
  void liftTimerStop();
 
 private:
  LiftEndEffector();
  static LiftEndEffector *INSTANCE;
};

#endif /* SRC_LIFTENDEFFECTOR_H_ */