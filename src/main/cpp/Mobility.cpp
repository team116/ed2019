/**
 * Mobility.cpp
 *
 *  Created on: Feb 23, 2019
 *      Author: Mike A.
 */

#include <Mobility.h>
#include <OI.h>
#include <cameraserver/CameraServer.h>
#include <ctre/Phoenix.h>
#include <frc/DriverStation.h>
#include <frc/GenericHID.h>
#include <frc/Joystick.h>
#include <frc/MotorSafety.h>
#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "Ports.h"

Mobility* Mobility::INSTANCE = nullptr;

Mobility::Mobility() {
  // put initialization code into the constructor
  // Get the OI instance

  try {
    oi = OI::getInstance();
  } catch (std::exception& e) {
    frc::DriverStation::ReportError("Error initializing OI object");
    frc::DriverStation::ReportError(e.what());
  }

  m_robotDrive.SetExpiration(2.0);
  m_robotDrive.SetSafetyEnabled(false);

#ifdef HASPIGEONIMU  // Do we have the pigeon IMU?
  pigeon = new PigeonIMU(RobotPorts::kPigeonChannel);
#endif
}

#ifdef HASPIGEONIMU  // Do we have the pigeon IMU?
/** @return 10% deadband */
double Db(double axisVal) {
  if (axisVal < -0.10) return axisVal;
  if (axisVal > +0.10) return axisVal;
  return 0;
}
/** @param value to cap.
 * @param peak positive double representing the maximum (peak) value.
 * @return a capped value.
 */
double Cap(double value, double peak) {
  if (value < -peak) return -peak;
  if (value > +peak) return +peak;
  return value;
}
/**
 * As a simple trick, lets take the spare talon and use the web-based
 * config to easily change the gains we use for the Pigeon servo.
 * The talon isn't being used for closed-loop, just use it as a convenient
 * storage for gains.
 */
void UpdateGains() {}
/**
 * Given the robot forward throttle and ratio, return the max
 * corrective turning throttle to adjust for heading.  This is
 * a simple method of avoiding using different gains for
 * low speed, high speed, and no-speed (zero turns).
 */
double MaxCorrection(double forwardThrot, double scalor) {
  /* make it positive */
  if (forwardThrot < 0) {
    forwardThrot = -forwardThrot;
  }
  /* max correction is the current forward throttle scaled down */
  forwardThrot *= scalor;
  /* ensure caller is allowed at least 10% throttle,
   * regardless of forward throttle */
  if (forwardThrot < 0.10) return 0.10;
  return forwardThrot;
}
#endif

void Mobility::process() {
  m_robotDrive.FeedWatchdog();

#ifdef HASPIGEONIMU  // Do we have the pigeon IMU?
  /* some temps for Pigeon API */
  PigeonIMU::GeneralStatus genStatus;
  double xyz_dps[3];
  /* grab some input data from Pigeon and gamepad*/
  pigeon->GetGeneralStatus(genStatus);
  pigeon->GetRawGyro(xyz_dps);

  PigeonIMU::FusionStatus* stat = new PigeonIMU::FusionStatus();
  pigeon->GetFusedHeading(*stat);
  double currentAngle = stat->heading;
  bool angleIsGood = (pigeon->GetState() == PigeonIMU::Ready) ? true : false;
  double currentAngularRate = xyz_dps[2];
  /* get input from gamepad */
  double forwardThrottle = oi->x;
  double turnThrottle = oi->y;
  /* deadbands so centering joysticks always results in zero output */
  forwardThrottle = Db(forwardThrottle);
  turnThrottle = Db(turnThrottle);
  /* simple state machine to update our goStraight selection */
  switch (goStraight) {
    /* go straight is off, better check gamepad to see if we should enable the feature */
    case GoStraightOff:
      if (oi->userWantsToGoStraight == false) {
        /* nothing to do */
      } else if (angleIsGood == false) {
        /* user wants to servo but Pigeon isn't connected? */
        goStraight = GoStraightSameThrottle; /* just apply same throttle to both sides */
      } else {
        /* user wants to servo, save the current heading so we know where to servo to. */
        goStraight = GoStraightWithPidgeon;
        targetAngle = currentAngle;
      }
      break;

    /* we are servo-ing heading with Pigeon */
    case GoStraightWithPidgeon:
      if (oi->userWantsToGoStraight == false) {
        goStraight = GoStraightOff; /* user let go, turn off the feature */
      } else if (angleIsGood == false) {
        goStraight =
            GoStraightSameThrottle; /* we were servoing with pidgy, but we lost
                                       connection?  Check wiring and deviceID setup */
      } else {
        /* user still wants to drive straight, keep doing it */
      }
      break;

    /* we are simply applying the same throttle to both sides, apparently Pigeon is not
     * connected */
    case GoStraightSameThrottle:
      if (oi->userWantsToGoStraight == false) {
        goStraight = GoStraightOff; /* user let go, turn off the feature */
      } else {
        /* user still wants to drive straight, keep doing it */
      }
      break;
  }

  /* if we can servo with IMU, do the math here */
  if (goStraight == GoStraightWithPidgeon) {
    /* very simple Proportional and Derivative (PD) loop with a cap,
     * replace with favorite close loop strategy or leverage future Talon <=> Pigeon
     * features. */
    turnThrottle = (targetAngle - currentAngle) * kPgain - (currentAngularRate)*kDgain;
    /* the max correction is the forward throttle times a scalar,
     * This can be done a number of ways but basically only apply small turning correction
     * when we are moving slow and larger correction the faster we move.  Otherwise you
     * may need stiffer pgain at higher velocities. */
    double maxThrot = MaxCorrection(forwardThrottle, kMaxCorrectionRatio);
    turnThrottle = Cap(turnThrottle, maxThrot);
  } else if (goStraight == GoStraightSameThrottle) {
    /* clear the turn throttle, just apply same throttle to both sides */
    turnThrottle = 0;
  } else {
    /* do nothing */
  }

  /* positive turnThrottle means turn to the left, this can be replaced with ArcadeDrive
   * object, or teams drivetrain object */
  float left = forwardThrottle - turnThrottle;
  float right = forwardThrottle + turnThrottle;
  left = Cap(left, 1.0);
  right = Cap(right, 1.0);

  /* some printing for easy debugging */
  if (++_printLoops > 50) {
    _printLoops = 0;
    printf("------------------------------------------\n");
    printf("error: %f\n", targetAngle - currentAngle);
    printf("angle: %f\n", currentAngle);
    printf("rate: %f\n", currentAngularRate);
    printf("noMotionBiasCount: %i\n", genStatus.noMotionBiasCount);
    printf("tempCompensationCount: %i\n", genStatus.tempCompensationCount);
    printf("%s\n", angleIsGood ? "Angle is good" : "Angle is NOT GOOD");
    printf("------------------------------------------\n");
  }

  /* press X button, Blue Button, to apply gains from webdash.  This can
   * be replaced with your favorite means of changing gains. */
  if (oi->updateGains) {
    UpdateGains();
  }

  /* my right side motors need to drive negative to move robot forward */
  if (oi->userWantsToGoStraight) {
    if (oi->halfPower) {  // Cut the power in half
      left /= 2.0;
      right /= 2.0;
    }
    m_FrontLeftMotor.Set(ControlMode::PercentOutput, left);
    m_RearLeftMotor.Set(ControlMode::PercentOutput, left);
    m_FrontRightMotor.Set(ControlMode::PercentOutput, -1. * right);
    m_RearRightMotor.Set(ControlMode::PercentOutput, -1. * right);
  } else if (oi->fieldCentric) {
    if (oi->halfPower) {
      m_robotDrive.DriveCartesian(oi->x / 2.0, oi->y / 2.0, oi->rotate / 2.0,
                                  currentAngle);
    } else {
      m_robotDrive.DriveCartesian(oi->x, oi->y, oi->rotate, currentAngle);
    }
  }

#else    // If the pigeon isn't enabled
  if (oi->halfPower) {
    m_robotDrive.DriveCartesian(oi->x / 2.0, oi->y / 2.0, oi->rotate / 2.0);
  } else {
    m_robotDrive.DriveCartesian(oi->x, oi->y, oi->rotate);
  }
#endif
}

Mobility* Mobility::getInstance() {
  if (INSTANCE == nullptr) {
    INSTANCE = new Mobility();
  }
  return INSTANCE;
}