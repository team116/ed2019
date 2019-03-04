/**
 * OI.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */

#include <OI.h>
#include <frc/smartdashboard/SmartDashboard.h>
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

void OI::upOrDown(LiftEndEffector::liftPosition currentPos,
                  LiftEndEffector::liftPosition newPos) {
  int numPlaces;  

//  lift->LiftEndEffector::liftTimer->Reset();

  if (currentPos > newPos) {  // Moving down
    numPlaces = currentPos - newPos;
    lift->liftDown(numPlaces, OI::disableLiftSensor);
  }
  if (currentPos < newPos) {  // Moving up
    numPlaces = newPos - currentPos;
    lift->liftUp(numPlaces, OI::disableLiftSensor);
  }
}

void OI::process() {
  volatile double tempX, tempY, tempRotate, rollerSpeed;
  volatile double elevatorY = 0.0;
  volatile double liftY = 0.0;
  volatile int xboxButtons = 0;
  volatile int buttonBox1Buttons = 0;
  volatile int buttonBox2Buttons = 0;

  // Read the Xbox Controller inputs
  tempX = xbox0->GetX(
      frc::GenericHID::JoystickHand::kLeftHand);  // XBox Lefthand joystick
  tempY = -(xbox0->GetY(
      frc::GenericHID::JoystickHand::kLeftHand));  // XBox Lefthand Joystick
  tempRotate = xbox0->GetX(
      frc::GenericHID::JoystickHand::kRightHand);  // XBox Righthand  joystick
  // Cube them to shape the curve while maintaining the sign
  OI::x = tempX * tempX * tempX;                      // pow(tempX,3);
  OI::y = tempY * tempY * tempY;                      // pow(tempY,3);
  OI::rotate = tempRotate * tempRotate * tempRotate;  // pow(tempRotate,3)
                                                
 
 
  if (ds.GetStickButtonPressed(OIPorts::kXboxChannel,
                               OIPorts::kXboxRightBumperButton)) {
    //  if (buttonBox2Buttons & (1 << (OIPorts::kRollerDeploy - 1))) {
    OI::halfPower = true;  
    printf("Half=T\n");
  }


  if (ds.GetStickButtonReleased(OIPorts::kXboxChannel,
                                OIPorts::kXboxRightBumperButton)) {
    OI::halfPower = false;  
    printf("Half=F\n");
    // once released we don't scale
  }

/*
if (halfPower) {
    OI::x = OI::x / 2.0;            // pow(tempX,3);
    OI::y = OI::y / 2.0;            // pow(tempY,3);
    OI::rotate = OI::rotate / 2.0;  // pow(tempRotate,3)
    printf("Half power %f  %f  %f\n", OI::x, OI::y, OI::rotate);
}
*/

  // Get the button status
  // We do this because a series of getRawButton calls is taking more time than
  // the 20ms for some reason
  //
  xboxButtons = ds.GetStickButtons(OIPorts::kXboxChannel);
  buttonBox1Buttons = ds.GetStickButtons(OIPorts::kJoystickChannel1);
  buttonBox2Buttons = ds.GetStickButtons(OIPorts::kJoystickChannel2);

  // Deal with disabled sensors
  if (buttonBox1Buttons & 0x1f) {  // are any of the disable sensors on?
                                   // Physically on OI box, up is on (0) and down if off (1)
                                   // The answer should be enabled (up -- on=0 bit) if sensors are working
    // This uses an ugly assignment with knowledge that the bool type is
    // actually an int under the hood
    OI::disableBottomSensor = (buttonBox1Buttons & 0x1);  // 1 bit
    OI::disableLiftSensor = (buttonBox1Buttons & 0x2);    // 2 bit
    OI::disableCargoSensor = (buttonBox1Buttons & 0x4);   // 3 bit
    OI::disableTipperSensor = (buttonBox1Buttons & 0x8);  // 4 bit
    OI::disableSensor5 = (buttonBox1Buttons & 0x10);      // 5 bit
  }

  // Deploy Intake
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel2,
                               OIPorts::kRollerDeploy)) {
    //  if (buttonBox2Buttons & (1 << (OIPorts::kRollerDeploy - 1))) {
    OI::intakeDeploy = true;
    OI::cargo->intakeDeploy();
    printf("press Intake out\n");
  }

  if (ds.GetStickButtonReleased(OIPorts::kJoystickChannel2,
                                OIPorts::kRollerDeploy)) {
    printf("release Intake retract\n");
    OI::intakeDeploy = false;
    OI::cargo->intakeRetract();
  }
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel1,
                               OIPorts::kRobotTipOver)) {
    OI::robotTip = true;
    OI::tipper->tipDeploy();
  }

  if (ds.GetStickButtonReleased(OIPorts::kJoystickChannel1,
                                OIPorts::kRobotTipOver)) {
    OI::robotTip = false;
    OI::tipper->tipRetract();
  }

  // Take lifter to the cargo position
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel1,
                               OIPorts::kCargoBay)) {
    OI::selectCargoBayPos = true;
    upOrDown(lift->liftPos, LiftEndEffector::liftPosition::RKTBTMCARGO);
  }

  // take lifter to the bottom
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel1,
                               OIPorts::kLifterBottom)) {
    OI::selectBottomPos = true;
    lift->bottomPos(OI::disableBottomSensor);
  }

  /*
    // take lifter to the rocket bottom
    if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel1,
                                 OIPorts::kRocketBottomPos)) {
      // use OI::intakeDeploy = true to select rocket positions
      OI::selectRocketBottomPos = true;
      if (OI::intakeDeploy) {  // we're dealing with hatches
        upOrDown(lift->liftPos, LiftEndEffector::liftPosition::LOADER);
      } else {
        upOrDown(lift->liftPos, LiftEndEffector::liftPosition::RKTBTMCARGO);
      }
    }

    if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel1,
                                 OIPorts::kRocketMidPos)) {
      // use OI::intakeDeploy = true to select rocket positions
      OI::selectRocketMidPos = true;
      if (OI::intakeDeploy) {  // we're dealing with hatches
        upOrDown(lift->liftPos, LiftEndEffector::liftPosition::RKTMIDHATCH);
      } else {
        upOrDown(lift->liftPos, LiftEndEffector::liftPosition::RKTMIDCARGO);
      }
    }
    */

  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel1,
                               OIPorts::kRocketTopPos)) {
    // use OI::intakeDeploy = true to select rocket positions
    OI::selectRocketTopPos = true;
    if (OI::intakeDeploy) {  // we're dealing with hatches
      upOrDown(lift->liftPos, LiftEndEffector::liftPosition::RKTTOPHATCH);
    } else {
      upOrDown(lift->liftPos, LiftEndEffector::liftPosition::RKTTOPCARGO);
    }
  }

  // Use the Big Red Joystick for the Elevator
  elevatorY = ds.GetStickAxis(OIPorts::kJoystickChannel1, OIPorts::kJoy1YAxis);
  frc::SmartDashboard::PutNumber("Elevator Joystick value", elevatorY);

  // Going up
  if (elevatorY < -0.2) {
    // Move up
    tipper->tipClimb(1.0, OI::disableLiftSensor);
  }

  // Going down
  if (elevatorY > 0.2) {
    // Move down
    tipper->tipLower(1.0);
  }

  // stop the elevator motor
  if ((elevatorY < 0.2) && (elevatorY > -0.2)) {
    tipper->tipStop();
  }

  // Move lifter up
  /*
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel2,
                               OIPorts::kLifterUp)) {
    OI::moveLifterUp = true;
    OI::moveLifterDown = false;
  } else {
    if (OI::moveLifterUp) {
      OI::moveLifterDown = false;
      OI::moveLifterUp = false;
    }
  }
*/
  // Use the Big Red Joystick for the Elevator
//  liftY = ds.GetStickAxis(OIPorts::kJoystickChannel2, OIPorts::kJoy2YAxis);
//  frc::SmartDashboard::PutNumber("Lift Joystick value", liftY);
  // Going up
  /*
    if (liftY < -0.13) {
      // Move up
      OI::moveLifterUp = true;
      lift->manualLiftDown();
    }

    // Going down
    if (liftY > 0.3) {
      // Move down
      lift->manualLiftUp();
    }

    // stop the elevator motor
    if ((liftY < 0.2) && (liftY > -0.08)) {
      lift->manualLiftStop();
    }
  */

  // Alternate Move lifter up Xbox Y
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel1,
                               OIPorts::kRocketBottomPos)) {
    //  if (xboxButtons & (1 << (OIPorts::kXboxYButton - 1))) {
    OI::moveLifterUp = true;
    OI::moveLifterDown = false;
    lift->manualLiftDown();
  }

  if (ds.GetStickButtonReleased(OIPorts::kJoystickChannel1,
                               OIPorts::kRocketBottomPos)) {
    //  if (xboxButtons & (1 << (OIPorts::kXboxYButton - 1))) {
    OI::moveLifterUp = false;
    OI::moveLifterDown = false;
    lift->manualLiftStop();
  }

  // Alternate Move lifter down on Xbox A
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel1,
                               OIPorts::kRocketMidPos)) {
    //  if (xboxButtons & (1 << (OIPorts::kXboxAButton - 1))) {
    OI::moveLifterDown = true;
    OI::moveLifterUp = false;
    lift->manualLiftUp();
  }

  if (ds.GetStickButtonReleased(OIPorts::kJoystickChannel1,
                               OIPorts::kRocketMidPos)) {
    //  if (xboxButtons & (1 << (OIPorts::kXboxYButton - 1))) {
    OI::moveLifterUp = false;
    OI::moveLifterDown = false;
    lift->manualLiftStop();
  }

  // Alternate Move lifter up Xbox Y
  if (ds.GetStickButtonPressed(OIPorts::kXboxChannel, OIPorts::kXboxYButton)) {
    //  if (xboxButtons & (1 << (OIPorts::kXboxYButton - 1))) {
    OI::moveLifterUp = true;
    OI::moveLifterDown = false;
    lift->manualLiftDown();
  }

  if (ds.GetStickButtonReleased(OIPorts::kXboxChannel, OIPorts::kXboxYButton)) {
    //  if (xboxButtons & (1 << (OIPorts::kXboxYButton - 1))) {
    OI::moveLifterUp = false;
    OI::moveLifterDown = false;
    lift->manualLiftStop();
  }

  // Move lifter down'

  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel2,
                               OIPorts::kLifterDown)) {
    //  if (buttonBox2Buttons & (1 << (OIPorts::kLifterDown - 1))) {
    OI::moveLifterDown = true;
    OI::moveLifterUp = false;
    lift->manualLiftUp();
  }

  // Alternate Move lifter down on Xbox A
  if (ds.GetStickButtonPressed(OIPorts::kXboxChannel, OIPorts::kXboxAButton)) {
    //  if (xboxButtons & (1 << (OIPorts::kXboxAButton - 1))) {
    OI::moveLifterDown = true;
    OI::moveLifterUp = false;
    lift->manualLiftDown();
  }

  if (ds.GetStickButtonReleased(OIPorts::kXboxChannel, OIPorts::kXboxAButton)) {
    //  if (xboxButtons & (1 << (OIPorts::kXboxYButton - 1))) {
    OI::moveLifterUp = false;
    OI::moveLifterDown = false;
    lift->manualLiftStop();
  }

  // Deploy Hatch
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel2,
                               OIPorts::kHatchDeploy)) {
    //  if (buttonBox2Buttons & (1 << (OIPorts::kHatchDeploy - 1))) {
    if (!OI::hatchDeploy) {
      printf("Deployed\n");
      OI::hatch->hatchDeploy();
      OI::hatchDeploy = true;
    }
  }

  if (ds.GetStickButtonReleased(OIPorts::kJoystickChannel2,
                                OIPorts::kHatchDeploy)) {
    printf("retract\n");
    OI::hatchDeploy = false;
    OI::hatch->hatchRetract();
  }

  // Roller Direction IN
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel2, OIPorts::kCargoIn)) {
    OI::rollerIntake = true;
    OI::rollerEject = false;
    rollerSpeed = buttonBox2->GetX();  // Get speed from rotary switch
    //    OI::cargo->intakeMovement(CargoEndEffector::Direction::INTAKE,
    //    rollerSpeed);
    OI::cargo->intakeMovement(CargoEndEffector::Direction::INTAKE, 0.9);
  }

  // Roller direction Out
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel2,
                               OIPorts::kCargoOut)) {
    OI::rollerEject = true;
    OI::rollerIntake = false;
    rollerSpeed = buttonBox2->GetX();  // Get speed from rotary switch
    //    OI::cargo->intakeMovement(CargoEndEffector::Direction::EJECT,
    //    rollerSpeed);
    OI::cargo->intakeMovement(CargoEndEffector::Direction::EJECT, 0.9);
  }

  // Stop roller
  if (!(buttonBox2Buttons & (1 << (OIPorts::kCargoIn - 1))) &&
      !(buttonBox2Buttons & (1 << (OIPorts::kCargoOut - 1)))) {
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
