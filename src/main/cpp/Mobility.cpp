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
}

void Mobility::process() {
  m_robotDrive.FeedWatchdog();
  if (oi->halfPower) {
    m_robotDrive.DriveCartesian(oi->x / 2.0, oi->y / 2.0, oi->rotate / 2.0);
  } else {
    m_robotDrive.DriveCartesian(oi->x, oi->y, oi->rotate);
  }
}

Mobility* Mobility::getInstance() {
  if (INSTANCE == nullptr) {
    INSTANCE = new Mobility();
  }
  return INSTANCE;
}