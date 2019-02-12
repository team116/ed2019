/**
 * LiftEndEffector.h
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#ifndef SRC_LIFTENDEFFECTOR_H_
#define SRC_LIFTENDEFFECTOR_H_

class LiftEndEffector {
public:
    static LiftEndEffector* getInstance();

private:
    LiftEndEffector();
    static LiftEndEffector* INSTANCE;
};

#endif /* SRC_LIFTENDEFFECTOR_H_ */