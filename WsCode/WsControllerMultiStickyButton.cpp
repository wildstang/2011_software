#include "WsControllerMultiStickyButton.h"
#include "WsControllerButton.h"

/**
 * Construst an instance of a WsControllerMultiStickyButton
 *
 * A WsControllerMultiStickyButton is a button that has an on and an off button.
 * It will remember the on/off state until the other button is pressed
 *
 * @param p_pad The gamepad that the physical button is on
 * @param offButton Which button on the gamepad the WsControllerMultiStickyButton will represent the off button
 * @param onButton Which button on the gamepad the WsControllerMultiStickyButton will represent the on button
 */
WsControllerMultiStickyButton::WsControllerMultiStickyButton(Gamepad *p_pad,
                                         Gamepad::ButtonType offButton,
                                         Gamepad::ButtonType onButton)
    : WsControllerButton(p_pad, onButton)
{
    a_offButton = offButton;
    ResetState();
}

/**
 * Get the state of the button represented by the class
 *
 * @return True when the on button was pressed and the off button hasn't been pressed yet
 * @return False when the off button was pressed and the on button hasn't been pressed yet
 * @return False when both buttons are pressed at the same time
 */
bool WsControllerMultiStickyButton::GetState(void)
{
    bool state = false;
    bool onState = WsControllerButton::GetState();
    bool offState = false;

    if(ap_gamepad != NULL)
    {
        offState = ap_gamepad->GetButton(a_offButton);
    }

    if(onState == true)
    {
        a_stickyState = true;
    }

    if(offState == true)
    {
        a_stickyState = false;
    }

    state = a_stickyState;

    return state;
}

/**
* Resets the internal states
*/
void WsControllerMultiStickyButton::ResetState(void)
{
    a_stickyState = false;
}
