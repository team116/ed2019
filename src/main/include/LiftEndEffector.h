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

  const double liftMotorSpeed = 1.0;

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

  liftPosition liftPos =
      BOTTOM;  // Start at the bottom position at the beginning of the match

  void liftUp(int numSwitches, bool disableSensor);
  void liftDown(int numSwitches, bool disableSensor);
  void manualLiftUp();
  void manualLiftDown();
  static void manualLiftStop();
  void bottomPos(bool disableSensor);
  void cargoPos(int numSwitches, bool disableSensor);
  void liftTimerReset();
  void liftTimerStart();

 private:
  LiftEndEffector();
  LiftEndEffector *liftEF;
  static LiftEndEffector *INSTANCE;
};

#endif /* SRC_LIFTENDEFFECTOR_H_ */