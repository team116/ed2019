/**
 * OI.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#include <CargoEndEffector.h>
#include <HatchEndEffector.h>
#include <LiftEndEffector.h>
#include <OI.h>
#include <Ports.h>
#include <TipperEndEffector.h>
#include <frc/DriverStation.h>
#include <math.h>
#include <ctre/Phoenix.h>

OI *OI::INSTANCE = nullptr;

OI::OI() {
  // put initialization code into the constructor
  xbox0 = new frc::XboxController(OIPorts::kXboxChannel);
  buttonBox1 = new frc::Joystick(OIPorts::kJoystickChannel1);
  buttonBox2 = new frc::Joystick(OIPorts::kJoystickChannel2);

  // Get the LiftEndEffector instance
  try {
    OI::lift = LiftEndEffector::getInstance();
  } catch (std::exception &e) {
    frc::DriverStation::ReportError("Error initializing Lift object");
    frc::DriverStation::ReportError(e.what());
  }

  // Get the HatchEndEffector instance
  try {
    OI::hatch = HatchEndEffector::getInstance();
  } catch (std::exception &e) {
    frc::DriverStation::ReportError("Error initializing Lift object");
    frc::DriverStation::ReportError(e.what());
  }

  // Get the TipperEndEffector instance
  try {
    OI::tipper = TipperEndEffector::getInstance();
  } catch (std::exception &e) {
    frc::DriverStation::ReportError("Error initializing Lift object");
    frc::DriverStation::ReportError(e.what());
  }

  // Get the CargoEndEffector instance
  try {
    OI::cargo = CargoEndEffector::getInstance();
  } catch (std::exception &e) {
    frc::DriverStation::ReportError("Error initializing Lift object");
    frc::DriverStation::ReportError(e.what());
  }  
}

void OI::process() {
  double tempX, tempY, tempRotate, rollerSpeed;

  // Read the Xbox Controller inputs
  tempX = xbox0->GetX(
      frc::GenericHID::JoystickHand::kRightHand);  // XBox Righthand joystick
  tempY = -(xbox0->GetY(
      frc::GenericHID::JoystickHand::kRightHand));  // XBox Righthand Joystick
  tempRotate = xbox0->GetX(
      frc::GenericHID::JoystickHand::kLeftHand);  // XBox Lefthand  joystick
  // Cube them to shape the curve while maintaining the sign
  OI::x = tempX * tempX * tempX;                      // pow(tempX,3);
  OI::y = tempY * tempY * tempY;                      // pow(tempY,3);
  OI::rotate = tempRotate * tempRotate * tempRotate;  // pow(tempRotate,3)

  // Process the buttons

  // Deal with disabled sensors

  if (buttonBox1->GetRawButton(OIPorts::kSensor1Enable)) {
    OI::enableSensor1 = true;
  } else {
    OI::enableSensor1 = false;
  }
  if (buttonBox1->GetRawButton(OIPorts::kSensor2Enable)) {
    OI::enableSensor2 = true;
  } else {
    OI::enableSensor2 = false;
  }
  if (buttonBox1->GetRawButton(OIPorts::kSensor3Enable)) {
    OI::enableSensor3 = true;
  } else {
    OI::enableSensor3 = false;
  }
  if (buttonBox1->GetRawButton(OIPorts::kSensor4Enable)) {
    OI::enableSensor4 = true;
  } else {
    OI::enableSensor4 = false;
  }
  if (buttonBox1->GetRawButton(OIPorts::kSensor5Enable)) {
    OI::enableSensor5 = true;
  } else {
    OI::enableSensor5 = false;
  }

  // Deal with selecting cargo bays vs. rocket lifter positions
  if (buttonBox1->GetRawButton(OIPorts::kCargoBay)) {
    OI::selectCargoBayPos = true;
  } else {
    OI::selectCargoBayPos = false;
  }

  // take lifter to the bottom
  if (buttonBox1->GetRawButton(OIPorts::kLifterBottom)) {
    OI::selectBottomPos = true;
  } else {
    OI::selectBottomPos = false;
  }

  // take lifter to the bottom
  if (buttonBox1->GetRawButton(OIPorts::kRobotTipOver)) {
    OI::robotTip = true;
    OI::tipper->tipDeploy();
  } else {
    OI::robotTip = false;
    OI::tipper->tipRetract();
  }

  // take lifter to the rocket bottom
  if (buttonBox1->GetRawButton(OIPorts::kRocketBottomPos)) {
    OI::selectRocketBottomPos = true;
  } else {
    OI::selectRocketBottomPos = false;
  }

  // take lifter to the rocket mid
  if (buttonBox1->GetRawButton(OIPorts::kRocketMidPos)) {
    OI::selectRocketMidPos = true;
  } else {
    OI::selectRocketMidPos = false;
  }

  // take lifter to the rocket top
  if (buttonBox1->GetRawButton(OIPorts::kRocketTopPos)) {
    OI::selectRocketTopPos = true;
  } else {
    OI::selectRocketTopPos = false;
  }

  // take lifter to the rocket top
  if (buttonBox1->GetRawButton(OIPorts::kRobotClimb)) {
    OI::robotClimb = true;
    tipper->tipClimb(0.5);
  } else {
    tipper->tipClimb(0.0);
    OI::robotClimb = false;
  }

  // Move lifter up
  if (buttonBox2->GetRawButton(OIPorts::kLifterUp)) {
    OI::moveLifterUp = true;
    OI::moveLifterDown = false;
  } else {
    OI::moveLifterUp = false;
  }


  // Deploy Intake
  if (buttonBox2->GetRawButton(OIPorts::kRollerDeploy)) {
    OI::intakeDeploy = true;
    OI::cargo->intakeDeploy();
  } else {
    OI::intakeDeploy = false;
    OI::cargo->intakeRetract();
  }

  // Deploy Hatch
  if (buttonBox2->GetRawButton(OIPorts::kHatchDeploy)) {
    OI::hatchDeploy = true;
    OI::hatch->hatchDeploy();
  } else {
    OI::hatchDeploy = false;
    OI::hatch->hatchRetract();
  }

  // Roller Direction IN
  if (buttonBox2->GetRawButton(OIPorts::kCargoIn)) {
    OI::rollerIntake = true;
    OI::rollerEject = false;
    rollerSpeed = buttonBox2->GetX();
    OI::cargo->intakeMovement(CargoEndEffector::Direction::INTAKE, rollerSpeed);
  }

  if (buttonBox2->GetRawButton(OIPorts::kCargoOut)) {
    OI::rollerEject = true;
    OI::rollerIntake = false;
    rollerSpeed = buttonBox2->GetX();
    OI::cargo->intakeMovement(CargoEndEffector::Direction::INTAKE, rollerSpeed);
  }

  if (!(buttonBox2->GetRawButton(OIPorts::kCargoOut)) &&
      !(buttonBox2->GetRawButton(OIPorts::kCargoIn))) {
    OI::rollerEject = false;
    OI::rollerIntake = false;
    rollerSpeed = buttonBox2->GetX();
    OI::cargo->intakeMovement(CargoEndEffector::Direction::OFF, rollerSpeed);
  }

    // Move lifter down
  if (buttonBox2->GetRawButton(OIPorts::kLifterDown)) {
    OI::moveLifterDown = true;
    OI::moveLifterUp = false;
  } else {
    OI::moveLifterDown = false;
  }

  // Alternate Move lifter up Xbox Y
  if (xbox0->GetRawButton(OIPorts::kXboxYButton)) {
    OI::moveLifterUp = true;
    OI::moveLifterDown = false;
  } else {
    OI::moveLifterUp = false;
  }


  // Alternate Move lifter down on Xbox A
  if (xbox0->GetRawButton(OIPorts::kXboxAButton)) {
    OI::moveLifterDown = true;
    OI::moveLifterUp = false;
  } else {
    OI::moveLifterDown = false;
  }
}

OI *OI::getInstance() {
  if (INSTANCE == nullptr) {
    INSTANCE = new OI();
  }
  return INSTANCE;
}
