#ifndef _WSSTICKYBUTTON_H_
#define _WSSTICKYBUTTON_H_

#include "WsButton.h"

class WsStickyButton : public WsButton
{
    public:
        WsStickyButton(Gamepad *p_pad, Gamepad::ButtonType button);
        virtual bool GetState(void);
    protected:
        bool a_statePrev;
        bool a_stickyState;
};

#endif
