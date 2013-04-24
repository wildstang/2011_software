/*******************************************************************************
* FILE NAME: ws_autonomous.c
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
#include "ws_autonomous.h"
#include "ws_general.h"

/*******************************************************************************
* FUNCTION NAME: processDrive
* PURPOSE:       Process all inputs related to driving
* CALLED FROM:   Process_Data_From_Master_uP()
* ARGUMENTS:
* RETURNS:       none
*******************************************************************************/
void processAutonomous(void)
{
  set_motor_vals_off();

  /* assign motor values for right & left drive speeds */
  //motor_vals.left_drive = 140;
  //motor_vals.right_drive = -140;
  return;
}


