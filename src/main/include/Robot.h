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
#include <frc/drive/MecanumDrive.h>
#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include <frc/GenericHID.h>
#include <ctre/phoenix.h>
#include "Ports.h"


class Robot : public frc::TimedRobot {
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

// Driver Station related
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

// CAN-based Motor Controllers
  WPI_TalonSRX m_FrontLeftMotor{kFrontLeftChannel};
  WPI_TalonSRX m_RearLeftMotor{kRearLeftChannel};
  WPI_TalonSRX m_FrontRightMotor{kFrontRightChannel};
  WPI_TalonSRX m_RearRightMotor{kRearRightChannel};

  WPI_TalonSRX m_BallIntake{kBallIntakeChannel};

// Speed Controller Groups for ganging controllers in Tandem 
  //frc::SpeedControllerGroup m_left{m_FrontLeftMotor, m_RearLeftMotor};
  //frc::SpeedControllerGroup m_right{m_FrontRightMotor, m_RearRightMotor};


// Mecanum Drive Robot Declaration
  frc::MecanumDrive m_robotDrive{m_FrontLeftMotor, m_RearLeftMotor, m_FrontRightMotor,m_RearRightMotor};

// Joysticks on the OI -- Includes all of the for buttons, etc.
  frc::XboxController m_stick{kXboxChannel};
  frc::Joystick joy1{kJoystickChannel1};
  frc::Joystick joy2{kJoystickChannel2};
  frc::Joystick joy3{kJoystickChannel3};
  frc::Joystick joy4{kJoystickChannel4};

};
