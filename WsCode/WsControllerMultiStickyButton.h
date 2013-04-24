#ifndef _WSCONTROLLERMULTISTICKYBUTTON_H_
#define _WSCONTROLLERMULTISTICKYBUTTON_H_

#include "WsControllerButton.h"

class WsControllerMultiStickyButton : public WsControllerButton
{
    public:
        WsControllerMultiStickyButton(Gamepad *p_pad,
                            Gamepad::ButtonType offButton,
                            Gamepad::ButtonType onButton);
        virtual bool GetState(void);
        virtual void ResetState(void);
    protected:
        Gamepad::ButtonType a_offButton;
        bool a_stickyState;
};

#endif
