/**
 * utils.cpp
 *  Created on: March 17, 2019
 *      Author: Mike A.
 */
#include <Utils.h>

Utils* Utils::INSTANCE = nullptr;

Utils::Utils() {
// put initialization code into the constructor
// We need to run our vision program in a separate thread. If not, our robot
// program will not run.
}

Utils* Utils::getInstance() {
    if (INSTANCE == nullptr) {
        INSTANCE = new Utils();  // instance of the class
    }
    return INSTANCE;
}
