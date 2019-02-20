/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include <frc/GenericHID.h>
#include <ctre/phoenix.h>
#include <frc/DriverStation.h>
#include <frc/MotorSafety.h>
#include <Ports.h>
#include <oi.h>
#include <CargoEndEffector.h>
#include <HatchEndEffector.h>
#include <LiftEndEffector.h>
#include <TipperEndEffector.h>
#include <USBCamera.h>

class Robot : public frc::TimedRobot
{
public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

private:
  // ========================== Device Instances =============================

  // Instances
  OI *oi;
  LiftEndEffector *lift;
  CargoEndEffector *cargo;
  HatchEndEffector *hatch;
  TipperEndEffector *tipper;
  USBCamera *driverCamera;

  // CAN-based Motor Controllers
#ifdef EDV21  
  WPI_VictorSPX m_FrontLeftMotor{RobotPorts::kFrontLeftChannel};
  WPI_VictorSPX m_RearLeftMotor{RobotPorts::kRearLeftChannel};
  WPI_VictorSPX m_FrontRightMotor{RobotPorts::kFrontRightChannel};
  WPI_VictorSPX m_RearRightMotor{RobotPorts::kRearRightChannel};

  WPI_VictorSPX m_BallIntake{RobotPorts::kBallIntakeChannel};
#else
  WPI_TalonSRX m_FrontLeftMotor{RobotPorts::kFrontLeftChannel};
  WPI_TalonSRX m_RearLeftMotor{RobotPorts::kRearLeftChannel};
  WPI_TalonSRX m_FrontRightMotor{RobotPorts::kFrontRightChannel};
  WPI_TalonSRX m_RearRightMotor{RobotPorts::kRearRightChannel};

  WPI_TalonSRX m_BallIntake{RobotPorts::kBallIntakeChannel};
#endif

  // Mecanum Drive Robot Declaration
  frc::MecanumDrive m_robotDrive{m_FrontLeftMotor, m_RearLeftMotor, m_FrontRightMotor, m_RearRightMotor};


  // Joysticks on the OI -- Includes all of the for buttons, etc.
  //  frc::XboxController m_stick{kXboxChannel};
  //  frc::Joystick joy1{kJoystickChannel1};
  //  frc::Joystick joy2{kJoystickChannel2};
  //  frc::Joystick joy3{kJoystickChannel3};
  //  frc::Joystick joy4{kJoystickChannel4};
};
