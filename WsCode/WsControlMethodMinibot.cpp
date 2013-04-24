#include <math.h>
#include "WsControlMethodMinibot.h"
#include "InputManager.h"

WsControlMethodMinibot::WsControlMethodMinibot()
{
    ap_inputManager = InputManager::Instance();
    reset(true);
}

WsControlMethodMinibot::~WsControlMethodMinibot()
{

}

WsControlMethodMinibot::MinibotInputModeT WsControlMethodMinibot::getMinibotMode(void)
{
//    WsControlMethodMinibot::MinibotInputModeT minibotModePrev = a_minibotMode;
    bool minibotSwitch = ap_inputManager->GetButtonValue(InputManager::BUTTON_INDEX_MINIBOT_MODE);
    //printf("SW: %d (%d)", minibotSwitch, minibotSwitch == MINIBOT_SWITCH_OFF);

    if( minibotSwitch == MINIBOT_SWITCH_OFF )
    {
        a_minibotMode = MINIBOT_INPUT_MODE_OFF;
    }

    if( ( a_minibotMode != MINIBOT_INPUT_MODE_UNINIT ) &&
        ( minibotSwitch == MINIBOT_SWITCH_ON ))
    {
        a_minibotMode = MINIBOT_INPUT_MODE_ON;
    }

    //printf("Mode: %d ", a_minibotMode);

    return a_minibotMode;
}
WsControlMethodMinibot::MinibotDeployStateT WsControlMethodMinibot::getDeployState(void)
{
    WsControlMethodMinibot::MinibotDeployStateT state = WsControlMethodMinibot::MINIBOT_DEPLOY_NONE;

    if( a_minibotMode == MINIBOT_INPUT_MODE_ON )
    {
        if(ap_inputManager->GetButtonValue( InputManager::BUTTON_INDEX_MINIBOT_DEPLOY ) == true)
        {
           state = WsControlMethodMinibot::MINIBOT_DEPLOY_OUT;
        }
        else if(ap_inputManager->GetButtonValue( InputManager::BUTTON_INDEX_MINIBOT_RETRACT ) == true)
        {
           state = WsControlMethodMinibot::MINIBOT_DEPLOY_IN;
        }
    }

    a_cachedDeployState = state;
    return state;
}

void WsControlMethodMinibot::reset(bool fullReset)
{

    if(fullReset == true)
    {
        a_minibotMode = MINIBOT_INPUT_MODE_UNINIT;
    }
    else
    {
        if(a_minibotMode != MINIBOT_INPUT_MODE_UNINIT)
        {
            a_minibotMode = MINIBOT_INPUT_MODE_OFF;
        }
    }

    a_cachedDeployState = MINIBOT_DEPLOY_IN;

    ap_inputManager->ResetButton(InputManager::BUTTON_INDEX_MINIBOT_DEPLOY,
                                 InputManager::GAMEPAD_INDEX_MANIPULATOR);
    ap_inputManager->ResetButton(InputManager::BUTTON_INDEX_MINIBOT_RETRACT,
                                 InputManager::GAMEPAD_INDEX_MANIPULATOR);
}

WsControlMethodMinibot::MinibotInputModeT WsControlMethodMinibot::dashGetMinibotMode(void)
{
    return a_minibotMode;
}

WsControlMethodMinibot::MinibotDeployStateT WsControlMethodMinibot::dashGetDeployState(void)
{
    return a_cachedDeployState;
}
