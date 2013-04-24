#include "WsMultiStickyButton.h"
#include "WsButton.h"

/**
 * Construst an instance of a WsMultiStickyButton
 *
 * A WsMultiStickyButton is a button that has an on and an off button.
 * It will remember the on/off state until the other button is pressed
 *
 * @param p_pad The gamepad that the physical button is on
 * @param onButton Which button on the gamepad the WsMultiStickyButton will represent the on button
 * @param offButton Which button on the gamepad the WsMultiStickyButton will represent the off button
 */
WsMultiStickyButton::WsMultiStickyButton(Gamepad *p_pad,
                                         Gamepad::ButtonType onButton,
                                         Gamepad::ButtonType offButton)
    : WsButton(p_pad, onButton)
{
    a_offButton = offButton;
    a_stickyState = false;
}

/**
 * Get the state of the button represented by the class
 *
 * @return True when the on button was pressed and the off button hasn't been pressed yet
 * @return False when the off button was pressed and the on button hasn't been pressed yet
 * @return False when both buttons are pressed at the same time
 */
bool WsMultiStickyButton::GetState(void)
{
    bool state = false;
    bool onState = WsButton::GetState();
    bool offState = false;

    if(ap_pad != NULL)
    {
        offState = ap_pad->GetButton(a_offButton);
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
