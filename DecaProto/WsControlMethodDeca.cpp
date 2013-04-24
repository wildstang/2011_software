#include "WsControlMethodDeca.h"

WsControlMethodDeca::WsControlMethodDeca(void)
{
    ap_gamepad = NULL;
    ap_decaButton = NULL;
    ap_decaVector = new WsDriveVector();
    a_decaAxis = Gamepad::kLeftXAxis;
    a_decaState = DECA_STATE_UP;
}
WsControlMethodDeca::~WsControlMethodDeca(void)
{
    if(ap_gamepad != NULL)
    {
        delete ap_gamepad;
        ap_gamepad = NULL;
    }
    if(ap_decaButton != NULL)
    {
        delete ap_decaButton;
        ap_decaButton = NULL;
    }
    if(ap_decaVector != NULL)
    {
        delete ap_decaVector;
        ap_decaVector = NULL;
    }
}

void WsControlMethodDeca::assignInputs(Gamepad* gamepad,
                                       Gamepad::AxisType driveAxis,
                                       Gamepad::AxisType turnAxis,
                                       Gamepad::ButtonType decaButton,
                                       Gamepad::AxisType decaAxis)
{
    WsControlMethod6WD::assignInputs(gamepad, driveAxis, turnAxis);
    ap_gamepad = gamepad;
    ap_decaButton = new WsButton(gamepad, decaButton);
    a_decaAxis = decaAxis;
 
}
                                
void WsControlMethodDeca::readInputs(void)
{
    bool decaButtonState = false;
    float decaAxisValue = 0;
    
    if( ap_decaButton != NULL)
    {
        decaButtonState = ap_decaButton->GetState();
    }
    
    if(ap_gamepad != NULL)
    {
        decaAxisValue = ap_gamepad->GetAxis(a_decaAxis);
    }
    
    // Reset the deca vector every loop
    ap_decaVector->Reset();
    
    if(decaButtonState == false)
    {
        WsControlMethod6WD::readInputs();
        a_decaState = DECA_STATE_UP;
    }
    else
    {
        // Turn the drive vector off because we're in deca mode
        ap_driveVector->Reset();
        
        ap_decaVector->a_speed = ap_gamepad->GetAxis(a_decaAxis);
        ap_decaVector->a_direction = 0;
        ap_decaVector->a_x = 0;
        ap_decaVector->a_y = ap_decaVector->a_speed;
        
        a_decaState = DECA_STATE_DOWN;
    }
}

void WsControlMethodDeca::getDecaState(WsDecaStateT* decaState, WsDriveVector* decaVector)
{
    *decaState = a_decaState;
    
    decaVector->a_direction = ap_decaVector->a_direction;
    decaVector->a_speed = ap_decaVector->a_speed;
    decaVector->a_x = ap_decaVector->a_x;
    decaVector->a_y = ap_decaVector->a_y;
}
        