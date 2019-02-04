/**
 * Ports.h
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#ifndef SRC_PORTS_H_
#define SRC_PORTS_H_

// PDP CAN bus ID -- Must be ID 0 for WPILib to be able to read the current
  static constexpr int kPDPChannel        = 0;

// Miscellaneous CAN IDs
  static constexpr int kCanifierChannel   = 6;
  static constexpr int kPigeonChannel     = 9;

// Motor Controllers
  static constexpr int kFrontLeftChannel  = 1;
  static constexpr int kRearLeftChannel   = 2;
  static constexpr int kFrontRightChannel = 3;
  static constexpr int kRearRightChannel  = 4;
  static constexpr int kBallIntakeChannel = 14;
  static constexpr int kLiftChannel       = 15;
  static constexpr int kTippingChannel    = 16;


// PCM 0 Solenoid Assignments
  static constexpr int kPCM0CANID    = 10;
  static constexpr int kPCM0Channel0 = 0;
  static constexpr int kPCM0Channel1 = 1;
  static constexpr int kPCM0Channel2 = 2;
  static constexpr int kPCM0Channel3 = 3;
  static constexpr int kPCM0Channel4 = 4;
  static constexpr int kPCM0Channel5 = 5;
  static constexpr int kPCM0Channel6 = 6;
  static constexpr int kPCM0Channel7 = 7;

// PCM 1 Solenoid Assignments  -- Maybe not needed
  static constexpr int kPCM1CANID    = 11;
  static constexpr int kPCM1Channel0 = 0;
  static constexpr int kPCM1Channel1 = 1;
  static constexpr int kPCM1Channel2 = 2;
  static constexpr int kPCM1Channel3 = 3;
  static constexpr int kPCM1Channel4 = 4;
  static constexpr int kPCM1Channel5 = 5;
  static constexpr int kPCM1Channel6 = 6;
  static constexpr int kPCM1Channel7 = 7;
 
// Joysticks
  static constexpr int kXboxChannel       = 0;
  static constexpr int kJoystickChannel1  = 1;
  static constexpr int kJoystickChannel2  = 2;
  static constexpr int kJoystickChannel3  = 3;
  static constexpr int kJoystickChannel4  = 4;

// Digital I/O from RoboRIO  --  Be sure the rename these to something more meaningful
  static constexpr int kDIOChannel0       = 0;
  static constexpr int kDIOChannel1       = 1;
  static constexpr int kDIOChannel2       = 2;
  static constexpr int kDIOChannel3       = 3;
  static constexpr int kDIOChannel4       = 4;
  static constexpr int kDIOChannel5       = 5;
  static constexpr int kDIOChannel6       = 6;
  static constexpr int kDIOChannel7       = 7;
  static constexpr int kDIOChannel8       = 8;
  static constexpr int kDIOChannel9       = 9;
  static constexpr int kDIOChannel10      = 10;


#endif /* SRC_PORTS_H_ */