//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang 2009
//  @ File Name : WsControllerPolarStick.h
//  @ Date : 1/17/2009
//  @ Author : 
//
//


#if !defined(_WSCONTROLLERPOLARSTICK_H)
#define _WSCONTROLLERPOLARSTICK_H

#include <stdio.h>
#include <math.h>
#include "WsTrig.h"
#include "Gamepad.h"

//Joystick Bounds.  Currently 1.0f
#define BOUNDS 1.0f

class WsControllerAxis;

/**
* This is a composition of two WsControllerAxis objects that combines the two axes into polar coordinates.
*/
class WsControllerPolarStick
{
public:
    WsControllerPolarStick(Gamepad* gamepad, Gamepad::AxisType xAxis, Gamepad::AxisType yAxis);
    virtual ~WsControllerPolarStick();
    float GetRadius(void);
    float GetAngle(void);
    float GetX(void);
    float GetY(void);
protected:
    float calcRadius(float x, float y);
    float calcAngle(float x, float y);

    Gamepad* ap_gamepad;
    Gamepad::AxisType a_xAxis;
    Gamepad::AxisType a_yAxis;
    
};

#endif  //_WSCONTROLLERPOLARSTICK_H
