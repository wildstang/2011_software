/*******************************************************************************
* FILE NAME: ws_drive.c
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
#include "ws_drive.h"

/*******************************************************************************
* FUNCTION NAME: processDrive
* PURPOSE:       Process all inputs related to driving
* CALLED FROM:   Process_Data_From_Master_uP()
* ARGUMENTS:
* RETURNS:       none
*******************************************************************************/
void processDrive(UINT8 use_deadzone)
{
  INT16  left_drive_speed;
  INT16  right_drive_speed;

  if(use_deadzone == TRUE)
  {
      DEADZONE(Oi_rx1_ly, DRIVE_DEADZONE);
      DEADZONE(Oi_rx1_ry, DRIVE_DEADZONE);
  }

  /* Calculate speeds based on joystick values */
  left_drive_speed = Oi_rx1_ly;
  right_drive_speed = Oi_rx1_ry;

  /* remap the speeds from 0-254 range to -127-127 range */
  left_drive_speed = left_drive_speed - 127;
  right_drive_speed = right_drive_speed - 127;

  left_drive_speed = left_drive_speed * -1;

  /*** DO ANY SPECIAL PROCESSING HERE ***/
  if(Oi_rx1_r_trigger > TRIGGER_UP_PRESS)
  {
      left_drive_speed = (INT16)((left_drive_speed * DRIVE_ANTITURBO_NUM) / (float)DRIVE_ANTITURBO_DEN);
      right_drive_speed = (INT16)((right_drive_speed * DRIVE_ANTITURBO_NUM) / (float)DRIVE_ANTITURBO_DEN);
  }


  /* Keep the speeds in range */
  MIN_MAX(left_drive_speed, -127, 127);
  MIN_MAX(right_drive_speed, -127, 127);

  /* assign motor values from right & left drive speeds */
  motor_vals.left_drive = left_drive_speed;
  motor_vals.right_drive = right_drive_speed;

  return;
}


