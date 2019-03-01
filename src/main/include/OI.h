/**
 * OI.h
 *
 *  Created on: Feb 11, 2019
 *      Author: Mike A.
 */
#ifndef SRC_OI_H_
#define SRC_OI_H_

#include <Ports.h>
#include <ctre/Phoenix.h>
#include <frc/GenericHID.h>
#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/DriverStation.h>
#include <CargoEndEffector.h>
#include <HatchEndEffector.h>
#include <LiftEndEffector.h>
#include <TipperEndEffector.h>
#include <USBCamera.h>


class OI {
 public:
  static OI *getInstance();
  void process();

  frc::XboxController *xbox0;
  frc::Joystick *buttonBox1;
  frc::Joystick *buttonBox2;
  frc::Joystick *buttonBox3;

  // Disabled sensor state variables
  bool disableBottomSensor = false;
  bool disableLiftSensor   = false;
  bool disableCargoSensor  = false;
  bool disableTipperSensor = false;
  bool disableSensor5      = false;

  // Cargo Bay vs. Rocket lifter state flags
  bool selectCargoBayPos      = false; // initial state is off
  bool selectBottomPos        = false; // initial state is off
  bool selectRocketBottomPos  = false; // initial state is off
  bool selectRocketMidPos     = false; // initial state is off
  bool selectRocketTopPos     = false; // initial state is off

  // Hatch deploy
  bool hatchDeploy            = false;

  // Intake Position state variables
  bool intakeDeploy           = false;

  // Intake direction state variables
  bool rollerIntake           = false;
  bool rollerEject            = false;
  bool rollerStop             = true;  // begin with stopped roller

  // climb and tip state variables
  bool robotClimb             = false;
  bool robotTip               = false;

  // Lifter direction override
  bool moveLifterUp           = false;
  bool moveLifterDown         = false;

  // Driver Station related
  double x, y, rotate;  // Position of joystick inputs

  enum Pos { LEFT, CENTER, RIGHT };
  frc::SendableChooser<Pos> m_chooser;

  enum Dest {
    TELEOP,
    DONOTHING,
    FRONTCARGO,
    RIGHTCARGO,
    LEFTCARGO,
    RIGHTROCKET,
    LEFTROCKET
  };
  frc::SendableChooser<Dest> m_destination;

  Pos startPosition;
  Dest destination;

 private:
  // Instances
  LiftEndEffector *lift;
  CargoEndEffector *cargo;
  HatchEndEffector *hatch;
  TipperEndEffector *tipper;
  USBCamera *driverCamera;
  frc::DriverStation&  ds = frc::DriverStation::GetInstance();


  OI();
  static OI *INSTANCE;
};

#endif /* SRC_OI_H_ */
