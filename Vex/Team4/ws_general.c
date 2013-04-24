/*******************************************************************************
* FILE NAME: ws_general.c
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
#include "ws_general.h"


/*******************************************************************************
* FUNCTION NAME: set_motor_vals_off()
* PURPOSE:       Turns all motors off in motor_vals struct
* ARGUMENTS:     none
* RETURNS:       none
*
*******************************************************************************/
void set_motor_vals_off(void)
{
  /*********  ADD CODE BELOW HERE ***********/
  motor_vals.left_drive = 0;
  motor_vals.right_drive = 0;

  /*********  ADD CODE ABOVE HERE ***********/
}



