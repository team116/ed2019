/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

void Robot::RobotInit() {
  double currentComp;
  bool enabled;
  bool pressureSW;

  // Get the OI instance
  try {
    oi = OI::getInstance();
  } catch (std::exception &e) {
    frc::DriverStation::ReportError("Error initializing OI object");
    frc::DriverStation::ReportError(e.what());
  }

  // Get the LiftEndEffector instance
  try {
    lift = LiftEndEffector::getInstance();
  } catch (std::exception &e) {
    frc::DriverStation::ReportError("Error initializing Lift object");
    frc::DriverStation::ReportError(e.what());
  }

  // Get the TipperEndEffector instance
  try {
    tipper = TipperEndEffector::getInstance();
  } catch (std::exception &e) {
    frc::DriverStation::ReportError("Error initializing Lift object");
    frc::DriverStation::ReportError(e.what());
  }

  // Get the CargoEndEffector instance
  try {
    cargo = CargoEndEffector::getInstance();
  } catch (std::exception &e) {
    frc::DriverStation::ReportError("Error initializing Lift object");
    frc::DriverStation::ReportError(e.what());
  }

  // Camera
  try {
    driverCamera = USBCamera::getInstance();
  } catch (std::exception &e) {
    frc::DriverStation::ReportError("Error initializing USB Camera object");
    frc::DriverStation::ReportError(e.what());
  }

  // Mobility
  try {
    mobility = Mobility::getInstance();
  } catch (std::exception &e) {
    frc::DriverStation::ReportError("Error initializing Mobility object");
    frc::DriverStation::ReportError(e.what());
  }

  oi->m_chooser.AddOption("Left", oi->Pos::LEFT);
  oi->m_chooser.AddOption("Center", oi->Pos::CENTER);
  oi->m_chooser.AddOption("Right", oi->Pos::RIGHT);
  oi->m_chooser.SetDefaultOption("Left", oi->Pos::LEFT);

  frc::SmartDashboard::PutData("Play", &oi->m_chooser);

  oi->m_destination.AddOption("Teleop", oi->Dest::TELEOP);
  oi->m_destination.AddOption("Do Not Move", oi->Dest::DONOTHING);
  oi->m_destination.AddOption("Front Cargo", oi->Dest::FRONTCARGO);
  oi->m_destination.AddOption("Right Cargo", oi->Dest::RIGHTCARGO);
  oi->m_destination.AddOption("Left Cargo", oi->Dest::LEFTCARGO);
  oi->m_destination.AddOption("Right Rocket", oi->Dest::RIGHTROCKET);
  oi->m_destination.AddOption("Left Rocket", oi->Dest::LEFTROCKET);
  oi->m_destination.SetDefaultOption("Teleop", oi->Dest::TELEOP);

  frc::SmartDashboard::PutData("Destination", &oi->m_destination);
  // Enable the closed loop compressor
  Robot::compress->SetClosedLoopControl(true);
  enabled = compress->Enabled();
  pressureSW = compress->GetPressureSwitchValue();
  currentComp = compress->GetCompressorCurrent();

  printf(" %d  %d  %f", enabled, pressureSW, currentComp);

}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  oi->startPosition = oi->m_chooser.GetSelected();
  switch (oi->startPosition) {
    case OI::Pos::LEFT:
      printf("Left Selected\n");
      break;
    case OI::Pos::CENTER:
      printf("Center Selected\n");
      break;
    case OI::Pos::RIGHT:
      printf("Right Selected\n");
      break;
    default:
      printf("Default Selected\n");
      break;
        Robot::compress->SetClosedLoopControl(true);
  }

  oi->destination = oi->m_destination.GetSelected();
  switch (oi->destination) {
    case OI::Dest::TELEOP:
      printf("Teleop Selected\n");
      break;
    case OI::Dest::DONOTHING:
      printf("Do Not Move Selected\n");
      break;
    case OI::Dest::FRONTCARGO:
      printf("Front Cargo Selected\n");
      break;
    case OI::Dest::RIGHTCARGO:
      printf("Right Cargo Selected\n");
      break;
    case OI::Dest::LEFTCARGO:
      printf("Left Cargo Selected\n");
      break;
    case OI::Dest::RIGHTROCKET:
      printf("Right Rocket Selected\n");
      break;
    case OI::Dest::LEFTROCKET:
      printf("Left Rocket Selected\n");
      break;
    default:
      printf("Default Selected\n");
      break;
  }

  try {
    oi->process();
  } catch (std::exception &e) {
    printf("Error in AutonomousInit\n%s", e.what());
  }
}

void Robot::AutonomousPeriodic() {
  switch (oi->destination) {
    case OI::Dest::TELEOP:
      // read the joystick
      try {
        oi->process();
      } catch (std::exception &e) {
        printf("Error in TeleopPeriodic\n%s", e.what());
      }
      try {
        mobility->process();
      } catch (std::exception &e) {
        printf("Error in TeleopPeriodic\n%s", e.what());
      }
      break;
    case OI::Dest::DONOTHING:
      break;
    case OI::Dest::FRONTCARGO:
      break;
    case OI::Dest::RIGHTCARGO:
      break;
    case OI::Dest::LEFTCARGO:
      break;
    case OI::Dest::RIGHTROCKET:
      break;
    case OI::Dest::LEFTROCKET:
      break;
    default:
      printf("Default Selected\n");
      break;
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
    Robot::compress->SetClosedLoopControl(true);
  while ((Robot::ds.IsOperatorControl()) && (Robot::ds.IsEnabled())) {
    try {
      oi->process();
    } catch (std::exception &e) {
      printf("Error in OI -- TeleopPeriodic\n%s", e.what());
    }

    try {
      mobility->process();
    } catch (std::exception &e) {
      printf("Error in Mobility -- TeleopPeriodic\n%s", e.what());
    }
  }
  if (!Robot::ds.IsEnabled()) {
    // Disable the closed loop compressor
    Robot::compress->SetClosedLoopControl(false);
  }
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
