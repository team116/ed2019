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
#ifdef HASPIGEONIMU  // Do we have the pigeon IMU?
  userWantsToGoStraight = false;
  fieldCentric = false;
  updateGains = false;
#endif
}

void OI::upOrDown(LiftEndEffector::liftPosition currentPos,
                  LiftEndEffector::liftPosition newPos) {
  int numPlaces;

  if (currentPos > newPos) {  // Moving down
    numPlaces = currentPos - newPos;
    lift->liftDown(numPlaces);
  }
  if (currentPos < newPos) {  // Moving up
    numPlaces = newPos - currentPos;
    lift->liftUp(numPlaces);
  }
}

//*************************************  Ball intake  ********************************
void OI::processRoller(int buttonBox2Buttons) {
  volatile double rollerSpeed;
  // Deploy Intake
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel2, OIPorts::kRollerDeploy)) {
    OI::intakeDeploy = true;
    OI::cargo->intakeDeploy();
  }

  if (ds.GetStickButtonReleased(OIPorts::kJoystickChannel2, OIPorts::kRollerDeploy)) {
    OI::intakeDeploy = false;
    OI::cargo->intakeRetract();
  }

  // The control ranges from -1 to 1.  The negatives would be backwards
  // So, add 1 to it to eliminate the negatives and square it to scale
  rollerSpeed = OI::buttonBox2->GetX() + 1.0;  // Get speed from rotary switch
  if (rollerSpeed > 1.0) {
    rollerSpeed = 1.0;
  }
  rollerSpeed = rollerSpeed * rollerSpeed;

  // Roller Direction IN
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel2, OIPorts::kCargoIn)) {
    OI::rollerIntake = true;
    OI::rollerEject = false;
    OI::cargo->intakeMovement(CargoEndEffector::Direction::INTAKE, rollerSpeed);
  }

  // Roller direction Out
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel2, OIPorts::kCargoOut)) {
    OI::rollerEject = true;
    OI::rollerIntake = false;
    OI::cargo->intakeMovement(CargoEndEffector::Direction::EJECT, rollerSpeed);
  }

  // Stop roller
  if (!(buttonBox2Buttons & (1 << (OIPorts::kCargoIn - 1))) &&
      !(buttonBox2Buttons & (1 << (OIPorts::kCargoOut - 1)))) {
    OI::rollerEject = false;
    OI::rollerIntake = false;
    OI::cargo->intakeMovement(CargoEndEffector::Direction::OFF, 0.0);
  }
}
//********************************** END Ball intake  ********************************

//******************************** Lifter Related  **********************************
void OI::processLifter() {
  // take lifter to the bottom
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel1, OIPorts::kLifterBottom)) {
    if (!(OI::disableLiftSensor)) {
      OI::selectBottomPos = true;
      lift->bottomPos(lift->liftPos);
    }
  }

  // Take lifter to the cargo position
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel1, OIPorts::kCargoBay)) {
    if (!(OI::disableLiftSensor)) {
      OI::selectCargoBayPos = true;
      upOrDown(lift->liftPos, LiftEndEffector::liftPosition::RKTBTMCARGO);
    }
  }

  // take lifter to the rocket bottom for Cargo or Hatches
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel1, OIPorts::kRocketBottomPos)) {
    // use OI::intakeDeploy = true to select rocket positions
    if (!(OI::disableLiftSensor)) {
      OI::selectRocketBottomPos = true;
      if (OI::intakeDeploy) {  // we're dealing with hatches
        upOrDown(lift->liftPos, LiftEndEffector::liftPosition::LOADER);
      } else {
        upOrDown(lift->liftPos, LiftEndEffector::liftPosition::RKTBTMCARGO);
      }
    } else {
      printf("Lift Sensor Disabled!");
    }
  }

  // take lifter to the rocket mid for Cargo or Hatches
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel1, OIPorts::kRocketMidPos)) {
    // use OI::intakeDeploy = true to select rocket positions
    if (!(OI::disableLiftSensor)) {
      OI::selectRocketMidPos = true;
      if (OI::intakeDeploy) {  // we're dealing with hatches
        upOrDown(lift->liftPos, LiftEndEffector::liftPosition::RKTMIDHATCH);
      } else {
        upOrDown(lift->liftPos, LiftEndEffector::liftPosition::RKTMIDCARGO);
      }
    } else {
      printf("Lift Sensor Disabled!");
    }
  }

  // take lifter to the rocket top for Cargo or Hatches
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel1, OIPorts::kRocketTopPos)) {
    // use OI::intakeDeploy = true to select rocket positions
    if (!OI::disableLiftSensor) {
      OI::selectRocketTopPos = true;
      if (OI::intakeDeploy) {  // we're dealing with hatches
        upOrDown(lift->liftPos, LiftEndEffector::liftPosition::RKTTOPHATCH);
      } else {
        upOrDown(lift->liftPos, LiftEndEffector::liftPosition::RKTTOPCARGO);
      }
    } else {
      printf("Lift Sensor Disabled!");
    }
  }
}
//**************************** END Lifter Related  **********************************

//****************************** Elevator Related  **********************************
void OI::processElevator() {
  volatile double elevatorY = 0.0;
  // Use the Big Red Joystick for the Elevator
  elevatorY = ds.GetStickAxis(OIPorts::kJoystickChannel1, OIPorts::kJoy1YAxis);

  // Going up
  if (elevatorY < -0.2) {
    // Move up
    tipper->tipLower(1.0);
  }

  // Going down
  if (elevatorY > 0.2) {
    // Move down
    tipper->tipClimb(1.0, OI::disableTipperSensor);
  }

  // stop the elevator motor
  if ((elevatorY < 0.2) && (elevatorY > -0.2)) {
    tipper->tipStop();
  }
}
//*************************** END Elevator Related  **********************************

//****************************** Hatch Related  **********************************
void OI::processHatch() {
  // Deploy Hatch
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel2, OIPorts::kHatchDeploy)) {
    //  if (buttonBox2Buttons & (1 << (OIPorts::kHatchDeploy - 1))) {
    if (!OI::hatchDeploy) {
      printf("Deployed\n");
      OI::hatch->hatchDeploy();
      OI::hatchDeploy = true;
    }
  }

  if (ds.GetStickButtonReleased(OIPorts::kJoystickChannel2, OIPorts::kHatchDeploy)) {
    printf("retract\n");
    OI::hatchDeploy = false;
    OI::hatch->hatchRetract();
  }
}
//************************** END Hatch Related  **********************************

//********************************** Robot Tipper  ***********************************
void OI::processTipper() {

  if (ds.GetStickButton(OIPorts::kJoystickChannel1, OIPorts::kRobotTipOver)) {
    OI::robotTip = true;
    OI::tipper->tipDeploy();
    printf("Tipper Deployed\n");
  }

  if (ds.GetStickButtonReleased(OIPorts::kJoystickChannel1, OIPorts::kRobotTipOver)) {
    OI::robotTip = false;
    OI::tipper->tipRetract();
    printf("Tipper Retract\n");
  }
}
//******************************* END Robot Tipper  *********************************

//******************************* Manual Lift Code  **********************************
void OI::processManualLift(int buttonBox1Buttons, int buttonBox2Buttons) {
  // Move lifter up
  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel2, OIPorts::kLifterUp)) {
    OI::moveLifterUp = true;
    OI::moveLifterDown = false;
    lift->manualLiftUp();
  }

  if (ds.GetStickButtonReleased(OIPorts::kJoystickChannel2, OIPorts::kLifterUp)) {
    OI::moveLifterUp = false;
    OI::moveLifterDown = false;
    lift->manualLiftStop();
  }

  if (ds.GetStickButtonPressed(OIPorts::kJoystickChannel2, OIPorts::kLifterDown)) {
    OI::moveLifterUp = true;
    OI::moveLifterDown = false;
    lift->manualLiftDown(disableBottomSensor);
  }

  if (ds.GetStickButtonReleased(OIPorts::kJoystickChannel2, OIPorts::kLifterDown)) {
    OI::moveLifterUp = false;
    OI::moveLifterDown = false;
    lift->manualLiftStop();
  }

  // Alternate Move lifter up Xbox Y
  if (ds.GetStickButtonPressed(OIPorts::kXboxChannel, OIPorts::kXboxYButton)) {
    OI::moveLifterUp = true;
    OI::moveLifterDown = false;
    lift->manualLiftUp();
  }

  if (ds.GetStickButtonReleased(OIPorts::kXboxChannel, OIPorts::kXboxYButton)) {
    OI::moveLifterUp = false;
    OI::moveLifterDown = false;
    lift->manualLiftStop();
  }

  // Alternate Move lifter down on Xbox A
  if (ds.GetStickButtonPressed(OIPorts::kXboxChannel, OIPorts::kXboxAButton)) {
    OI::moveLifterDown = true;
    OI::moveLifterUp = false;
    lift->manualLiftDown(disableBottomSensor);
  }

  if (ds.GetStickButtonReleased(OIPorts::kXboxChannel, OIPorts::kXboxAButton)) {
    OI::moveLifterUp = false;
    OI::moveLifterDown = false;
    lift->manualLiftStop();
  }
}
//*************************** END Manual Lift Code  **********************************

void OI::process() {
  volatile double tempX, tempY, tempRotate;
  volatile double elevatorY = 0.0;
  volatile double liftY = 0.0;
  volatile int xboxButtons = 0;
  volatile int buttonBox1Buttons = 0;
  volatile int buttonBox2Buttons = 0;

  //**************************  Driver JoySticks ***************************************
  // Read the Xbox Controller inputs
  tempX =
      xbox0->GetX(frc::GenericHID::JoystickHand::kLeftHand);  // XBox Lefthand joystick
  tempY =
      -(xbox0->GetY(frc::GenericHID::JoystickHand::kLeftHand));  // XBox Lefthand Joystick
  tempRotate =
      xbox0->GetX(frc::GenericHID::JoystickHand::kRightHand);  // XBox Righthand  joystick
  // Cube them to shape the curve while maintaining the sign
  OI::x = tempX * tempX * tempX;                      // pow(tempX,3);
  OI::y = tempY * tempY * tempY;                      // pow(tempY,3);
  OI::rotate = tempRotate * tempRotate * tempRotate;  // pow(tempRotate,3)

  //********************** End Driver JoySticks ***************************************

  // Get the button status
  // We do this because a series of getRawButton calls is taking more time than
  // the 20ms for some reason
  //
  xboxButtons = ds.GetStickButtons(OIPorts::kXboxChannel);
  buttonBox1Buttons = ds.GetStickButtons(OIPorts::kJoystickChannel1);
  buttonBox2Buttons = ds.GetStickButtons(OIPorts::kJoystickChannel2);

  //**************************  Adjust Power if Pressed ********************************
  if (xboxButtons & (1 << (OIPorts::kXboxRightBumperButton - 1))) {
    OI::halfPower = true;
  } else {
    OI::halfPower = false;
    // once released we don't scale
  }
  //************************ End Adjust Power if Pressed ********************************

  //**************************  Drive straight and field centric ********************************
  // Add code for Drive Straight and Field Centric
#ifdef HASPIGEONIMU  // Do we have the pigeon IMU?
  // Left bumper says to go straight
  if (xboxButtons & (1 << (OIPorts::kXboxLeftBumperButton - 1))) {
    OI::userWantsToGoStraight = true;
  } else {
    OI::userWantsToGoStraight = false;
  }

  // Option to update the Gains on the turn
  if (xboxButtons & (1 << (OIPorts::kXboxXButton - 1))) {
    OI::updateGains = true;
  } else {
    OI::updateGains = false;
  }
#endif

  // Is the field centric switch set?
  OI::fieldCentric =
      (buttonBox1Buttons & (1 << (OIPorts::kFieldCentricMode - 1)));  // 5 bit
  if (OI::fieldCentric) {
#ifdef HASPIGEONIMU  // Do we have the pigeon IMU?
    frc::SmartDashboard::PutString("Orientation", "Field-Centric");
#else
    frc::SmartDashboard::PutString("Orientation", "Robot-Centric");
#endif
  } else {
    frc::SmartDashboard::PutString("Orientation", "Robot-Centric");
  }
  //****************** End Drive straight and field centric ****************************


  //***********************  Check for Disabled Sensors ********************************

  // Reset Switch sense
  OI::disableBottomSensor = false;
  OI::disableLiftSensor = false;
  OI::disableCargoSensor = false;
  OI::disableTipperSensor = false;

  if (buttonBox1Buttons & 0xf) {  // are any of the disable sensors on?
    // Physically on OI box, up is on (0) and down if off (1)
    // The answer should be enabled (up -- on=0 bit) if sensors are working
    // This uses an ugly assignment with knowledge that the bool type is
    // actually an int under the hood
    OI::disableBottomSensor = (buttonBox1Buttons & 0x1);  // 1 bit
    OI::disableLiftSensor = (buttonBox1Buttons & 0x2);    // 2 bit
    OI::disableCargoSensor = (buttonBox1Buttons & 0x4);   // 3 bit
    OI::disableTipperSensor = (buttonBox1Buttons & 0x8);  // 4 bit
  }

  //*********************** END Check for Disabled Sensors *****************************

  // Deal with cargo intake
  OI::processRoller(buttonBox2Buttons);

  // Deal with lifter
  OI::processLifter();

  // Deal with the Elevator
  OI::processElevator();

  // Deal with the Hatch
  OI::processHatch();

  // Deal with the Tipper
  OI::processTipper();

  // Deal with Manual Override on the Lift
  OI::processManualLift(buttonBox1Buttons, buttonBox2Buttons);
}

OI *OI::getInstance() {
  if (INSTANCE == nullptr) {
    INSTANCE = new OI();
  }
  return INSTANCE;
}
