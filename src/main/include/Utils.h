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
#include <frc/DigitalInput.h>
#include <frc/DriverStation.h>
#include <frc/GenericHID.h>
#include <frc/Joystick.h>
#include <frc/XboxController.h>

class Utils {
 public:
  static Utils *getInstance();

  class DigitalDebouncer {
    frc::DigitalInput *digital;
    int portNum;
    double latest;
    double debounce_period = 0.5;  // default to 1/2 second
    frc::Timer *debounceTimer;

   public:
    DigitalDebouncer(frc::DigitalInput *digital, int portNum) {
      this->digital = digital;
      this->portNum = portNum;
      this->latest = 0.0;
      this->debounce_period = 0.5;
    }

    DigitalDebouncer(frc::DigitalInput *digital, int portNum, float period) {
      this->digital = digital;
      this->portNum = portNum;
      this->latest = 0.0;
      this->debounce_period = period;
    }

    void setDebouncePeriod(float period) { this->debounce_period = period; }

    bool get() {
      double now = debounceTimer->GetFPGATimestamp();
      if (digital->Get()) {
        if ((now - latest) > debounce_period) {
          latest = now;
          return true;
        }
      }
      return false;
    }

   private:
    // Instances
    frc::DriverStation &ds = frc::DriverStation::GetInstance();

    DigitalDebouncer();
    static DigitalDebouncer *INSTANCE;
  };

  class ButtonDebouncer {
    frc::Joystick *joystick;
    int buttonnum;
    double latest;
    double debounce_period;  // default to 1/2 second
    frc::Timer *debounceTimer;

   public:
    ButtonDebouncer(frc::Joystick *joystick, int buttonnum) {
      this->joystick = joystick;
      this->buttonnum = buttonnum;
      this->latest = 0;
      this->debounce_period = .5;
    }

    ButtonDebouncer(frc::Joystick *joystick, int buttonnum, float period) {
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

   private:
    // Instances
    frc::DriverStation &ds = frc::DriverStation::GetInstance();

    ButtonDebouncer();
    static ButtonDebouncer *INSTANCE;
  };

 private:
  Utils();
  static Utils *INSTANCE;
};

#endif /* SRC_UTILS_H_ */