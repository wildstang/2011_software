#ifndef __INPUTMANAGER_H_
#define __INPUTMANAGER_H_
#include "stubs.h"

#include "Gamepad.h"
#include <map>
#include <vector>


typedef struct
{
    WsControllerAxis* axis;
    float cachedValue;
} AxisDataT;

typedef struct
{
    WsControllerButton* button;
    bool cachedValue;
} ButtonDataT;

typedef struct
{
    GamepadDPad* pad;
    GamepadDPad::DPadDirection cachedValue;
} DPadDataT;

class InputManager
{
    public:

        typedef enum
        {
            MIN_AXIS = 0,
            AXIS_INDEX_DRIVE_THROTTLE = MIN_AXIS,
            AXIS_INDEX_DRIVE_TURN,
            NUM_AXES
        } AxisIndexT;

        typedef enum
        {
            MIN_BUTTON = 0,
            BUTTON_INDEX_DRIVE_ANTITURBO = MIN_BUTTON,
            BUTTON_INDEX_KICK,
            BUTTON_INDEX_MULTISTICKY_TEST,
            BUTTON_INDEX_STICKY_TEST,
            NUM_BUTTONS
        } ButtonIndexT;

        typedef enum
        {
            MIN_DPAD = 0,
            DPAD_INDEX_DRIVER = MIN_DPAD,
            DPAD_INDEX_MANIPULATOR,
            NUM_DPAD
        } DPadIndexT;

        typedef enum
        {
            BUTTON_TYPE_STANDARD,
            BUTTON_TYPE_STICKY,
            BUTTON_TYPE_MULTISTICKY,
            BUTTON_TYPE_TAP
        } ButtonTypeT;



        static InputManager* Instance();
        ~InputManager();

        void RegisterAxis(AxisIndexT index,
                          UINT32 devicePort,
                          UINT32 axis,
                          bool invert = false);

        void RegisterDPad(DPadIndexT index,
                          UINT32 devicePort);

        void RegisterButton(ButtonIndexT index,
                            UINT32 devicePort,
                            UINT32 buttonNumber,
                            ButtonTypeT buttonType = BUTTON_TYPE_STANDARD,
                            bool invert = false);

        void RegisterButton(ButtonIndexT index,
                            UINT32 devicePort,
                            std::vector<UINT32> buttonList,
                            ButtonTypeT buttonType = BUTTON_TYPE_STANDARD,
                            bool invert = false);


        //void RegisterDsAnalog();

        void ReadInputs(void);
        void ResetInputs(void);


        float GetAxisValue(AxisIndexT index);
        bool GetButtonValue(ButtonIndexT index);
        GamepadDPad::DPadDirection GetDPadValue(DPadIndexT index);
        //UINT32 GetAnalogValue();

        void UnregisterAxis(AxisIndexT index);
        void UnregisterButton(ButtonIndexT index);
        void UnregisterDPad(DPadIndexT index);
        //void UnregisterDsAnalog();
        void UnregisterAll();

    protected:

        std::map<AxisIndexT, AxisDataT*> a_axisMap;
        std::map<ButtonIndexT, ButtonDataT*> a_buttonMap;
        std::map<DPadIndexT, DPadDataT*> a_dPadMap;

    private:
        InputManager();
        static InputManager* ap_singletonInstance;
};

typedef std::map<InputManager::AxisIndexT, AxisDataT*>::iterator AxisIteratorT;
typedef std::map<InputManager::ButtonIndexT, ButtonDataT*>::iterator ButtonIteratorT;
typedef std::map<InputManager::DPadIndexT, DPadDataT*>::iterator DPadIteratorT;





#endif // __INPUTMANAGER_H_
