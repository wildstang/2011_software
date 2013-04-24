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
    INT16  shoulderSpeed = 0;
    INT16  elbowSpeed = 0;

    DEADZONE(Oi_rx2_ry, SHOULDER_DEADZONE);
    DEADZONE(Oi_rx2_lx, CLAW_DEADZONE);

    elbowSpeed = Oi_rx2_lx;

    /* Calculate speeds based on joystick values */
    shoulderSpeed = Oi_rx2_ry;

    /* remap the speeds from 0-254 range to -127-127 range */
    shoulderSpeed = shoulderSpeed - 127;
    elbowSpeed = elbowSpeed - 127;

    if(Oi_rx2_l_trigger > TRIGGER_UP_PRESS)
    {
        elbowSpeed = CLAW_SPEED_OUT;
    }
    else if(Oi_rx2_l_trigger < TRIGGER_DOWN_PRESS)
    {
        elbowSpeed = CLAW_SPEED_IN;
    }
    else
    {
        elbowSpeed = (INT16)((elbowSpeed * CLAW_SENSITIVITY_NUM) / (float)CLAW_SENSITIVITY_DEN);
    }

    /* Keep the speeds in range */
    MIN_MAX(shoulderSpeed, -127, 127);
    MIN_MAX(elbowSpeed, -127, 127);

    /* assign motor values */
    motor_vals.shoulder = shoulderSpeed;
    motor_vals.elbow = elbowSpeed;

    /* DO NOT CHANGE ANYTHING BELOW THIS LINE */
    return;
}


