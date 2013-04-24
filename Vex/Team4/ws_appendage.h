/*******************************************************************************
* FILE NAME: ws_appendage.h
*
* DESCRIPTION:
*  This is the include file which corresponds to ws_appendage.c
*
*  It contains some aliases and function prototypes used in those files.
*
* USAGE:
*  If you add your own routines to those files, this is a good place to add
*  your custom macros (aliases), type definitions, and function prototypes.
*******************************************************************************/

#ifndef __ws_appendage_h_
#define __ws_appendage_h_

/******************************* TYPEDEFS *************************************/

/******************************** MACROS **************************************/

/***************************** DEFINITIONS ************************************/
#define SHOULDER_DEADZONE            20
#define GRIPPER_DEADZONE                20
#define GRIPPER_SPEED_IN                63
#define GRIPPER_SPEED_OUT               -63
//#define GRIPPER_SENSITIVITY_NUM         1
//#define GRIPPER_SENSITIVITY_DEN         2

/****************************** STRUCTURES ************************************/

/************************* FUNCTION PROTOTYPES ********************************/
extern void  processAppendage(void);

#endif /* __ws_appendage_h_ */


