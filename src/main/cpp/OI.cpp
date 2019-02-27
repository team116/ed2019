/**
 * OI.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */

#include <OI.h>
#include <math.h>

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
  volatile double tempX, tempY, tempRotate, rollerSpeed;
  volatile int xboxButtons = 0;
  volatile int buttonBox1Buttons = 0;
  volatile int buttonBox2Buttons = 0;

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

  // Get the button status
  // We do this because a series of getRawButton calls is taking more time than
  // the 20ms for some reason
  //
  xboxButtons = ds.GetStickButtons(OIPorts::kXboxChannel);
  buttonBox1Buttons = ds.GetStickButtons(OIPorts::kJoystickChannel1);
  buttonBox2Buttons = ds.GetStickButtons(OIPorts::kJoystickChannel2);

  // Deal with disabled sensors
  if (buttonBox1Buttons & 0x1f) {  // are any of the disable sensors on?
                                   // The answer should be no for any of them
    // This uses an ugly assignment with knowledge that the bool type is
    // actually an int under the hood
    OI::enableSensor1 = (buttonBox1Buttons & 0x1);   // 1 bit
    OI::enableSensor2 = (buttonBox1Buttons & 0x2);   // 2 bit
    OI::enableSensor3 = (buttonBox1Buttons & 0x4);   // 3 bit
    OI::enableSensor4 = (buttonBox1Buttons & 0x8);   // 4 bit
    OI::enableSensor5 = (buttonBox1Buttons & 0x10);  // 5 bit
  }

  // Deal with selecting cargo bays vs. rocket lifter positions
  OI::selectCargoBayPos = (buttonBox1Buttons & (1 << (OIPorts::kCargoBay - 1)));

  // take lifter to the bottom
  OI::selectBottomPos =
      (buttonBox1Buttons & (1 << (OIPorts::kLifterBottom - 1)));

  // take lifter to the bottom
  if (buttonBox1Buttons & (1 << (OIPorts::kRobotTipOver - 1))) {
    OI::robotTip = true;
    OI::tipper->tipDeploy();
  } else {
    if (OI::robotTip) {  // only retract if the tipper was previously deployed
      OI::robotTip = false;
      OI::tipper->tipRetract();
    }
  }

  // take lifter to the rocket bottom
  OI::selectRocketBottomPos =
      (buttonBox1Buttons & (1 << (OIPorts::kRocketBottomPos - 1)));

  // take lifter to the rocket mid
  OI::selectRocketMidPos =
      (buttonBox1Buttons & (1 << (OIPorts::kRocketMidPos - 1)));

  // take lifter to the rocket top
  OI::selectRocketTopPos =
      (buttonBox1Buttons & (1 << (OIPorts::kRocketTopPos - 1)));

  // Start the climb
  if (buttonBox1Buttons & (1 << (OIPorts::kRobotClimb - 1))) {
    OI::robotClimb = true;
    tipper->tipClimb(0.5);
  } else {
    if (OI::robotClimb) {
      tipper->tipStop();
      OI::robotClimb = false;
    }
  }

  // Move lifter up
  if (buttonBox2Buttons & (1 << (OIPorts::kLifterUp - 1))) {
    OI::moveLifterUp = true;
    OI::moveLifterDown = false;
  } else {
    OI::moveLifterUp = false;
  }
  // Alternate Move lifter up Xbox Y
  if (xboxButtons & (1 << (OIPorts::kXboxYButton - 1))) {
    OI::moveLifterUp = true;
    OI::moveLifterDown = false;
  } else {
    OI::moveLifterUp = false;
  }

  // Move lifter down
  if (buttonBox2Buttons & (1 << (OIPorts::kLifterDown - 1))) {
    OI::moveLifterDown = true;
    OI::moveLifterUp = false;
  } else {
    OI::moveLifterDown = false;
  }

  // Alternate Move lifter down on Xbox A
  if (xboxButtons & (1 << (OIPorts::kXboxAButton - 1))) {
    OI::moveLifterDown = true;
    OI::moveLifterUp = false;
  } else {
    OI::moveLifterDown = false;
  }

  // Deploy Intake
  if (buttonBox2Buttons & (1 << (OIPorts::kRollerDeploy - 1))) {
    OI::intakeDeploy = true;
    OI::cargo->intakeDeploy();
  } else {
    if (OI::intakeDeploy) {  // retract only if previously deployed
      OI::intakeDeploy = false;
      OI::cargo->intakeRetract();
    }
  }

  // Deploy Hatch
  if (buttonBox2Buttons & (1 << (OIPorts::kHatchDeploy - 1))) {
    if (!OI::hatchDeploy) {
      OI::hatch->hatchDeploy();
      OI::hatchDeploy = true;
    }
  } else {
    if (OI::hatchDeploy) {  // retract only if previously deployed
      OI::hatchDeploy = false;
      OI::hatch->hatchRetract();
    }
  }

  // Roller Direction IN
  if (buttonBox2Buttons & (1 << (OIPorts::kCargoIn - 1))) {
    OI::rollerIntake = true;
    OI::rollerEject = false;
    rollerSpeed = buttonBox2->GetX();  // Get speed from rotary switch
    OI::cargo->intakeMovement(CargoEndEffector::Direction::INTAKE, rollerSpeed);
  }

  // Roller direction Out
  if (buttonBox2Buttons & (1 << (OIPorts::kCargoOut - 1))) {
    OI::rollerEject = true;
    OI::rollerIntake = false;
    rollerSpeed = buttonBox2->GetX();  // Get speed from rotary switch
    OI::cargo->intakeMovement(CargoEndEffector::Direction::INTAKE, rollerSpeed);
  }

  // Stop roller
  if (OI::rollerIntake || OI::rollerEject) {
    OI::rollerEject = false;
    OI::rollerIntake = false;
    OI::cargo->intakeMovement(CargoEndEffector::Direction::OFF, 0.0);
  }
}

OI *OI::getInstance() {
  if (INSTANCE == nullptr) {
    INSTANCE = new OI();
  }
  return INSTANCE;
}
