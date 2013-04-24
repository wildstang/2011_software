/*******************************************************************************
* FILE NAME: ws_io.c
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

/*******************************************************************************
* FUNCTION NAME: assign_outputs_slow
* PURPOSE:       assign motor speeds to pwm outputs
* CALLED FROM:
* ARGUMENTS:
* RETURNS:       none
*******************************************************************************/
void assign_outputs_slow()
{

  /****************************************************************************
   *
   * This section assigns PWM outputs
   *
   ***************************************************************************/
  pwm01 = 127;
  pwm02 = 127;
  pwm03 = 127;
  pwm04 = 127;
  pwm05 = 127;
  pwm06 = 127;
  pwm07 = 127;
  pwm08 = 127;
  pwm09 = 127;
  pwm10 = 127;
  pwm11 = 127;
  pwm12 = 127;

  /*
  printf("left: %d right: %d\r", (int)motor_vals.left_drive,
         (int)motor_vals.right_drive);
  */

  /* drive motors */
  Rc_analog_out_drive_left = 127 + (INT16)motor_vals.left_drive;
  Rc_analog_out_drive_right = 127 + (INT16)motor_vals.right_drive;

  Rc_analog_out_lift_1l = 127 - (INT16)motor_vals.lift_1;
  Rc_analog_out_lift_1r = 127 + (INT16)motor_vals.lift_1;
  Rc_analog_out_lift_2  = 127 + (INT16)motor_vals.lift_2;
  Rc_analog_out_gripper_l = 127 + (INT16)motor_vals.gripper;
  Rc_analog_out_gripper_r = 127 - (INT16)motor_vals.gripper;

  /*
  printf("IN %3d %3d   OUT %4d %4d\r",
          motor_vals.left_drive, motor_vals.right_drive,
          Rc_analog_out_drive_l, Rc_analog_out_drive_r);
          */

  return;
}




void io_print_oi_inputs()
{
    /*
    printf("p1 LX:%03d LY:%03d RX:%03d RY:%03d LT:%03d RT:%03d\r",
           Oi_rx1_lx, Oi_rx1_ly, Oi_rx1_rx, Oi_rx1_ry,
           Oi_rx1_l_trigger, Oi_rx1_r_trigger);
    printf("p2 LX:%03d LY:%03d RX:%03d RY:%03d LT:%03d RT:%03d\r",
           Oi_rx2_lx, Oi_rx2_ly, Oi_rx2_rx, Oi_rx2_ry,
           Oi_rx2_l_trigger, Oi_rx2_r_trigger);
    */

  return;
}


void io_print_rc_inputs()
{
  /*
  printf("01 %d 02 %d 03 %d 04 %d 05 %d 06 %d 07 %d 08 %d 09 %d\r",
          rc_dig_in01, rc_dig_in02, rc_dig_in03, rc_dig_in04, 
          rc_dig_in05, rc_dig_in06, rc_dig_in07, rc_dig_in08, 
          rc_dig_in09);
  printf("10 %d 11 %d 12 %d 13 %d 14 %d 15 %d 16 %d 17 %d 18 %d\r",
          rc_dig_in10, rc_dig_in11, rc_dig_in12, 
          rc_dig_in13, rc_dig_in14, rc_dig_in15, rc_dig_in16, 
          rc_dig_in17, rc_dig_in18);
  printf("\r");
  */
  return;
}





