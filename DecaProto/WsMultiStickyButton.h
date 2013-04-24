#ifndef _WSMULTISTICKYBUTTON_H_
#define _WSMULTISTICKYBUTTON_H_

#include "WsButton.h"

class WsMultiStickyButton : public WsButton
{
    public:
        WsMultiStickyButton(Gamepad *p_pad,
                            Gamepad::ButtonType onButton,
                            Gamepad::ButtonType offButton);
        virtual bool GetState(void);
    protected:
        Gamepad::ButtonType a_offButton;
        bool a_stickyState;
};

#endif
