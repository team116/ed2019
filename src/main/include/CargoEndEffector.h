/**
 * CargoEndEffector.h
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#ifndef SRC_CARGOENDEFFECTOR_H_
#define SRC_CARGOENDEFFECTOR_H_
#include <frc/DigitalInput.h>
#include <Ports.h>
#include <ctre/Phoenix.h>
#include <frc/DoubleSolenoid.h>

class CargoEndEffector {
 public:
  static CargoEndEffector* getInstance();

  // Which way is the roller moving
  enum Direction { INTAKE, OFF, EJECT };
  
#ifdef EDV21  
  WPI_VictorSPX m_IntakeMotor{RobotPorts::kBallIntakeChannel};
#else
  WPI_TalonSRX m_IntakeMotor{RobotPorts::kBallIntakeChannel};
#endif

  frc::DoubleSolenoid CargoIntakeSolenoid{PCM0Ports::kPCM0CANID,
                                          PCM0Ports::kPCM0CargoIntakeExtend,
                                          PCM0Ports::kPCM0CargoIntakeRetract};

  void intakeDeploy();
  void intakeRetract();
  void intakeMovement(Direction direction, double speed);
  void intakeOff();

  frc::DigitalInput *cargoLS;

 private:
  CargoEndEffector();
  static CargoEndEffector* INSTANCE;
};

#endif /* SRC_CARGOENDEFFECTOR_H_ */
