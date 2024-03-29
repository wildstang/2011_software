//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang 2010
//  @ File Name : WsControllerStickyButton.cpp
//  @ Date : 1/14/2009
//  @ Author : 
//
//


#include "WsControllerStickyButton.h"
#include "Joystick.h"
#include "Gamepad.h"

/**
* Constructs a WsControllerStickyButton
* @param p_js The joystick that has the button of interest
* @param p_button The button numeber to use as input
*/
WsControllerStickyButton::WsControllerStickyButton(Joystick* p_js, UINT32 button) :
                          WsControllerButton(p_js, button)
{
    ResetState();
}

/**
* Constructs a WsControllerStickyButton
* @param p_pad The gamepad that has the button of interest
* @param p_button The button numeber to use as input
*/
WsControllerStickyButton::WsControllerStickyButton(Gamepad* p_pad, UINT32 button) :
                          WsControllerButton(p_pad, button)
{
    ResetState();
}

WsControllerStickyButton::WsControllerStickyButton(Gamepad* p_pad, Gamepad::ButtonType button) :
                          WsControllerButton(p_pad, button)
{
    ResetState();
}

/**
* Destructs a WsControllerStickyButton
*/
WsControllerStickyButton::~WsControllerStickyButton()
{
}

/**
* Resets the internal states
*/
void WsControllerStickyButton::ResetState(void)
{
    a_statePrev = false;
    a_stickyState = false;
}

/**
* Calculates the current virtual state of the button
* @returns The current vitrual state of the button
*/
bool WsControllerStickyButton::GetState(void )
{
    bool stateCurr;
    stateCurr = WsControllerButton::GetState();
    if((a_statePrev == false) && (stateCurr == true))
    {
        a_stickyState = !a_stickyState;
    }
    a_statePrev = stateCurr;

    return a_stickyState;
}

