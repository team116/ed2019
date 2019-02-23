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

  // Mecanum Drive Robot Declaration
  frc::MecanumDrive m_robotDrive{m_FrontLeftMotor, m_RearLeftMotor,
                                 m_FrontRightMotor, m_RearRightMotor};

 private:
  Mobility();
  OI *oi;
  static Mobility* INSTANCE;
};

#endif /* SRC_Mobility_H_ */