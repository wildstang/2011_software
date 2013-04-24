#if !defined(_WSSMARTLED_H)
#define _WSSMARTLED_H

#include <stdio.h>

#include "WPILib.h"

class WsSmartLED
{
public:

    static const UINT8 LED_COLOR_RED = 0;
    static const UINT8 LED_COLOR_WHITE = 1;
    static const UINT8 LED_COLOR_BLUE = 2;
    static const UINT8 LED_COLOR_YELLOW = 3;
    static const UINT8 LED_COLOR_RED_BLINK = 4;
    static const UINT8 LED_COLOR_GREEN = 5;
    static const UINT8 LED_COLOR_BLUE_BLINK = 6;
    static const UINT8 LED_COLOR_GREEN_BLINK = 7;
    static const UINT8 LED_COLOR_RAINBOW_1 = 8;
    static const UINT8 LED_COLOR_RAINBOW_2 = 9;
    static const UINT8 LED_COLOR_RAINBOW_3 = 10;
    static const UINT8 LED_COLOR_RAINBOW_4 = 11;
    static const UINT8 LED_COLOR_RAINBOW_5 = 12;
    static const UINT8 LED_COLOR_RAINBOW_6 = 13;
    static const UINT8 LED_COLOR_DONT_CARE = 14;
    static const UINT8 LED_COLOR_OFF = 15;

    static const UINT8 LED_CODE_STARTED_VALUE      = LED_COLOR_RED_BLINK;
    static const UINT8 LED_CODE_INITIALIZED_VALUE  = LED_COLOR_RAINBOW_1;
    static const UINT8 LED_REQUEST_TRIANGLE_VALUE  = LED_COLOR_RED;
    static const UINT8 LED_REQUEST_CIRCLE_VALUE    = LED_COLOR_WHITE;
    static const UINT8 LED_REQUEST_SQUARE_VALUE    = LED_COLOR_BLUE;
    static const UINT8 LED_REQUEST_GREEN_VALUE     = LED_COLOR_GREEN;
    static const UINT8 LED_HAS_TUBE_VALUE          = LED_COLOR_YELLOW;
    static const UINT8 LED_MINIBOT_ENABLED_VALUE   = LED_COLOR_RAINBOW_2;
    static const UINT8 LED_MINIBOT_LAUNCHED_VALUE  = LED_COLOR_RAINBOW_3;
    static const UINT8 LED_MINIBOT_COMPLETE_VALUE  = LED_COLOR_GREEN_BLINK;
    // 9
    static const UINT8 LED_AUTO_SINGLE_VALUE       = LED_COLOR_RAINBOW_5;
    static const UINT8 LED_AUTO_DOUBLE_1_VALUE     = LED_COLOR_RAINBOW_6;
    static const UINT8 LED_AUTO_DOUBLE_2_VALUE     = LED_COLOR_RAINBOW_5;
    static const UINT8 LED_AUTO_DONE_VALUE         = LED_COLOR_RAINBOW_4;
    static const UINT8 LED_DONT_CARE_VALUE         = LED_COLOR_DONT_CARE;
    static const UINT8 LED_OFF_VALUE               = LED_COLOR_OFF;
    static const UINT8 LED_SHUTDOWN_VALUE          = LED_COLOR_BLUE_BLINK;
    static const UINT8 LED_FLASHLIGHT_VALUE        = LED_COLOR_WHITE;

    typedef enum
    {
        LED_CODE_STARTED,
        LED_CODE_INITIALIZED,
        LED_REQUEST_CIRCLE,
        LED_REQUEST_TRIANGLE,
        LED_REQUEST_SQUARE,
        LED_REQUEST_GREEN,
        LED_HAS_TUBE,
        LED_MINIBOT_ENABLED,
        LED_MINIBOT_LAUNCHED,
        LED_MINIBOT_COMPLETE,
        LED_AUTO_SINGLE,
        LED_AUTO_DOUBLE_1,
        LED_AUTO_DOUBLE_2,
        LED_AUTO_DONE,
        LED_DONT_CARE,
        LED_OFF,
        LED_SHUTDOWN,
        LED_FLASHLIGHT,
    } LedCmdT;

    static WsSmartLED* Instance();
    static void Destroy();
    ~WsSmartLED();
    void assignDigOut(UINT32 digOut1,
                      UINT32 digOut2,
                      UINT32 digOut3,
                      UINT32 digOut4);

    void setCommand(LedCmdT cmd);
    LedCmdT getCommand(void);
    UINT8 getOutputValue(void);
    void reset(void);
    void send(void);

private:
    WsSmartLED();
    static WsSmartLED* ap_singletonInstance;
    LedCmdT a_currentCmd;

    // These are static to allow them to be used in Destroy
    static DigitalOutput* ap_digOut1;
    static DigitalOutput* ap_digOut2;
    static DigitalOutput* ap_digOut3;
    static DigitalOutput* ap_digOut4;

};

#endif  //_WSSMARTLED_H

