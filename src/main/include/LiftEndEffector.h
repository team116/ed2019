/**
 * LiftEndEffector.h
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#ifndef SRC_LIFTENDEFFECTOR_H_
#define SRC_LIFTENDEFFECTOR_H_
#include <frc/DigitalInput.h>
#include <ctre/Phoenix.h>
#include <Ports.h>

class LiftEndEffector {
public:
    static LiftEndEffector* getInstance();
#ifdef EDV21    
     WPI_VictorSPX m_LiftMotor{RobotPorts::kLiftChannel};
#else
     WPI_TalonSRX m_LiftMotor{RobotPorts::kLiftChannel};
#endif

  enum liftPosition {BOTTOM, LOADER, RKTBTMCARGO, CARGOBAY, RKTMIDHATCH, RKTMIDCARGO, RKTTOPHATCH, RKTTOPCARGO};

  liftPosition liftPos = BOTTOM;  // Start at the bottom position at the beginning of the match

  frc::DigitalInput *bottomLS;
  frc::DigitalInput *liftLS;

private:
    LiftEndEffector();
    static LiftEndEffector* INSTANCE;
};

#endif /* SRC_LIFTENDEFFECTOR_H_ */