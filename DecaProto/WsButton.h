#ifndef _WSBUTTON_H_
#define _WSBUTTON_H_

#include "Gamepad.h"

class WsButton
{
    public:
        WsButton(Gamepad *p_pad, Gamepad::ButtonType button);
        virtual bool GetState(void);
    protected:
        Gamepad *ap_pad;
        Gamepad::ButtonType a_button;
};

#endif
