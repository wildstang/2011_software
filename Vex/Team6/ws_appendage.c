/*******************************************************************************
* FILE NAME: ws_appendage.c
*
* DESCRIPTION:
*
* USAGE:
*
*******************************************************************************/

#include "ifi_aliases.h"
#include "ifi_default.h"
#include "ifi_utilities.h"
#include "ws_includes.h"
#include "ws_io.h"
#include "ws_appendage.h"

/*******************************************************************************
* FUNCTION NAME: processAppendage
* PURPOSE:       Process all inputs related to appendages
* CALLED FROM:   Process_Data_From_Master_uP()
* ARGUMENTS:
* RETURNS:       none
*******************************************************************************/
void processAppendage(void)
{
    /* DO NOT CHANGE ANYTHING ABOVE THIS LINE */
    INT16  lift1Speed = 0;
    INT16  lift2Speed = 0;
    INT16  gripperSpeed = 0;

    DEADZONE(Oi_rx2_ly, LIFT_DEADZONE);
    DEADZONE(Oi_rx2_ry, LIFT_DEADZONE);

    /* Calculate speeds based on joystick values */
    lift1Speed = Oi_rx2_ly;
    lift2Speed = Oi_rx2_ry;

    /* remap the speeds from 0-254 range to -127-127 range */
    lift1Speed = lift1Speed - 127;
    lift2Speed = lift2Speed - 127;

    if(Oi_rx2_l_trigger > TRIGGER_UP_PRESS)
    {
        gripperSpeed = GRIPPER_SPEED_OUT;
    }
    else if(Oi_rx2_l_trigger < TRIGGER_DOWN_PRESS)
    {
        gripperSpeed = GRIPPER_SPEED_IN;
    }

    /* Keep the speeds in range */
    MIN_MAX(lift1Speed, -127, 127);
    MIN_MAX(lift2Speed, -127, 127);
    MIN_MAX(gripperSpeed, -127, 127);

    /* assign motor values */
    motor_vals.lift_1 = lift1Speed;
    motor_vals.lift_2 = lift2Speed;
    motor_vals.gripper = gripperSpeed;












    /* DO NOT CHANGE ANYTHING BELOW THIS LINE */
    return;
}


