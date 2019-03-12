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

  static double liftMotorSpeed;

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

  static direction currentDirection;  // we start the match with no direction on the lift

  static liftPosition liftPos;  // Start at the bottom position at the beginning of the match

  bool liftIsActive;
  static int numClicks ;
  static bool liftDestinationIsBottom;
  static bool disableSensor;

  static const int MAX_TIME_OUT = 4.0;   // time out for the lift travel

  void liftUp(int numSwitches, bool disableSensor);
  void liftDown(int numSwitches, bool disableSensor);
  void manualLiftUp();
  void manualLiftDown();
  static void manualLiftStop();
  void bottomPos(bool disableSensor);
  void cargoPos(int numSwitches, bool disableSensor);
  void liftTimerReset();
  void liftTimerStart();
  void liftTimerStop();
 
 private:
  LiftEndEffector();
  static LiftEndEffector *INSTANCE;
};

#endif /* SRC_LIFTENDEFFECTOR_H_ */