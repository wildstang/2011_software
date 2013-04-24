//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang 2010
//  @ File Name : WsControllerButton.h
//  @ Date : 1/14/2009
//  @ Author : 
//
//


#if !defined(_WSCONTROLLERBUTTON_H)
#define _WSCONTROLLERBUTTON_H

#include <stdio.h>
#include "WsControllerBase.h"

/**
* A simple button class to handle joystick, gamepad, dpad, or DS buttons
*/
class WsControllerButton : public WsControllerBase
{
public:
    WsControllerButton();
    WsControllerButton(Joystick* p_js, UINT32 button);
    WsControllerButton(Gamepad* p_pad, UINT32 button);
    WsControllerButton(Gamepad* p_pad, Gamepad::ButtonType button);
    WsControllerButton(Gamepad* p_pad, GamepadDPad::DPadDirection direction);
    WsControllerButton(UINT32 channel);
    virtual ~WsControllerButton();
    virtual bool GetState(void );
    virtual void ResetState(void);
protected:
    virtual bool ApplyInvert(bool state);
    virtual bool GetButtonState(UINT32 buttonNum, UINT32 channelNum, GamepadDPad::DPadDirection direction);
};

#endif  //_WSCONTROLLERBUTTON_H
