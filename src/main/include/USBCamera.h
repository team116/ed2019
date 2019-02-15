/**
 * USBCamera.h
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#ifndef SRC_USBCAMERA_H_
#define SRC_USBCAMERA_H_

class USBCamera {
public:
    static USBCamera* getInstance();

private:
    USBCamera();
    static USBCamera* INSTANCE;
};

#endif /* SRC_USBCAMERA_H_ */