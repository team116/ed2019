/**
 * CargoEndEffector.h
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#ifndef SRC_CARGOENDEFFECTOR_H_
#define SRC_CARGOENDEFFECTOR_H_
#include <ctre/phoenix.h>

class CargoEndEffector {
public:
    static CargoEndEffector* getInstance();

private:
    CargoEndEffector();
    static CargoEndEffector* INSTANCE;
};

#endif /* SRC_CARGOENDEFFECTOR_H_ */

