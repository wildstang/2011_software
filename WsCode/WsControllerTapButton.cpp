#include "WsControllerTapButton.h"
#include "WsControllerButton.h"

/**
 * Construst an instance of a WsControllerTapButton
 *
 * A WsControllerTapButton is a virtual button that will only return true at
 * the instant the physical button is pressed
 *
 * @param p_pad The gamepad that the physical button is on
 * @param button Which button on the gamepad the WsControllerTapButton will represent
 */
WsControllerTapButton::WsControllerTapButton(Gamepad *p_pad, Gamepad::ButtonType button)
    : WsControllerButton(p_pad, button)
{
    a_statePrev = false;
}

/**
 * Get the state of the button represented by the class
 *
 * @return True if the button is pressed and it previously wasn't
 * @return False in all other situations
 */
bool WsControllerTapButton::GetState(void)
{
    bool state = false;
    bool curState = WsControllerButton::GetState();

    if((curState == true) && (a_statePrev == false))
    {
        state = true;
    }

    a_statePrev = curState;

    return state;
}
