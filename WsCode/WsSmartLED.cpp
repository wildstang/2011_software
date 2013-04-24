#include "WsSmartLED.h"
#include "WPILib.h"

// Initialize singleton instance
WsSmartLED* WsSmartLED::ap_singletonInstance = NULL;

// Initialize static objects
DigitalOutput* WsSmartLED::ap_digOut1 = NULL;
DigitalOutput* WsSmartLED::ap_digOut2 = NULL;
DigitalOutput* WsSmartLED::ap_digOut3 = NULL;
DigitalOutput* WsSmartLED::ap_digOut4 = NULL;


// Return the singleton instance
WsSmartLED* WsSmartLED::Instance()
{
    if(ap_singletonInstance == NULL)
    {
        ap_singletonInstance = new WsSmartLED();
    }

    return ap_singletonInstance;
}


void WsSmartLED::Destroy()
{
    delete ap_digOut1;
    ap_digOut1 = NULL;
    
    delete ap_digOut2;
    ap_digOut2 = NULL;
    
    delete ap_digOut3;
    ap_digOut3 = NULL;
    
    delete ap_digOut4;
    ap_digOut4 = NULL;
    
}


WsSmartLED::WsSmartLED()
{
    a_currentCmd = LED_CODE_STARTED;
}

WsSmartLED::~WsSmartLED()
{
}

void WsSmartLED::assignDigOut(UINT32 digOut1,
                              UINT32 digOut2,
                              UINT32 digOut3,
                              UINT32 digOut4)
{
    ap_digOut1 = new DigitalOutput(digOut1);
    ap_digOut2 = new DigitalOutput(digOut2);
    ap_digOut3 = new DigitalOutput(digOut3);
    ap_digOut4 = new DigitalOutput(digOut4);
}

void WsSmartLED::setCommand(LedCmdT cmd)
{
    a_currentCmd = cmd;
}

WsSmartLED::LedCmdT WsSmartLED::getCommand(void)
{
    return a_currentCmd;
}

void WsSmartLED::reset(void)
{
    a_currentCmd = LED_CODE_STARTED;
    setCommand(a_currentCmd);
}

UINT8 WsSmartLED::getOutputValue(void)
{
    UINT8 cmdValue = LED_DONT_CARE;

    switch(a_currentCmd)
    {
        case LED_CODE_STARTED:
            cmdValue = LED_CODE_STARTED_VALUE;
            break;
        case LED_CODE_INITIALIZED:
            cmdValue = LED_CODE_INITIALIZED_VALUE;
            break;
        case LED_REQUEST_CIRCLE:
            cmdValue = LED_REQUEST_CIRCLE_VALUE;
            break;
        case LED_REQUEST_TRIANGLE:
            cmdValue = LED_REQUEST_TRIANGLE_VALUE;
            break;
        case LED_REQUEST_SQUARE:
            cmdValue = LED_REQUEST_SQUARE_VALUE;
            break;
        case LED_REQUEST_GREEN:
            cmdValue = LED_REQUEST_GREEN_VALUE;
            break;
        case LED_MINIBOT_ENABLED:
            cmdValue = LED_MINIBOT_ENABLED_VALUE;
            break;
        case LED_MINIBOT_LAUNCHED:
            cmdValue = LED_MINIBOT_LAUNCHED_VALUE;
            break;
        case LED_MINIBOT_COMPLETE:
            cmdValue = LED_MINIBOT_COMPLETE_VALUE;
            break;
        case LED_AUTO_SINGLE:
            cmdValue = LED_AUTO_SINGLE_VALUE;
            break;
        case LED_AUTO_DOUBLE_1:
            cmdValue = LED_AUTO_DOUBLE_1_VALUE;
            break;
        case LED_AUTO_DOUBLE_2:
            cmdValue = LED_AUTO_DOUBLE_2_VALUE;
            break;
        case LED_AUTO_DONE:
            cmdValue = LED_AUTO_DONE_VALUE;
            break;
        case LED_HAS_TUBE:
            cmdValue = LED_HAS_TUBE_VALUE;
            break;
        case LED_DONT_CARE:
            cmdValue = LED_DONT_CARE_VALUE;
            break;
        case LED_SHUTDOWN:
            cmdValue = LED_SHUTDOWN_VALUE;
            break;
        case LED_FLASHLIGHT:
            cmdValue = LED_FLASHLIGHT_VALUE;
            break;
        case LED_OFF:
            cmdValue = LED_OFF_VALUE;
            break;
        default:
            cmdValue = LED_DONT_CARE_VALUE;
            break;
    }

    return cmdValue;
}

void WsSmartLED::send(void)
{
    UINT32 bit0;
    UINT32 bit1;
    UINT32 bit2;
    UINT32 bit3;

    UINT8 cmdValue = getOutputValue();

    bit0 = (cmdValue & 1);
    bit1 = (cmdValue & 2) >> 1;
    bit2 = (cmdValue & 4) >> 2;
    bit3 = (cmdValue & 8) >> 3;
    //printf("SEND COMMAND - %d - %d%d%d%d\n", cmdValue, bit3, bit2, bit1, bit0);

    ap_digOut1->Set(bit0);
    ap_digOut2->Set(bit1);
    ap_digOut3->Set(bit2);
    ap_digOut4->Set(bit3);
}


