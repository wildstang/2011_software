#ifndef _WS_JOYSTICK_H_
#define _WS_JOYSTICK_H_

#include "Joystick.h"

class WsJoystick : public Joystick
{
    public:
        WsJoystick(UINT32 port);
        virtual float GetY(JoystickHand hand = kRightHand);
};

#endif
