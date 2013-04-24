#include "WsStickyButton.h"
#include "WsButton.h"

/**
 * Construst an instance of a WsStickyButton
 *
 * A WsStickyButton is a virtual button that will retain its previous state
 * until the physical button is pressed, at which time the state will toggle
 *
 * @param p_pad The gamepad that the physical button is on
 * @param button Which button on the gamepad the WsStickyButton will represent
 */
WsStickyButton::WsStickyButton(Gamepad *p_pad, Gamepad::ButtonType button)
    : WsButton(p_pad, button)
{
    a_statePrev = false;
    a_stickyState = false;
}

/**
 * Get the virtual state of the button represented by the class
 *
 * The sticky state of the virtual button is toggled when the physical button
 * is pressed and it previously wasn't
 *
 * @return The sticky state of the button
 */
bool WsStickyButton::GetState(void)
{
    bool state = false;
    bool curState = WsButton::GetState();

    if((curState == true) &&
       (a_statePrev == false))
    {
        a_stickyState = !a_stickyState;
    }

    state = a_stickyState;
    a_statePrev = curState;

    return state;
}
