/**
 * TipperEndEffector.h
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#ifndef SRC_TIPPER_H_
#define SRC_TIPPER_H_

class TipperEndEffector {
public:
    static TipperEndEffector* getInstance();

private:
    TipperEndEffector();
    static TipperEndEffector* INSTANCE;
};

#endif /* SRC_TIPPER_H_ */