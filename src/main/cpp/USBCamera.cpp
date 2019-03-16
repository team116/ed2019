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
// We need to run our vision program in a separate thread. If not, our robot
// program will not run.
#if defined(__linux__)
  std::thread visionThread(USBCamera::VisionThread);
  visionThread.detach();
#else
  wpi::errs() << "Vision only available on Linux.\n";
  wpi::errs().flush();
#endif
}

USBCamera* USBCamera::getInstance() {
    if (INSTANCE == nullptr) {
        INSTANCE = new USBCamera();  // instance of the class
    }
    return INSTANCE;
}
