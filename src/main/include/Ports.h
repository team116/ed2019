/**
 * Ports.h
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#ifndef SRC_PORTS_H_
#define SRC_PORTS_H_

//#define EDV21 1
#undef EDV21

namespace RobotPorts {
// PDP CAN bus ID -- Must be ID 0 for WPILib to be able to read the current
constexpr int kPDPChannel = 0;

// Miscellaneous CAN IDs
constexpr int kCanifierChannel = 6;
constexpr int kPigeonChannel = 9;

// Motor Controllers
constexpr int kFrontLeftChannel  = 1;
constexpr int kRearLeftChannel   = 2;
constexpr int kFrontRightChannel = 3;
constexpr int kRearRightChannel  = 4;
constexpr int kBallIntakeChannel = 14;
constexpr int kLiftChannel       = 15;
constexpr int kTippingChannel    = 16;

// Digital I/O from RoboRIO  --  Be sure the rename these to something more
// meaningful
constexpr int kBottomLimSw     = 0;  
constexpr int kLiftLimSw       = 1;
constexpr int kBallIntakeLimSw = 2;
constexpr int kElevatorLimSw   = 3;
constexpr int kDIOChannel4     = 4;
constexpr int kDIOChannel5     = 5;
constexpr int kDIOChannel6     = 6;
constexpr int kDIOChannel7     = 7;
constexpr int kDIOChannel8     = 8;
constexpr int kDIOChannel9     = 9;
constexpr int kDIOChannel10    = 10;

// Analog Inputs
constexpr int kAIChannel0 = 0;
constexpr int kAIChannel1 = 1;
constexpr int kAIChannel2 = 2;
constexpr int kAIChannel3 = 3;

}  // namespace RobotPorts

namespace PCM0Ports {

// PCM 0 Solenoid Assignments
constexpr int kPCM0CANID              = 10;
constexpr int kPCM0HatchExtend        = 2;
constexpr int kPCM0HatchRetract       = 5;
constexpr int kPCM0CargoIntakeExtend  = 3;
constexpr int kPCM0CargoIntakeRetract = 4;
constexpr int kPCM0Tipper1Extend      = 0;
constexpr int kPCM0Tipper1Retract     = 7;
constexpr int kPCM0Tipper2Extend      = 1;
constexpr int kPCM0Tipper2Retract     = 6;
}  // namespace PCM0Ports

namespace PCM1Ports {
// PCM 1 Solenoid Assignments  -- Maybe not needed
constexpr int kPCM1CANID = 11;
constexpr int kPCM1Channel0 = 0;
constexpr int kPCM1Channel1 = 1;
constexpr int kPCM1Channel2 = 2;
constexpr int kPCM1Channel3 = 3;
constexpr int kPCM1Channel4 = 4;
constexpr int kPCM1Channel5 = 5;
constexpr int kPCM1Channel6 = 6;
constexpr int kPCM1Channel7 = 7;
}  // namespace PCM1Ports

namespace OIPorts {
// Joysticks
constexpr int kXboxChannel = 0;
constexpr int kJoystickChannel1 = 1;
constexpr int kJoystickChannel2 = 2;
constexpr int kJoystickChannel3 = 3;
constexpr int kJoystickChannel4 = 4;

// Buttons on the Xbox
// We don't mess with the D-Pad as that shows up as an Axis (6)

// Analog Axes 
constexpr int kXboxLXAxis            = 0;
constexpr int kXboxLYAxis            = 1;
constexpr int kXboxLTriggerAxis      = 2;  // Only 0-1 does not do negative
constexpr int kXboxRTriggerAxis      = 3;  // Only 0-1 does not do negative
constexpr int kXboxRXAxis            = 4;
constexpr int kXboxRYAxis            = 5;

// Digital buttons
constexpr int kXboxAButton           = 1;  // Lifter down
constexpr int kXboxBButton           = 2;  
constexpr int kXboxXButton           = 3;
constexpr int kXboxYButton           = 4;  // Lifter up
constexpr int kXboxLeftBumperButton  = 5;  // Drive Straight
constexpr int kXboxRightBumperButton = 6;  // Field centric/Robot Centeric
constexpr int kXboxBackButton        = 7;
constexpr int kXboxStartButton       = 8;
constexpr int kXboxLeftJoyButton     = 9;
constexpr int kXboxRightJoyButton    = 10;

// Second external Joystick Interface  -- Digital only USB interface (Generic USB)
constexpr int kSensor1Enable   = 1;   // Map 1
constexpr int kSensor2Enable   = 2;   // Map 2
constexpr int kSensor3Enable   = 3;   // Map 3
constexpr int kSensor4Enable   = 4;   // Map 4
constexpr int kSensor5Enable   = 5;   // Map 5
constexpr int kRobotTipOver    = 6;   // Map 14
constexpr int kRocketTopPos    = 7;   // Map 6
constexpr int kRocketMidPos    = 8;   // Map 12
constexpr int kRocketBottomPos = 9;   // Map 15
constexpr int kCargoBay        = 10;  // Map 13
constexpr int kLifterBottom    = 11;  // Map 16
constexpr int kRobotClimb      = 12;  // Map 7

constexpr int kJoy1XAxis = 1;
constexpr int kJoy1YAxis = 2;
constexpr int kJoy1ZAxis = 3;

// Third external Joystick Interface   -- BU0836LC
constexpr int kLifterUp     = 1;
constexpr int kLifterDown   = 2;
constexpr int kJoy2Button3  = 3;
constexpr int kJoy2Button4  = 4;
constexpr int kJoy2Button5  = 5;
constexpr int kJoy2Button6  = 6;
constexpr int kJoy2Button7  = 7;
constexpr int kJoy2Button8  = 8;
constexpr int kHatchDeploy  = 9;     // Map 11 Hatch Deploy
constexpr int kRollerDeploy = 10;    // Map 10 Roller Deploy
constexpr int kCargoIn      = 11;    // Map 9A
constexpr int kCargoOut     = 12;    // Map 9B

constexpr int kJoy2RollerSpeed = 1;

}  // namespace OIPorts

#endif /* SRC_PORTS_H_ */