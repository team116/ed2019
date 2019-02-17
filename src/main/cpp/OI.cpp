/**
 * OI.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: Mike A.
 */
#include <OI.h>
#include "Ports.h"

OI *OI::INSTANCE = nullptr;

OI::OI()
{
    // put initialization code into the constructor
    xbox0 = new frc::XboxController(OIPorts::kXboxChannel);
    buttonBox1 = new frc::Joystick(OIPorts::kJoystickChannel1);
    buttonBox2 = new frc::Joystick(OIPorts::kJoystickChannel2);
    buttonBox3 = new frc::Joystick(OIPorts::kJoystickChannel3);
}

void OI::process() {

}

OI *OI::getInstance()
{
    if (INSTANCE == nullptr)
    {
        INSTANCE = new OI();
    }
    return INSTANCE;
}
