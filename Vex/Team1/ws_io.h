/*******************************************************************************
* FILE NAME: ws_io.h
*
* DESCRIPTION:
*  This is the include file which corresponds to io_code.c
*
*  It contains some aliases and function prototypes used in those files.
*
* USAGE:
*  If you add your own routines to those files, this is a good place to add
*  your custom macros (aliases), type definitions, and function prototypes.
*******************************************************************************/

#ifndef __ws_io_h_
#define __ws_io_h_

/******************************* TYPEDEFS *************************************/

/******************************** MACROS **************************************/

/***************************** DEFINITIONS ************************************/

/**************************************************************
 * Inputs
 **************************************************************/
/*
    | 0
    |
0 ----- 255
    |
    | 255

   port 1
   Lx - 4
   Ly - 3
   Rx - 1
   Ry - 2
   Left Trigger - 5 - 0 down 127 not pressed(both) 255 up
   Right Trigger - 6 - 0 down 127 not pressed(both) 255 up

   port 2
   Lx - 10
   Ly - 9
   Rx - 8
   Ry - 7
   Left Trigger - 11 - 0 down 127 not pressed(both) 255 up
   Right Trigger - 12 - 0 down 127 not pressed(both) 255 up

   */


#define TRIGGER_UP_PRESS  (127 + 30)
#define TRIGGER_DOWN_PRESS  (127 -  30)

/***** Joystick Inputs *****/
#define Oi_rx1_lx         PWM_in4
#define Oi_rx1_ly         PWM_in3
#define Oi_rx1_rx         PWM_in1
#define Oi_rx1_ry         PWM_in2
#define Oi_rx1_l_trigger  PWM_in5
#define Oi_rx1_r_trigger  PWM_in6

#define Oi_rx2_lx         PWM_in10
#define Oi_rx2_ly         PWM_in9
#define Oi_rx2_rx         PWM_in7
#define Oi_rx2_ry         PWM_in8
#define Oi_rx2_l_trigger  PWM_in11
#define Oi_rx2_r_trigger  PWM_in12

/***** RC Analog Inputs *****/
#define Analog_in_01                     rc_ana_in01
#define Analog_in_02                     rc_ana_in02
#define Analog_in_03                     rc_ana_in03
#define Analog_in_04                     rc_ana_in04
#define Analog_in_05                     rc_ana_in05
#define Analog_in_06                     rc_ana_in06
#define Analog_in_07                     rc_ana_in07
#define Analog_in_08                     rc_ana_in08
#define Analog_in_09                     rc_ana_in09
#define Analog_in_10                     rc_ana_in10
#define Analog_in_11                     rc_ana_in11
#define Analog_in_12                     rc_ana_in12
#define Analog_in_13                     rc_ana_in13
#define Analog_in_14                     rc_ana_in14
#define Analog_in_15                     rc_ana_in15
#define Analog_in_16                     rc_ana_in16


/* The digital inputs / outputs are the same pins, a pin can either be an
   output or an input, not both */
/***** RC Digital Inputs *****/
#define Dig_in_01                 rc_dig_in01
#define Dig_in_02                 rc_dig_in02
#define Dig_in_03                 rc_dig_in03
#define Dig_in_04                 rc_dig_in04
#define Dig_in_05                 rc_dig_in05
#define Dig_in_06                 rc_dig_in06
#define Dig_in_07                 rc_dig_in07
#define Dig_in_08                 rc_dig_in08
#define Dig_in_09                 rc_dig_in09
#define Dig_in_10                 rc_dig_in10
#define Dig_in_11                 rc_dig_in11
#define Dig_in_12                 rc_dig_in12
#define Dig_in_13                 rc_dig_in13
#define Dig_in_14                 rc_dig_in14
#define Dig_in_15                 rc_dig_in15
#define Dig_in_16                 rc_dig_in16
#define Dig_in_17                 rc_dig_in17
#define Dig_in_18                 rc_dig_in18

/***** RC Digital Outputs *****/
#define Dig_out_01                rc_dig_out01
#define Dig_out_02                rc_dig_out02
#define Dig_out_03                rc_dig_out03
#define Dig_out_04                rc_dig_out04
#define Dig_out_05                rc_dig_out05
#define Dig_out_06                rc_dig_out06
#define Dig_out_07                rc_dig_out07
#define Dig_out_08                rc_dig_out08
#define Dig_out_09                rc_dig_out09
#define Dig_out_10                rc_dig_out10
#define Dig_out_11                rc_dig_out11
#define Dig_out_12                rc_dig_out12
#define Dig_out_13                rc_dig_out13
#define Dig_out_14                rc_dig_out14
#define Dig_out_15                rc_dig_out15
#define Dig_out_16                rc_dig_out16
#define Dig_out_17                rc_dig_out17
#define Dig_out_18                rc_dig_out18

/**************************************************************
 * Outputs
 **************************************************************/
/***** RC Analog Outputs *****/

#define Rc_analog_out_drive_lf     pwm01
#define Rc_analog_out_drive_lb     pwm02
#define Rc_analog_out_drive_rf     pwm03
#define Rc_analog_out_drive_rb     pwm04
#define Rc_analog_out_shoulder_l   pwm05
#define Rc_analog_out_shoulder_r   pwm06
#define Rc_analog_out_07           pwm07
#define Rc_analog_out_08           pwm08
#define Rc_analog_out_09           pwm09
#define Rc_analog_out_10           pwm10
#define Rc_analog_out_11           pwm11
#define Rc_analog_out_12           pwm12


/****************************** STRUCTURES ************************************/

/************************* FUNCTION PROTOTYPES ********************************/
extern void assign_outputs_slow(void);
extern void assign_outputs_fast(void);
extern UINT8 joystick_scaling(UINT8, UINT8, UINT8, UINT8);
extern void io_print_oi_inputs(void);
extern void io_print_rc_inputs(void);

#endif /* __ws_io_h_ */


