#ifndef __INPUTMANAGER_H_
#define __INPUTMANAGER_H_

#include "Gamepad.h"
#include "WsControllerAxis.h"
#include "WsControllerButton.h"
#include "WsControllerStickyButton.h"
#include "WsControllerMultiStickyButton.h"
#include "WsControllerMultiFunctionButton.h"
#include "WsControllerTapButton.h"
#include <map>
#include <vector>


#define GAMEPAD_PORT_DRIVER 1
#define GAMEPAD_PORT_UNUSED_A 2
#define GAMEPAD_PORT_MANIPULATOR 3
#define GAMEPAD_PORT_OI 4

typedef struct
{
    Gamepad* pad;
} GamepadDataT;

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
        static const GamepadDPad::DPadDirection DPAD_DIR_CLAW_OPEN = GamepadDPad::kUp;
        static const GamepadDPad::DPadDirection DPAD_DIR_CLAW_CLOSE = GamepadDPad::kDown;
        static const GamepadDPad::DPadDirection DPAD_DIR_LED_REQUEST_SQUARE = GamepadDPad::kRight;
        static const GamepadDPad::DPadDirection DPAD_DIR_LED_REQUEST_RANDOM = GamepadDPad::kLeft;

        typedef enum
        {
            MIN_GAMEPAD = 0,
            GAMEPAD_INDEX_DRIVER = MIN_GAMEPAD,
            GAMEPAD_INDEX_MANIPULATOR,
            GAMEPAD_INDEX_PORT3,
            GAMEPAD_INDEX_OI,
            NUM_GAMEPADS
        } GamepadIndexT;

        typedef enum
        {
            MIN_AXIS = 0,
            AXIS_INDEX_DRIVE_THROTTLE = MIN_AXIS,
            AXIS_INDEX_DRIVE_TURN,
            AXIS_INDEX_ARM,
            AXIS_INDEX_LIFT,
            AXIS_INDEX_AUTO_PROG_SELECTOR,
            AXIS_INDEX_AUTO_RACK_SELECTOR,
            AXIS_INDEX_AUTO_COL_SELECTOR,
            AXIS_INDEX_AUTO_HEIGHT_SELECTOR,
            NUM_AXES
        } AxisIndexT;

        typedef enum
        {
            MIN_BUTTON = 0,
            BUTTON_INDEX_DRIVE_SHIFTER = MIN_BUTTON,
            BUTTON_INDEX_DRIVE_TURBO,
            BUTTON_INDEX_ROLLER_CLAW_IN,
            BUTTON_INDEX_ROLLER_CLAW_OUT,
            BUTTON_INDEX_LARM_POS_HOME,
            BUTTON_INDEX_LARM_POS_FLOOR,
            BUTTON_INDEX_LARM_POS_HP,
            BUTTON_INDEX_LARM_POS_SCORE_LOW1,
            BUTTON_INDEX_LARM_POS_SCORE_MID1,
            BUTTON_INDEX_LARM_POS_SCORE_HIGH1,
            BUTTON_INDEX_LARM_POS_SCORE_LOW2,
            BUTTON_INDEX_LARM_POS_SCORE_MID2,
            BUTTON_INDEX_LARM_POS_SCORE_HIGH2,
            BUTTON_INDEX_ARM_CALIB_BOT,
            BUTTON_INDEX_ARM_CALIB_0,
            BUTTON_INDEX_ARM_CALIB_90,
            BUTTON_INDEX_CALIB,
            BUTTON_INDEX_ARM_FEEDBACK_DISABLE,
            BUTTON_INDEX_SCORE_TUBE,
            BUTTON_INDEX_LED_ENABLE,
            BUTTON_INDEX_AUTO_LOCKIN,
            BUTTON_INDEX_MINIBOT_MODE,
            BUTTON_INDEX_MINIBOT_DEPLOY,
            BUTTON_INDEX_MINIBOT_RETRACT,
            // Square is in dpad
            BUTTON_INDEX_LED_REQUEST_CIRCLE,
            BUTTON_INDEX_LED_REQUEST_TRIANGLE,
            NUM_BUTTONS
        } ButtonIndexT;

        typedef enum
        {
            MIN_DPAD = 0,
            DPAD_INDEX_DRIVER = MIN_DPAD,
            DPAD_INDEX_MANIPULATOR,
            DPAD_INDEX_PORT3,
            DPAD_INDEX_OI,
            NUM_DPAD
        } DPadIndexT;

        typedef enum
        {
            BUTTON_STYLE_STANDARD,
            BUTTON_STYLE_STICKY,
            BUTTON_STYLE_MULTISTICKY,
            BUTTON_STYLE_TAP,
            BUTTON_STYLE_MULTIFUNCTION_NO_SHIFT,
            BUTTON_STYLE_MULTIFUNCTION_SHIFT,
        } ButtonStyleT;



        static InputManager* Instance();
        ~InputManager();

        void RegisterAxis(AxisIndexT index,
                          GamepadIndexT gamepadIndex,
                          Gamepad::AxisType axis,
                          bool invert = false);

        void RegisterDPad(DPadIndexT index,
                          GamepadIndexT gamepadIndex);
        
        void RegisterButton(ButtonIndexT index,
                            GamepadIndexT gamepadIndex,
                            Gamepad::ButtonType buttonType,
                            ButtonStyleT buttonStyle = BUTTON_STYLE_STANDARD,
                            bool invert = false);

        void RegisterButton(ButtonIndexT index,
                            GamepadIndexT gamepadIndex,
                            std::vector<Gamepad::ButtonType> buttonList,
                            ButtonStyleT buttonStyle = BUTTON_STYLE_STANDARD,
                            bool invert = false);


        //void RegisterDsAnalog();

        void ReadInputs(void);
        void ResetInputs(void);
        void ResetButton(ButtonIndexT index,
                         GamepadIndexT gamepadIndexT);


        float GetAxisValue(AxisIndexT index);
        bool GetButtonValue(ButtonIndexT index);
        GamepadDPad::DPadDirection GetDPadValue(DPadIndexT index);
        //UINT32 GetAnalogValue();

        void UnregisterAxis(AxisIndexT index);
        void UnregisterButton(ButtonIndexT index);
        void UnregisterDPad(DPadIndexT index);
        void UnregisterGamepad(GamepadIndexT index);
        //void UnregisterDsAnalog();
        void UnregisterAll();

        Gamepad* GetGamepad(GamepadIndexT gamepadIndex);

    protected:

        std::map<GamepadIndexT, GamepadDataT*> a_gamepadMap;
        std::map<AxisIndexT, AxisDataT*> a_axisMap;
        std::map<ButtonIndexT, ButtonDataT*> a_buttonMap;
        std::map<DPadIndexT, DPadDataT*> a_dPadMap;

    private:
        InputManager();
        static InputManager* ap_singletonInstance;
        UINT32 GetPortFromIndex(GamepadIndexT gamepadIndex);
};

typedef std::map<InputManager::GamepadIndexT, GamepadDataT*>::iterator GamepadIteratorT;
typedef std::map<InputManager::AxisIndexT, AxisDataT*>::iterator AxisIteratorT;
typedef std::map<InputManager::ButtonIndexT, ButtonDataT*>::iterator ButtonIteratorT;
typedef std::map<InputManager::DPadIndexT, DPadDataT*>::iterator DPadIteratorT;





#endif // __INPUTMANAGER_H_
