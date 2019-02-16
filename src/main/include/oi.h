/**
 * OI.h
 *
 *  Created on: Feb 11, 2019
 *      Author: Mike A.
 */
#ifndef SRC_OI_H_
#define SRC_OI_H_

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include <frc/GenericHID.h>
#include <ctre/phoenix.h>
#include <Ports.h>

class OI
{
  public:

    static OI *getInstance();

    frc::XboxController *xbox0;
    frc::Joystick *buttonBox1;
    frc::Joystick *buttonBox2;
    frc::Joystick *buttonBox3;
    // Driver Station related

    enum Pos
    {
        LEFT,
        CENTER,
        RIGHT
    };
    frc::SendableChooser<Pos> m_chooser;

    enum Dest
    {
        TELEOP,
        DONOTHING,
        FRONTCARGO,
        RIGHTCARGO,
        LEFTCARGO,
        RIGHTROCKET,
        LEFTROCKET
    };
    frc::SendableChooser<Dest> m_destination;

    Pos startPosition;
    Dest destination;

  private:
    OI();
    static OI *INSTANCE;
};

#endif /* SRC_OI_H_ */