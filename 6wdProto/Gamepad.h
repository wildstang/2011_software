#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

#include "GenericHID.h"

class DriverStation;

class Gamepad : public GenericHID
{
    public:
        typedef enum
        {
            kLeftXAxis, kLeftYAxis, kRightXAxis, kRightYAxis,
        } AxisType;

        typedef enum
        {
            kLeftTrigger, kLeftTop, kLeftBumper,
            kRightTrigger, kRightTop, kRightBumper,
            kTriangleButton, kCircleButton, kSquareButton, kXButton,
            kSelectButton, kStartButton, kNumButtons
        } ButtonType;

        typedef enum
        {
            kCenter, kUp, kUpLeft, kLeft,
            kDownLeft, kDown, kDownRight,
            kRight, kUpRight
        } DPadDirection;

        explicit Gamepad(UINT32 port);
        virtual ~Gamepad();

        virtual float GetX(JoystickHand hand = kRightHand);
        virtual float GetY(JoystickHand hand = kRightHand);
        virtual float GetZ();
        virtual float GetTwist();
        virtual float GetThrottle();
        virtual float GetAxis(AxisType axis);
        float GetRawAxis(UINT32 axis);

        virtual bool GetTrigger(JoystickHand hand = kRightHand);
        virtual bool GetTop(JoystickHand hand = kRightHand);
        virtual bool GetBumper(JoystickHand hand = kRightHand);
        virtual bool GetTriangleButton();
        virtual bool GetCircleButton();
        virtual bool GetSquareButton();
        virtual bool GetXButton();
        virtual bool GetSelectButton();
        virtual bool GetStartButton();
        virtual bool GetButton(ButtonType button);
        bool GetRawButton(UINT32 button);

        virtual float GetMagnitude(JoystickHand hand = kRightHand);
        virtual float GetDirectionRadians(JoystickHand hand = kRightHand);
        virtual float GetDirectionDegrees(JoystickHand hand = kRightHand);

        DPadDirection GetDPad();

    private:
        static const UINT32 kLeftXAxisNum  = 1;
        static const UINT32 kLeftYAxisNum  = 2;
        static const UINT32 kRightXAxisNum = 3;
        static const UINT32 kRightYAxisNum = 4;
        static const UINT32 kDPadXAxisNum  = 5;
        static const UINT32 kDPadYAxisNum  = 6;

        static const UINT32 kSquareButtonNum   = 1;
        static const UINT32 kXButtonNum        = 2;
        static const UINT32 kCircleButtonNum   = 3;
        static const UINT32 kTriangleButtonNum = 4;

        static const UINT32 kLeftBumperButtonNum   = 5;
        static const UINT32 kRightBumperButtonNum  = 6;
        static const UINT32 kLeftTriggerButtonNum  = 7;
        static const UINT32 kRightTriggerButtonNum = 8;

        static const UINT32 kSelectButtonNum = 9;
        static const UINT32 kStartButtonNum  = 10;

        static const UINT32 kLeftAnalogStickButtonNum  = 11;
        static const UINT32 kRightAnalogStickButtonNum = 12;

        DriverStation *ap_ds;
        UINT32 a_port;
};

#endif
