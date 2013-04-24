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
#include "ws_drive.h"
#include "ws_appendage.h"

/*******************************************************************************
* FUNCTION NAME: processDrive
* PURPOSE:       Process all inputs related to driving
* CALLED FROM:   Process_Data_From_Master_uP()
* ARGUMENTS:
* RETURNS:       none
*******************************************************************************/
void processAutonomous(void)
{
  static UINT16 loopCount = 0;
  UINT16 maxLoops = 0;
  UINT16 speed = 127;
  set_motor_vals_off();

  /* assign motor values for right & left drive speeds */
  //motor_vals.left_drive = 140;
  //motor_vals.right_drive = -140;

  // 0 means a jumper is in place


  if(Dig_in_01 == 0)
  {
      speed = 0;
      maxLoops = 40;
  }
  else if(Dig_in_02 == 0)
  {
      speed = 0;
      maxLoops = 80;
  }
  else if(Dig_in_03 == 0)
  {
      speed = 0;
      maxLoops = 120;
  }
  else if(Dig_in_04 == 0)
  {
      speed = 255;
      maxLoops = 40;
  }
  else if(Dig_in_05 == 0)
  {
      speed = 255;
      maxLoops = 80;
  }
  else if(Dig_in_06 == 0)
  {
      speed = 255;
      maxLoops = 120;
  }
  else
  {
      speed = 127;
      maxLoops = 0;
  }

  if(loopCount < maxLoops)
  {
      Oi_rx1_ly = speed;
      Oi_rx1_ry = speed;
  }
  else
  {
      Oi_rx1_ly = 127;
      Oi_rx1_ry = 127;
  }

  loopCount++;

  processDrive(FALSE);
  processAppendage();


  return;
}


