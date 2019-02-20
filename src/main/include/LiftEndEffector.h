/**
 * LiftEndEffector.h
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#ifndef SRC_LIFTENDEFFECTOR_H_
#define SRC_LIFTENDEFFECTOR_H_
#include <ctre/phoenix.h>
#include <Ports.h>

class LiftEndEffector {
public:
    static LiftEndEffector* getInstance();
#ifdef EDV21    
     WPI_VictorSPX m_LiftMotor{RobotPorts::kLiftChannel};
#else
     WPI_TalonSRX m_LiftMotor{RobotPorts::kLiftChannel};
#endif
private:
    LiftEndEffector();
    static LiftEndEffector* INSTANCE;
};

#endif /* SRC_LIFTENDEFFECTOR_H_ */