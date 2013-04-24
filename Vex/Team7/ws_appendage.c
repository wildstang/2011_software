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
    INT16  arm_speed = 0;

    DEADZONE(Oi_rx2_ry, ARM_DEADZONE);

    arm_speed = Oi_rx2_ry;

    /* remap the speeds from 0-254 range to -127-127 range */
    arm_speed = arm_speed - 127;

    if(Oi_rx2_l_trigger > BUTTON_UP_THRESH)
    {
        arm_speed = (arm_speed * ARM_ANTITURBO_NUM) / ARM_ANTITURBO_DENOM;
    }

    /* Keep the speeds in range */
    MIN_MAX(arm_speed, -127, 127);

    /* assign motor values */

    motor_vals.arm = arm_speed;

    /* DO NOT CHANGE ANYTHING BELOW THIS LINE */
    return;
}


