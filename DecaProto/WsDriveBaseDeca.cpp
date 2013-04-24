#include "WsDriveBaseDeca.h"
#include "WsDriveBase6WD.h"

WsDriveBaseDeca::WsDriveBaseDeca(void)
{
    ap_scDeca1 = NULL;
    ap_scDeca2 = NULL;
    ap_solDeca = NULL;
}

WsDriveBaseDeca::~WsDriveBaseDeca(void)
{
    if(ap_scDeca1 != NULL)
    {
       delete ap_scDeca1;
       ap_scDeca1 = NULL;
    }
    if(ap_scDeca2 != NULL)
    {
       delete ap_scDeca2;
       ap_scDeca2 = NULL;
    }
    if(ap_solDeca != NULL)
    {
        delete ap_solDeca;
        ap_solDeca = NULL;
    }
}

void WsDriveBaseDeca::assignControllers(SpeedController* scLeft1,
                                        SpeedController* scLeft2,
                                        SpeedController* scRight1,
                                        SpeedController* scRight2,
                                        SpeedController* scDeca1,
                                        SpeedController* scDeca2,
                                        Solenoid* solDeca)
{
    WsDriveBase6WD::assignControllers(scLeft1, scLeft2, scRight1, scRight2);
    ap_scDeca1 = scDeca1;
    ap_scDeca2 = scDeca2;
    ap_solDeca = solDeca;
}

void WsDriveBaseDeca::setOutputs(WsDriveVector* p_driveVector,
                                 WsDriveVector* p_decaVector,
                                 WsControlMethodDeca::WsDecaStateT decaState)
{
    bool state = false;
    WsDriveBase6WD::setOutputs(p_driveVector);
    
    ap_scDeca1->Set(-1 * p_decaVector->a_speed);
    ap_scDeca2->Set(p_decaVector->a_speed);
    
    if(decaState == WsControlMethodDeca::DECA_STATE_UP)
    {
        state = false;
    }
    else
    {
        state = true;
    }
    
    //printf("OUT: STATE: %d  SPEED %f\n", state, p_decaVector->a_speed);
    
    
    ap_solDeca->Set(state);
}