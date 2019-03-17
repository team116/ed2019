/**
 * Utils.h
 *
 *  Created on: March 17, 2019
 *      Author: Mike A.
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <Ports.h>
#include <ctre/Phoenix.h>
#include <frc/DriverStation.h>
#include <frc/GenericHID.h>
#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <thread>

using namespace frc;

class ButtonDebouncer {
  Joystick *joystick;
  int buttonnum;
  double latest;
  double debounce_period;
  Timer* debounceTimer;

 public:
  ButtonDebouncer(Joystick *joystick, int buttonnum) {
    this->joystick = joystick;
    this->buttonnum = buttonnum;
    this->latest = 0;
    this->debounce_period = .5;
  }
  ButtonDebouncer(Joystick *joystick, int buttonnum, float period) {
    this->joystick = joystick;
    this->buttonnum = buttonnum;
    this->latest = 0;
    this->debounce_period = period;
  }

  void setDebouncePeriod(float period) { this->debounce_period = period; }

  bool get() {
    double now = debounceTimer->GetFPGATimestamp();
    if (joystick->GetRawButton(buttonnum)) {
      if ((now - latest) > debounce_period) {
        latest = now;
        return true;
      }
    }
    return false;
  }
};
#endif /* SRC_UTILS_H_ */