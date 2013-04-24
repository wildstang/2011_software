#ifndef _WSTAPBUTTON_H_
#define _WSTAPBUTTON_H_

#include "WsButton.h"

class WsTapButton : public WsButton
{
    public:
        WsTapButton(Gamepad *p_pad, Gamepad::ButtonType button);
        virtual bool GetState(void);
    protected:
        bool a_statePrev;
};

#endif
