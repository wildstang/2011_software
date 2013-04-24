#include "WsButton.h"

/**
 * Construst an instance of a WsButton
 *
 * @param p_pad The gamepad that the physical button is on
 * @param button Which button on the gamepad the WsButton will represent
 */
WsButton::WsButton(Gamepad *p_pad, Gamepad::ButtonType button)
{
    ap_pad = p_pad;
    a_button = button;
}

/**
 * Get the state of the button represented by the class
 *
 * @return False when the button is not pressed
 * @return True when the button is pressed
 */
bool WsButton::GetState(void)
{
    bool state = false;

    if(ap_pad != NULL)
    {
        state = ap_pad->GetButton(a_button);
    }

    return state;
}
