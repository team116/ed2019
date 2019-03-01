/**
 * TipperEndEffector.h
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#ifndef SRC_TIPPER_H_
#define SRC_TIPPER_H_
#include <frc/DigitalInput.h>
#include <frc/DoubleSolenoid.h>
#include <ctre/Phoenix.h>
#include <Ports.h>

class TipperEndEffector {
 public:
  static TipperEndEffector* getInstance();
  frc::DoubleSolenoid Tipper1EjectorSolenoid{PCM0Ports::kPCM0CANID,
                                             PCM0Ports::kPCM0Tipper1Extend,
                                             PCM0Ports::kPCM0Tipper1Retract};
  frc::DoubleSolenoid Tipper2EjectorSolenoid{PCM0Ports::kPCM0CANID,
                                             PCM0Ports::kPCM0Tipper2Extend,
                                             PCM0Ports::kPCM0Tipper2Retract};
  void tipDeploy();
  void tipRetract();
  void tipOff();
  void tipClimb(double speed, bool disableSensor);
  void tipLower(double speed);
  void tipStop();

  frc::DigitalInput *elevatorLS;

#ifdef EDV21
  WPI_VictorSPX m_TipperMotor{RobotPorts::kTippingChannel};
#else
  WPI_TalonSRX m_TipperMotor{RobotPorts::kTippingChannel};
#endif

 private:
  TipperEndEffector();
  static TipperEndEffector* INSTANCE;
};

#endif /* SRC_TIPPER_H_ */