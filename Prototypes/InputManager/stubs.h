#ifndef __STUBS_H_
#define __STUBS_H_

#define STUBBED 1

#if STUBBED

#include <stdio.h>

typedef unsigned int UINT32;

extern int BadJoystickAxis;
extern void wpi_assert(bool b);
extern void wpi_fatal(int i);

class GenericHID
{
    public:
        typedef enum
        {
            kRightHand,
            kLeftHand,
        } JoystickHand;
};

class DriverStation
{
    public:

        static DriverStation* GetInstance(void)
        {
            if(ap_singletonInstance == NULL)
            {
                ap_singletonInstance = new DriverStation();
            }
            return ap_singletonInstance;
        }

        float GetStickAxis(UINT32 port, UINT32 axis)
        {
            float value = a_stickValue;
            return value;
        }

        short GetStickButtons(UINT32 stick)
        {
            return 0;
        }


    private:

        DriverStation()
        {
            a_stickValue = 0.0;
        }

        static DriverStation* ap_singletonInstance;

        float a_stickValue;


};

class WsControllerButton
{
    public:
        WsControllerButton(UINT32 devicePort, UINT32 buttonNumber)
        {
            printf("CREATE BUTTON(%d, %d)\n", devicePort, buttonNumber);
            a_state = false;
        }
        virtual ~WsControllerButton()
        {
            printf("DELETE BUTTON\n");
        }

        bool GetState()
        {
            bool state = a_state;
            a_state = !a_state;
            return state;
        }

        virtual void Reset()
        {
        }

    private:
        bool a_state;
};

class WsControllerStickyButton : public WsControllerButton
{
    public:
        WsControllerStickyButton(UINT32 devicePort, UINT32 buttonNumber)
            : WsControllerButton(devicePort, buttonNumber)
        {
            printf("CREATE STICKY BUTTON(%d, %d)\n", devicePort, buttonNumber);
        }
        virtual ~WsControllerStickyButton()
        {
            printf("DELETE STICKY BUTTON\n");
        }
};

class WsControllerMultiStickyButton : public WsControllerButton
{
    public:
        WsControllerMultiStickyButton(UINT32 devicePort, UINT32 onButtonNumber, UINT32 offButtonNumber)
            : WsControllerButton(devicePort, onButtonNumber)
        {
            printf("CREATE MULTISTICKY BUTTON(%d, %d, %d)\n", devicePort, onButtonNumber, offButtonNumber);
        }
        virtual ~WsControllerMultiStickyButton()
        {
            printf("DELETE MULTISTICKY BUTTON\n");
        }
};

class WsControllerTapButton : public WsControllerButton
{
    public:
        WsControllerTapButton(UINT32 devicePort, UINT32 buttonNumber)
            : WsControllerButton(devicePort, buttonNumber)
        {
            printf("CREATE TAP BUTTON(%d, %d)\n", devicePort, buttonNumber);
        }
        virtual ~WsControllerTapButton()
        {
            printf("DELETE TAP BUTTON\n");
        }
};

class WsControllerAxis
{
    public:
        WsControllerAxis(UINT32 devicePort, UINT32 axis, bool invert)
        {
            printf("CREATE CONTROLLER AXIS(%d, %d)\n", devicePort, axis);
            a_value = 0.0;
        }

        ~WsControllerAxis()
        {
            printf("DELETE AXIS\n");
        }

        float GetValue()
        {
            float value = a_value;

            a_value++;

            return value;
        }

    private:
        float a_value;
};

#endif






#endif
