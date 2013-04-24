#ifndef _WSCONTROLLERTAPBUTTON_H_
#define _WSCONTROLLERTAPBUTTON_H_

#include "WsControllerButton.h"

class WsControllerTapButton : public WsControllerButton
{
    public:
        WsControllerTapButton(Gamepad *p_pad, Gamepad::ButtonType button);
        virtual bool GetState(void);
    protected:
        bool a_statePrev;
};

#endif
