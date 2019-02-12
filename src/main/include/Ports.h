/**
 * Ports.h
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#ifndef SRC_PORTS_H_
#define SRC_PORTS_H_

// PDP CAN bus ID -- Must be ID 0 for WPILib to be able to read the current
  constexpr int kPDPChannel        = 0;

// Miscellaneous CAN IDs
  constexpr int kCanifierChannel   = 6;
  constexpr int kPigeonChannel     = 9;

// Motor Controllers
  constexpr int kFrontLeftChannel  = 1;
  constexpr int kRearLeftChannel   = 2;
  constexpr int kFrontRightChannel = 3;
  constexpr int kRearRightChannel  = 4;
  constexpr int kBallIntakeChannel = 14;
  constexpr int kLiftChannel       = 15;
  constexpr int kTippingChannel    = 16;


// PCM 0 Solenoid Assignments
  constexpr int kPCM0CANID    = 10;
  constexpr int kPCM0Channel0 = 0;
  constexpr int kPCM0Channel1 = 1;
  constexpr int kPCM0Channel2 = 2;
  constexpr int kPCM0Channel3 = 3;
  constexpr int kPCM0Channel4 = 4;
  constexpr int kPCM0Channel5 = 5;
  constexpr int kPCM0Channel6 = 6;
  constexpr int kPCM0Channel7 = 7;

// PCM 1 Solenoid Assignments  -- Maybe not needed
  constexpr int kPCM1CANID    = 11;
  constexpr int kPCM1Channel0 = 0;
  constexpr int kPCM1Channel1 = 1;
  constexpr int kPCM1Channel2 = 2;
  constexpr int kPCM1Channel3 = 3;
  constexpr int kPCM1Channel4 = 4;
  constexpr int kPCM1Channel5 = 5;
  constexpr int kPCM1Channel6 = 6;
  constexpr int kPCM1Channel7 = 7;
 
// Joysticks
  constexpr int kXboxChannel       = 0;
  constexpr int kJoystickChannel1  = 1;
  constexpr int kJoystickChannel2  = 2;
  constexpr int kJoystickChannel3  = 3;
  constexpr int kJoystickChannel4  = 4;

// Digital I/O from RoboRIO  --  Be sure the rename these to something more meaningful
  constexpr int kDIOChannel0       = 0;
  constexpr int kDIOChannel1       = 1;
  constexpr int kDIOChannel2       = 2;
  constexpr int kDIOChannel3       = 3;
  constexpr int kDIOChannel4       = 4;
  constexpr int kDIOChannel5       = 5;
  constexpr int kDIOChannel6       = 6;
  constexpr int kDIOChannel7       = 7;
  constexpr int kDIOChannel8       = 8;
  constexpr int kDIOChannel9       = 9;
  constexpr int kDIOChannel10      = 10;


#endif /* SRC_PORTS_H_ */