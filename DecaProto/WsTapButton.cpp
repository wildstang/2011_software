#include "WsTapButton.h"
#include "WsButton.h"

/**
 * Construst an instance of a WsTapButton
 *
 * A WsTapButton is a virtual button that will only return true at
 * the instant the physical button is pressed
 *
 * @param p_pad The gamepad that the physical button is on
 * @param button Which button on the gamepad the WsTapButton will represent
 */
WsTapButton::WsTapButton(Gamepad *p_pad, Gamepad::ButtonType button)
    : WsButton(p_pad, button)
{
    a_statePrev = false;
}

/**
 * Get the state of the button represented by the class
 *
 * @return True if the button is pressed and it previously wasn't
 * @return False in all other situations
 */
bool WsTapButton::GetState(void)
{
    bool state = false;
    bool curState = WsButton::GetState();

    if((curState == true) && (a_statePrev == false))
    {
        state = true;
    }

    a_statePrev = curState;

    return state;
}
