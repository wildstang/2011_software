#include "WsControlMethod6WD.h"

WsControlMethod6WD::WsControlMethod6WD(void)
{
        ap_polarStick = NULL;
        ap_driveVector = new WsDriveVector();
}

WsControlMethod6WD::~WsControlMethod6WD(void)
{
        delete ap_polarStick;
        ap_polarStick = NULL;
        
        delete ap_driveVector;
        ap_driveVector = NULL;
}

void WsControlMethod6WD::assignInputs(Gamepad* gamepad, GenericHID::JoystickHand hand)
{
    Gamepad::AxisType xAxis;
    Gamepad::AxisType yAxis;
    
    // Prevent double assignment
    if(ap_polarStick == NULL)
    {
        if(hand == GenericHID::kLeftHand)
        {
            xAxis = Gamepad::kLeftXAxis;
            yAxis = Gamepad::kLeftYAxis;
        }
        else
        {
            xAxis = Gamepad::kRightXAxis;
            yAxis = Gamepad::kRightYAxis;
        }
        
        assignInputs(gamepad, yAxis, xAxis);
    }
}

void WsControlMethod6WD::assignInputs(Gamepad* gamepad, Gamepad::AxisType throttleAxis, Gamepad::AxisType turnAxis)
{
        ap_polarStick = new WsControllerPolarStick(gamepad, turnAxis, throttleAxis);
}

void WsControlMethod6WD::readInputs(void)
{
    ap_driveVector->Reset();
    
    ap_driveVector->a_speed = ap_polarStick->GetRadius();
    ap_driveVector->a_direction = ap_polarStick->GetAngle();
    ap_driveVector->a_x = ap_polarStick->GetX();
    ap_driveVector->a_y = ap_polarStick->GetY();
}

void WsControlMethod6WD::getDriveVector(WsDriveVector* driveVector)
{
    driveVector->a_direction = ap_driveVector->a_direction;
    driveVector->a_speed = ap_driveVector->a_speed;
    driveVector->a_x = ap_driveVector->a_x;
    driveVector->a_y = ap_driveVector->a_y;
}


