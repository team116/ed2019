/**
 * HatchEndEffector.h
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#ifndef SRC_HATCHENDEFFECTOR_H_
#define SRC_HATCHENDEFFECTOR_H_
#include <frc/DoubleSolenoid.h>
#include <Ports.h>

class HatchEndEffector {
public:
    static HatchEndEffector* getInstance();
    frc::DoubleSolenoid hatchEjectorSolenoid {PCM0Ports::kPCM0CANID, PCM0Ports::kPCM0HatchExtend, PCM0Ports::kPCM0HatchRetract};

    void hatchDeploy(); 
    void hatchRetract(); 
    void hatchOff();

private:
    HatchEndEffector();
    static HatchEndEffector* INSTANCE;
};

#endif /* SRC_HATCHENDEFFECTOR_H_ */