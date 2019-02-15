/**
 * USBCamera.cpp
 *  Created on: Feb 14, 2019
 *      Author: Mike A.
 */
#include <USBCamera.h>
#include "Ports.h"

USBCamera* USBCamera::INSTANCE = nullptr;

USBCamera::USBCamera() {
    // put initialization code into the constructor
}

USBCamera* USBCamera::getInstance() {
    if (INSTANCE == nullptr) {
        INSTANCE = new USBCamera();
    }
    return INSTANCE;
}
