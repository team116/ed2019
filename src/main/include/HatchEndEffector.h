/**
 * HatchEndEffector.h
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#ifndef SRC_HATCHENDEFFECTOR_H_
#define SRC_HATCHENDEFFECTOR_H_

class HatchEndEffector {
public:
    static HatchEndEffector* getInstance();

private:
    HatchEndEffector();
    static HatchEndEffector* INSTANCE;
};

#endif /* SRC_HATCHENDEFFECTOR_H_ */