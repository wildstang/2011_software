#include "stubs.h"
#include "Gamepad.h"
#if !STUBBED
#include "DriverStation.h"
#include "Utility.h"
#include "WPIStatus.h"
#endif
#include <math.h>


GamepadDPad::GamepadDPad(UINT32 port)
    : ap_ds(NULL)
    , a_port(port)
    , a_dPadXAxisNum(5)
    , a_dPadYAxisNum(6)
{
    printf("CREATE DPAD(%d)\n", port);
    ap_ds = DriverStation::GetInstance();
}

GamepadDPad::GamepadDPad(UINT32 port, UINT32 xAxis, UINT32 yAxis)
    : ap_ds(NULL)
    , a_port(port)
    , a_dPadXAxisNum(xAxis)
    , a_dPadYAxisNum(yAxis)
{
    printf("CREATE DPAD(%d)\n", port);
    ap_ds = DriverStation::GetInstance();
}

GamepadDPad::~GamepadDPad()
{
    printf("DELETE DPAD\n");
}

GamepadDPad::DPadDirection GamepadDPad::GetDPad()
{
    float x = ap_ds->GetStickAxis(a_port, a_dPadXAxisNum);
    float y = ap_ds->GetStickAxis(a_port, a_dPadYAxisNum);

#if STUBBED
    static float tempX = 0.0;
    static float tempY = 0.0;
    static int testIteration = 1;

    switch(testIteration)
    {
        case 1:
            tempX = -.6;
            tempY = -.6;
            break;
        case 2:
            tempX = -.6;
            tempY = .6;
            break;
        case 3:
            tempX = .6;
            tempY = .6;
            break;
        case 4:
            tempX = .6;
            tempY = -.6;
            break;
        case 5:
            tempX = .5;
            tempY = -.6;
            break;
        case 6:
            tempX = -.6;
            tempY = -.5;
            break;
        case 7:
            tempX = -.5;
            tempY = .6;
            break;
        case 8:
            tempX = .6;
            tempY = .5;
            break;
        case 9:
            tempX = .5;
            tempY = .5;
            break;
        default:
            tempX =  -.6;
            tempY =  -.6;
            testIteration = 1;

    }
    testIteration++;

    x = tempX;
    y = tempY;

#endif

    if (x < -0.5 && y < -0.5)
        return kUpLeft;
    if (x < -0.5 && y > 0.5)
        return kDownLeft;
    if (x > 0.5 && y > 0.5)
        return kDownRight;
    if (x > 0.5 && y < -0.5)
        return kUpRight;
    if (y < -0.5)
        return kUp;
    if (x < -0.5)
        return kLeft;
    if (y > 0.5)
        return kDown;
    if (x > 0.5)
        return kRight;

    return kCenter;
}

/**
 * Construct an instance of a Gamepad.
 *
 * @param port The port on the driver station that the gamepad is plugged into.
 */
Gamepad::Gamepad(UINT32 port)
        : ap_ds (NULL)
        , ap_dPad (NULL)
        , a_port (port)
{
    printf("CREATE GAMEPAD(%d)\n", port);
    ap_ds = DriverStation::GetInstance();
    ap_dPad = new GamepadDPad(port);
}

Gamepad::~Gamepad()
{

    printf("DELETE GAMEPAD\n");
    delete ap_dPad;
    ap_dPad = NULL;
}

/**
 * Get the X value of the left or right stick on the gamepad.
 */
float Gamepad::GetX(JoystickHand hand)
{
    if (hand == kLeftHand)
    {
        return GetRawAxis(kLeftXAxisNum);
    }
    else if (hand == kRightHand)
    {
        return GetRawAxis(kRightXAxisNum);
    }

    wpi_assert(false);
    return 0;
}

/**
 * Get the Y value of the left or right stick on the gamepad.
 */
float Gamepad::GetY(JoystickHand hand)
{
    if (hand == kLeftHand)
    {
        return GetRawAxis(kLeftYAxisNum);
    }
    else if (hand == kRightHand)
    {
        return GetRawAxis(kRightYAxisNum);
    }

    wpi_assert(false);
    return 0;
}

/**
 * Get the Z value of the gamepad.
 *
 * This is not supported for the Gamepad; it is only here to complete the GenericHID interface.
 */
float Gamepad::GetZ()
{
    wpi_assert(false);
    return 0;
}

/**
 * Get the twist value of the gamepad.
 *
 * This is not supported for the Gamepad; it is only here to complete the GenericHID interface.
 */
float Gamepad::GetTwist()
{
    wpi_assert(false);
    return 0;
}

/**
 * Get the throttle value of the gamepad.
 *
 * This is not supported for the Gamepad; it is only here to complete the GenericHID interface.
 */
float Gamepad::GetThrottle()
{
    wpi_assert(false);
    return 0;
}

/**
 * Get the value of the axis.
 *
 * @param axis The axis to read [1-6].
 * @return The value of the axis.
 */
float Gamepad::GetRawAxis(UINT32 axis)
{
    return ap_ds->GetStickAxis(a_port, axis);
}

/**
 * For the current gamepad, return the axis determined by the argument.
 *
 * This is for cases where the joystick axis is returned programatically, otherwise one of the
 * previous functions would be preferable (for example GetX()).
 *
 * @param axis The axis to read.
 * @return The value of the axis.
 */
float Gamepad::GetAxis(AxisType axis)
{
    switch(axis)
    {
        case kLeftXAxis: return GetX(kLeftHand);
        case kLeftYAxis: return GetY(kLeftHand);
        case kRightXAxis: return GetX(kRightHand);
        case kRightYAxis: return GetY(kRightHand);
        default:
            wpi_fatal(BadJoystickAxis);
            return 0.0;
    }
}

/**
 * Get the state of the left or right trigger on the gamepad.
 */
bool Gamepad::GetTrigger(JoystickHand hand)
{
    if (hand == kLeftHand)
    {
        return GetRawButton(kLeftTriggerButtonNum);
    }
    else if (hand == kRightHand)
    {
        return GetRawButton(kRightTriggerButtonNum);
    }

    wpi_assert(false);
    return 0;
}

/**
 * Get the state of the left or right top on the gamepad.
 */
bool Gamepad::GetTop(JoystickHand hand)
{
    if (hand == kLeftHand)
    {
        return GetRawButton(kLeftAnalogStickButtonNum);
    }
    else if (hand == kRightHand)
    {
        return GetRawButton(kRightAnalogStickButtonNum);
    }

    wpi_assert(false);
    return 0;
}

/**
 * Get the state of the left or right bumper on the gamepad.
 */
bool Gamepad::GetBumper(JoystickHand hand)
{
    if (hand == kLeftHand)
    {
        return GetRawButton(kLeftBumperButtonNum);
    }
    else if (hand == kRightHand)
    {
        return GetRawButton(kRightBumperButtonNum);
    }

    wpi_assert(false);
    return 0;
}

/**
 * Get the state of the triangle button on the gamepad.
 */
bool Gamepad::GetTriangleButton()
{
    return GetRawButton(kTriangleButtonNum);
}

/**
 * Get the state of the circle button on the gamepad.
 */
bool Gamepad::GetCircleButton()
{
    return GetRawButton(kCircleButtonNum);
}

/**
 * Get the state of the square button on the gamepad.
 */
bool Gamepad::GetSquareButton()
{
    return GetRawButton(kSquareButtonNum);
}

/**
 * Get the state of the x button on the gamepad.
 */
bool Gamepad::GetXButton()
{
    return GetRawButton(kXButtonNum);
}
/**
 * Get the state of the select button on the gamepad.
 */
bool Gamepad::GetSelectButton()
{
    return GetRawButton(kSelectButtonNum);
}

/**
 * Get the state of the start button on the gamepad.
 */
bool Gamepad::GetStartButton()
{
    return GetRawButton(kStartButtonNum);
}


/**
 * Get the button value for buttons 1 through 12.
 *
 * The buttons are returned in a single 16 bit value with one bit representing
 * the state of each button. The appropriate button is returned as a boolean
 * value.
 *
 * @param button The button number to be read.
 * @return The state of the button.
 **/
bool Gamepad::GetRawButton(UINT32 button)
{
    return ((0x1 << (button-1)) & ap_ds->GetStickButtons(a_port)) != 0;
}

/**
 * Get buttons based on an enumerated type.
 *
 * The button type will be looked up in the list of buttons and then read.
 *
 * @param button The type of button to read.
 * @return The state of the button.
 */
bool Gamepad::GetButton(ButtonType button)
{
    switch (button)
    {
        case kLeftTrigger: return GetTrigger(kLeftHand);
        case kLeftTop: return GetTop(kLeftHand);
        case kLeftBumper: return GetBumper(kLeftHand);

        case kRightTrigger: return GetTrigger(kRightHand);
        case kRightTop: return GetTop(kRightHand);
        case kRightBumper: return GetBumper(kRightHand);

        case kTriangleButton: return GetTriangleButton();
        case kCircleButton: return GetCircleButton();
        case kSquareButton: return GetSquareButton();
        case kXButton: return GetXButton();
        
        case kSelectButton: return GetSelectButton();
        case kStartButton: return GetStartButton();

        default:
            wpi_assert(false);
            return false;
    }
}

/**
 * Based on the enumerated type, return the low level axis number
 *
 * @param axis The axis to look up
 * @return The axis number that the DS sees
 */
UINT32 Gamepad::GetAxisNumber(AxisType button)
{
    switch (button)
    {
        case kLeftXAxis : return kLeftXAxisNum;
        case kLeftYAxis : return kLeftYAxisNum;
        case kRightXAxis : return kRightXAxisNum;
        case kRightYAxis : return kRightYAxisNum;

        default:
            wpi_assert(false);
            return 0;
    }
}
/**
 * Based on the enumerated type, return the low level button number
 *
 * @param button The button to look up
 * @return The button number that the DS sees
 */
UINT32 Gamepad::GetButtonNumber(ButtonType button)
{
    switch (button)
    {
        case kLeftTrigger: return kLeftTriggerButtonNum;
        case kLeftTop: return kLeftAnalogStickButtonNum;
        case kLeftBumper: return kLeftBumperButtonNum;

        case kRightTrigger: return kRightTriggerButtonNum;
        case kRightTop: return kRightAnalogStickButtonNum;
        case kRightBumper: return kRightBumperButtonNum;

        case kTriangleButton: return kTriangleButtonNum;
        case kCircleButton: return kCircleButtonNum;
        case kSquareButton: return kSquareButtonNum;
        case kXButton: return kXButtonNum;

        case kSelectButton: return kSelectButtonNum;
        case kStartButton: return kStartButtonNum;

        default:
            wpi_assert(false);
            return 0;
    }
}

/**
 * Get the magnitude of the direction vector formed by the joystick's
 * current position relative to its origin
 *
 * @return The magnitude of the direction vector
 */
float Gamepad::GetMagnitude(JoystickHand hand)
{
    return sqrt(pow(GetX(hand), 2) + pow(GetY(hand), 2));
}

/**
 * Get the direction of the vector formed by the joystick and its origin
 * in radians
 *
 * @return The direction of the vector in radians
 */
float Gamepad::GetDirectionRadians(JoystickHand hand)
{
    return atan2(GetX(hand), -GetY(hand));
}

/**
 * Get the direction of the vector formed by the joystick and its origin
 * in degrees
 *
 * uses acos(-1) to represent Pi due to absence of readily accessable Pi
 * constant in C++
 *
 * @return The direction of the vector in degrees
 */
float Gamepad::GetDirectionDegrees(JoystickHand hand)
{
    return (180 / acos(-1)) * GetDirectionRadians(hand);
}

/**
 * Get the direction of the D-pad.
 */
GamepadDPad::DPadDirection Gamepad::GetDPad()
{
    return ap_dPad->GetDPad();
}

