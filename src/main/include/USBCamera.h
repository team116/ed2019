/**
 * USBCamera.h
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#ifndef SRC_USBCAMERA_H_
#define SRC_USBCAMERA_H_

#include <Ports.h>
#include <cameraserver/CameraServer.h>
#include <wpi/raw_ostream.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cscore_oo.h>
#include <thread>

class USBCamera {
 public:
  static USBCamera *getInstance();

#if defined(__linux__)
  static void VisionThread() {
#ifdef USEUSBCAMERA
    // Get the USB camera from CameraServer
    cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture();
    // Set the resolution
#ifdef EDV21    
    camera.SetResolution(160, 120); // Microsoft LifeCam
    camera.SetFPS(15);
#else
    camera.SetVideoMode(cs::VideoMode::PixelFormat::kMJPEG, 640, 480, 30);
//    camera.SetResolution(640, 480);  // Baby Mechanum camera
    //camera.SetFPS(15);
#endif
    //        camera.SetWhiteBalanceManual(50);
    // Get a CvSink. This will capture Mats from the Camera
    //cs::CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo();
    // Setup a CvSource. This will send images back to the Dashboard
    //cs::CvSource outputStream =
    //    frc::CameraServer::GetInstance()->PutVideo("Rectangle", 320, 240);

    // Mats are very memory expensive. Lets reuse this Mat.
    /*
            cv::Mat mat;

            while (true)
            {
                // Tell the CvSink to grab a frame from the camera and
                // put it
                // in the source mat.  If there is an error notify the
                // output.
                if (cvSink.GrabFrame(mat) == 0)
                {
                    // Send the output the error.
                    outputStream.NotifyError(cvSink.GetError());
                    // skip the rest of the current iteration
                    continue;
                }
                // Put a rectangle on the image
                rectangle(mat, cv::Point(100, 100), cv::Point(400, 400),
                          cv::Scalar(255, 255, 255), 5);
                // Give the output stream a new image to display
                outputStream.PutFrame(mat);
            }
            */
#else   // We must be using the Axis Camera
    // Get the Axis camera from CameraServer
    cs::AxisCamera camera =
        frc::CameraServer::GetInstance()->AddAxisCamera("FRC116Axis", "10.1.16.11");
    // Set the resolution
    camera.SetResolution(320, 240);
    camera.SetFPS(15);
/*
    // Get a CvSink. This will capture Mats from the Camera
    cs::CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo();
    // Setup a CvSource. This will send images back to the Dashboard
    cs::CvSource outputStream =
        frc::CameraServer::GetInstance()->PutVideo("Axis", 320, 240);
    // Mats are very memory expensive. Lets reuse this Mat.
    cv::Mat mat;

    while (true) {
      // Tell the CvSink to grab a frame from the camera and put it in the
      // source mat. If there is an error notify the output.
      if (cvSink.GrabFrame(mat) == 0) {
        // Send the output the error.
        outputStream.NotifyError(cvSink.GetError());
        // skip the rest of the current iteration
        continue;
      }
      // Put a rectangle on the image
      rectangle(mat, cv::Point(100, 100), cv::Point(400, 400),
                cv::Scalar(255, 255, 255), 5);
      // Give the output stream a new image to display
      outputStream.PutFrame(mat);
    }
  */
#endif
  }
#endif

 private:
  USBCamera();
  static USBCamera *INSTANCE;
};

#endif /* SRC_USBCAMERA_H_ */