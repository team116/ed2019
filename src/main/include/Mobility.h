/**
 * Mobility.h
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#ifndef SRC_Mobility_H_
#define SRC_Mobility_H_
#include <frc/drive/MecanumDrive.h>
#include <Ports.h>
#include <ctre/Phoenix.h>
#include <OI.h>

class Mobility {
 public:
  void process();
  static Mobility* getInstance();

  // CAN-based Motor Controllers
#ifdef EDV21
  WPI_VictorSPX m_FrontLeftMotor{RobotPorts::kFrontLeftChannel};
  WPI_VictorSPX m_RearLeftMotor{RobotPorts::kRearLeftChannel};
  WPI_VictorSPX m_FrontRightMotor{RobotPorts::kFrontRightChannel};
  WPI_VictorSPX m_RearRightMotor{RobotPorts::kRearRightChannel};
#else
  WPI_TalonSRX m_FrontLeftMotor{RobotPorts::kFrontLeftChannel};
  WPI_TalonSRX m_RearLeftMotor{RobotPorts::kRearLeftChannel};
  WPI_TalonSRX m_FrontRightMotor{RobotPorts::kFrontRightChannel};
  WPI_TalonSRX m_RearRightMotor{RobotPorts::kRearRightChannel};
#endif

#ifdef HASPIGEONIMU
  PigeonIMU *pigeon= new PigeonIMU(RobotPorts::kPigeonChannel);
  enum {
    GoStraightOff,
    GoStraightWithPidgeon,
    GoStraightSameThrottle
  } goStraight = GoStraightOff;
  /* Some gains for heading servo,
   * these were tweaked by using the web-based config (CAN Talon) and
   * pressing gamepad button 6 to load them.
   */
  double kPgain = 0.04;   /* percent throttle per degree of error */
  double kDgain = 0.0004; /* percent throttle per angular velocity dps */
  double kMaxCorrectionRatio =
      0.30; /* cap corrective turning throttle to 30 percent of forward throttle */
  /** holds the current angle to servo to */
  double targetAngle = 0;
  /** count loops to print every second or so */
  int _printLoops = 0;
  
#endif

      // Mecanum Drive Robot Declaration
      frc::MecanumDrive m_robotDrive{m_FrontLeftMotor, m_RearLeftMotor, m_FrontRightMotor,
                                     m_RearRightMotor};

 private:
  Mobility();
  OI *oi;

  static Mobility* INSTANCE;
};

#endif /* SRC_Mobility_H_ */