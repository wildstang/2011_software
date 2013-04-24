#if !defined(_WSCONTROLMETHODMINIBOT_H)
#define _WSCONTROLMETHODMINIBOT_H

#include <stdio.h>
//#include "WsMinibot.h"

#define MINIBOT_SWITCH_ON true
#define MINIBOT_SWITCH_OFF false

class InputManager;

class WsControlMethodMinibot
{
public:

    typedef enum
    {
        MINIBOT_INPUT_MODE_UNINIT,
        MINIBOT_INPUT_MODE_OFF,
        MINIBOT_INPUT_MODE_ON,
    } MinibotInputModeT;

    typedef enum
    {
        MINIBOT_DEPLOY_NONE,
        MINIBOT_DEPLOY_IN,
        MINIBOT_DEPLOY_OUT,
    } MinibotDeployStateT;

    WsControlMethodMinibot();
    ~WsControlMethodMinibot();

    WsControlMethodMinibot::MinibotInputModeT getMinibotMode(void);
    WsControlMethodMinibot::MinibotDeployStateT getDeployState(void);
    void reset(bool fullReset);

    WsControlMethodMinibot::MinibotInputModeT dashGetMinibotMode(void);
    WsControlMethodMinibot::MinibotDeployStateT dashGetDeployState(void);


private:
    InputManager *ap_inputManager;
    MinibotInputModeT a_minibotMode;

    WsControlMethodMinibot::MinibotDeployStateT a_cachedDeployState;

};

#endif  //_WSCONTROLMETHODMINIBOT_H
