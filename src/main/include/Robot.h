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
#include <cameraserver/CameraServer.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include <frc/GenericHID.h>
#include <ctre/Phoenix.h>
#include <frc/DriverStation.h>
#include <frc/MotorSafety.h>
#include <frc/Compressor.h>
#include <Ports.h>
#include <OI.h>
#include <CargoEndEffector.h>
#include <HatchEndEffector.h>
#include <LiftEndEffector.h>
#include <TipperEndEffector.h>
#include <Mobility.h>
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
  frc::Compressor *compress = new frc::Compressor(PCM0Ports::kPCM0CANID);
  frc::DriverStation&  ds = frc::DriverStation::GetInstance();


private:
  // ========================== Device Instances =============================

  // Instances
  OI *oi;
  LiftEndEffector *lift;
  CargoEndEffector *cargo;
  HatchEndEffector *hatch;
  TipperEndEffector *tipper;
  USBCamera *driverCamera;
  Mobility *mobility;

};
