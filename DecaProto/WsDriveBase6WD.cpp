#include "WsDriveBase6WD.h"
#include "WsTrig.h"

WsDriveBase6WD::WsDriveBase6WD(void)
{
    
}

WsDriveBase6WD::~WsDriveBase6WD(void)
{
    
}
        
void WsDriveBase6WD::assignControllers(SpeedController* scLeft1,
                                       SpeedController* scLeft2,
                                       SpeedController* scRight1,
                                       SpeedController* scRight2)
{

    ap_scLeft1 = scLeft1;
    ap_scLeft2 = scLeft2;
    ap_scRight1 = scRight1;
    ap_scRight2 = scRight2;
}
        
void WsDriveBase6WD::setOutputs(WsDriveVector* p_driveVector)
{
    
    float direction = 0;
    float speed = 0;
    
    float leftSpeed = 0;
    float rightSpeed = 0;
    
    if(p_driveVector != NULL)
    {
        direction = p_driveVector->a_direction;
        speed = p_driveVector->a_speed;
    }
    
    leftSpeed  = speed * (COSDEG(direction) + SINDEG(direction));
    rightSpeed = speed * (COSDEG(direction) - SINDEG(direction));
 
    /*
    printf("DIR: %f  SPEED: %f  L: %f  R: %f\n",
            direction, speed, leftSpeed, rightSpeed);
            */
    
    
    
    ap_scLeft1->Set(leftSpeed);
    ap_scLeft2->Set(leftSpeed);
    ap_scRight1->Set(rightSpeed);
    ap_scRight2->Set(rightSpeed);
}
