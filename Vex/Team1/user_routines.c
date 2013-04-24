/*******************************************************************************
* FILE NAME: user_routines.c <VEX VERSION>
*
* DESCRIPTION:
*  This file contains the default mappings for CONFIGURATIONS A,B and C.  
*
* USAGE:
*  You can either modify this file to fit your needs, or remove it from your 
*  project and replace it with a modified copy. 
*
*******************************************************************************/

#include "ifi_aliases.h"
#include "ifi_default.h"
#include "ifi_utilities.h"
#include "user_routines.h"
#include "ws_includes.h"
#include "ws_io.h"
#include "ws_drive.h"
#include "ws_appendage.h"
#include "ws_general.h"

#define CODE_VERSION            2     /* Use this def. to keep track of your version # */

#define BUTTON_REV_THRESH       100
#define BUTTON_FWD_THRESH       154
#define NEUTRAL_VALUE           127


/*** DEFINE USER VARIABLES AND INITIALIZE THEM HERE ***/
/* EXAMPLES: (see MPLAB C18 User's Guide, p.9 for all types)
unsigned char wheel_revolutions = 0; (can vary from 0 to 255)
unsigned int  delay_count = 7;       (can vary from 0 to 65,535)
int           angle_deviation = 142; (can vary from -32,768 to 32,767)
unsigned long very_big_counter = 0;  (can vary from 0 to 4,294,967,295)
*/

/*******************************************************************************
* FUNCTION NAME: Setup_Who_Controls_Pwms
* PURPOSE:       Each parameter specifies what processor will control the pwm.  
*                 
* CALLED FROM:   User_Initialization
*     Argument             Type    IO   Description
*     --------             ----    --   -----------
*     pwmSpec1              int     I   USER/MASTER (defined in ifi_aliases.h)
*     pwmSpec2              int     I   USER/MASTER
*     pwmSpec3              int     I   USER/MASTER
*     pwmSpec4              int     I   USER/MASTER
*     pwmSpec5              int     I   USER/MASTER
*     pwmSpec6              int     I   USER/MASTER
*     pwmSpec7              int     I   USER/MASTER
*     pwmSpec8              int     I   USER/MASTER
* RETURNS:       void
*******************************************************************************/
static void Setup_Who_Controls_Pwms(int pwmSpec1,int pwmSpec2,int pwmSpec3,int pwmSpec4,
                                    int pwmSpec5,int pwmSpec6,int pwmSpec7,int pwmSpec8)
{
  txdata.pwm_mask = 0xFF;         /* Default to master controlling all PWMs. */
  if (pwmSpec1 == USER)           /* If User controls PWM1 then clear bit0. */
    txdata.pwm_mask &= 0xFE;      /* same as txdata.pwm_mask = txdata.pwm_mask & 0xFE; */
  if (pwmSpec2 == USER)           /* If User controls PWM2 then clear bit1. */
    txdata.pwm_mask &= 0xFD;
  if (pwmSpec3 == USER)           /* If User controls PWM3 then clear bit2. */
    txdata.pwm_mask &= 0xFB;
  if (pwmSpec4 == USER)           /* If User controls PWM4 then clear bit3. */
    txdata.pwm_mask &= 0xF7;
  if (pwmSpec5 == USER)           /* If User controls PWM5 then clear bit4. */
    txdata.pwm_mask &= 0xEF;
  if (pwmSpec6 == USER)           /* If User controls PWM6 then clear bit5. */
    txdata.pwm_mask &= 0xDF;
  if (pwmSpec7 == USER)           /* If User controls PWM7 then clear bit6. */
    txdata.pwm_mask &= 0xBF;
  if (pwmSpec8 == USER)           /* If User controls PWM8 then clear bit7. */
    txdata.pwm_mask &= 0x7F;
}


/*******************************************************************************
* FUNCTION NAME: User_Initialization
* PURPOSE:       This routine is called first (and only once) in the Main function.  
*                You may modify and add to this function.
*                The primary purpose is to set up the DIGITAL IN/OUT - ANALOG IN
*                pins as analog inputs, digital inputs, and digital outputs.
* CALLED FROM:   main.c
* ARGUMENTS:     none
* RETURNS:       void
*******************************************************************************/
void User_Initialization (void)
{
/* FIRST: Set up the pins you want to use as analog INPUTs. */
  IO1 = IO2 = INPUT;        /* Used for analog inputs. */
    /* 
     Note: IO1 = IO2 = IO3 = IO4 = INPUT 
           is the same as the following:

           IO1 = INPUT;
           IO2 = INPUT;
           IO3 = INPUT;
           IO4 = INPUT;
    */

/* SECOND: Configure the number of analog channels. */
  Set_Number_of_Analog_Channels(TWO_ANALOG);     /* See ifi_aliases.h */

/* THIRD: Set up any extra digital inputs. */
  /* The six INTERRUPTS are already digital inputs. */
  /* If you need more then set them up here. */
  /* IOxx = IOyy = INPUT; */
  IO3 = IO4 = IO5 = IO6 = IO7 = IO8 = INPUT;        
  IO9 = IO10 = IO11 = IO12 = IO13 = IO15 = INPUT;        

/* FOURTH: Set up the pins you want to use as digital OUTPUTs. */
  IO14 = IO16 = OUTPUT;      

/* FIFTH: Initialize the values on the digital outputs. */
  rc_dig_out14 = rc_dig_out16 = 0; 

/* SIXTH: Set your initial PWM values.  Neutral is 127. */
  pwm01 = pwm02 = pwm03 = pwm04 = pwm05 = pwm06 = pwm07 = pwm08 = 127;

/* SEVENTH: Choose which processor will control which PWM outputs. */
  Setup_Who_Controls_Pwms(MASTER,MASTER,MASTER,MASTER,MASTER,MASTER,MASTER,MASTER);

/* EIGHTH: Set your PWM output type.  Only applies if USER controls PWM 1, 2, 3, or 4. */
  /*   Choose from these parameters for PWM 1-4 respectively:                          */
  /*     IFI_PWM  - Standard IFI PWM output generated with Generate_Pwms(...)          */
  /*     USER_CCP - User can use PWM pin as digital I/O or CCP pin.                    */
  Setup_PWM_Output_Type(IFI_PWM,IFI_PWM,IFI_PWM,IFI_PWM);

  /* 
     Example: The following would generate a 40KHz PWM with a 50% duty cycle
              on the CCP2 pin (PWM OUT 1):

      Setup_Who_Controls_Pwms(USER,USER,MASTER,MASTER,MASTER,MASTER,MASTER,MASTER);
      CCP2CON = 0x3C;
      PR2 = 0xF9;
      CCPR2L = 0x7F;
      T2CON = 0;
      T2CONbits.TMR2ON = 1;
      Setup_PWM_Output_Type(USER_CCP,IFI_PWM,IFI_PWM,IFI_PWM);
  */

/* Add any other user initialization code here. */

  Initialize_Serial_Comms();     
 
  Putdata(&txdata);             /* DO NOT CHANGE! */
  User_Proc_Is_Ready();         /* DO NOT CHANGE! - last line of User_Initialization */

#ifdef _SIMULATOR
    statusflag.NEW_SPI_DATA = 1;
#else
  /* This code receives the 1st packet from master to obtain the version # */
  while (!statusflag.NEW_SPI_DATA);  /* Wait for 1st packet from master */
  Getdata(&rxdata);   
  printf("VEX - Master v%d, User v%d\r",(int)rxdata.master_version,(int)CODE_VERSION);        
#endif
}


/*******************************************************************************
* FUNCTION NAME: Process_Data_From_Master_uP
* PURPOSE:       Executes every 17ms when it gets new data from the master 
*                microprocessor.
* CALLED FROM:   main.c
* ARGUMENTS:     none
* RETURNS:       void
*******************************************************************************/
void Process_Data_From_Master_uP(void)
{
  Getdata(&rxdata);   /* Get fresh data from the master microprocessor. */

  /********** BEGIN WS CODE ******************/
  io_print_oi_inputs();

  processDrive(TRUE);
  processAppendage();

  assign_outputs_slow();

  /********** END WS CODE ******************/
  Putdata(&txdata);             /* DO NOT CHANGE! */
}


/*******************************************************************************
* FUNCTION NAME: Default_Routine
* PURPOSE:       Performs the default mappings of inputs to outputs for  
*                CONFIGURATIONS A, B, and C (B = drive mode 12 - settings on radio)
* CALLED FROM:   this file, Process_Data_From_Master_uP routine
* ARGUMENTS:     none
* RETURNS:       void
*******************************************************************************/
void Default_Routine(void)
{           
  pwm01 = PWM_in1;
  pwm02 = PWM_in2;
  pwm03 = 255 - PWM_in3;      // reverse direction of left side (CCW)  
  pwm04 = PWM_in4;

  pwm05 = 0x7F;               //Handle Channel 5 receiver button
  if (PWM_in5 < BUTTON_REV_THRESH)
  {
    pwm05 = 0xFF;
  }
  else if (PWM_in5 > BUTTON_FWD_THRESH)
  {
    pwm05 = 0;
  }
  pwm06 = 0x7F;               //Handle Channel 6 receiver button
  if (PWM_in6 < BUTTON_REV_THRESH)
    pwm06 = 0xFF;
  else if (PWM_in6 > BUTTON_FWD_THRESH)
    pwm06 = 0;

  if (rc_dig_in15 == CLOSED)  //When Jumper 15 is on CONFIGURATION C is selected
  {
    pwm07 = pwm02;            //CONFIGURATION C 
    pwm08 = pwm03;
  }
  else                        //CONFIGURATION A & B 
  {
    pwm07 = ~pwm05;
    pwm08 = ~pwm06;
  }

} /* END Default_Routine(); */


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
