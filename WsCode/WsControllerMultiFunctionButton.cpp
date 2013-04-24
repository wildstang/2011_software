#include "WsControllerMultiFunctionButton.h"
#include "WsControllerButton.h"

/**
 * Construst an instance of a WsControllerMultiFunctionButton
 */
WsControllerMultiFunctionButton::WsControllerMultiFunctionButton(Gamepad *p_pad,
                                                                 Gamepad::ButtonType actionButton,
                                                                 Gamepad::ButtonType shiftButton,
                                                                 bool usesShiftButton)
    : WsControllerButton(p_pad, actionButton)
{
    a_shiftButton = shiftButton;
    a_usesShiftButton = usesShiftButton;

    a_actionMode = false;
    a_shiftMode = false;
}

/**
 * Get the state of the button represented by the class
 *
 */
bool WsControllerMultiFunctionButton::GetState(void)
{
    bool state = false;
    bool actionState = WsControllerButton::GetState();
    bool shiftState = false;

    bool actionModeNext = false;
    bool shiftModeNext = false;

    if( ap_gamepad != NULL )
    {
        shiftState = ap_gamepad->GetButton( a_shiftButton );
    }

    if( a_usesShiftButton )
    {
        /*
        state = ( !a_actionMode && 
                ( ( a_shiftMode && actionState ) || 
                  ( actionState && shiftState ) ) );
                  */

        state = !a_actionMode &&
                actionState &&
                (a_shiftMode || shiftState);
    }
    else
    {
        state = ( ( !a_shiftMode && ( actionState && !shiftState ) ) || 
                ( a_actionMode && actionState ) );
    }

    actionModeNext = ( ( !a_shiftMode && !shiftState && actionState ) ||
                     ( a_actionMode && actionState ) );

    shiftModeNext = ( !a_actionMode && ( shiftState || ( actionState && a_shiftMode ) ) );

    /*
    printf("AM %d  ACT %d  SH %d  SM %d | SM' %d  AM' %d state %d\n",
            a_actionMode, actionState, shiftState, a_shiftMode, shiftModeNext, actionModeNext, state);
            */

    a_actionMode = actionModeNext;
    a_shiftMode = shiftModeNext;

    return state;
}
