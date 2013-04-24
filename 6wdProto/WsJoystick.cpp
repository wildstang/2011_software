#include "WsJoystick.h"


/**
 * Construct an instance of a WsJoystick.
 *
 * @param port The port on the driver station that the joystick is plugged into.
 */
WsJoystick::WsJoystick(UINT32 port)
    : Joystick(port)
{
}

/**
 * Get the Y value of the joystick
 */
float WsJoystick::GetY(JoystickHand hand)
{
    float output;
    
    output = -1 * Joystick::GetY(hand);
    
    return output;
}
