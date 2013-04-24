/*******************************************************************************
* FILE NAME: ws_drive.h
*
* DESCRIPTION:
*  This is the include file which corresponds to ws_drive.c
*
*  It contains some aliases and function prototypes used in those files.
*
* USAGE:
*  If you add your own routines to those files, this is a good place to add
*  your custom macros (aliases), type definitions, and function prototypes.
*******************************************************************************/

#ifndef __ws_drive_h_
#define __ws_drive_h_

/******************************* TYPEDEFS *************************************/

/******************************** MACROS **************************************/

/* no constants at this time*/

/***************************** DEFINITIONS ************************************/

#define DRIVE_DEADZONE            20

/****************************** STRUCTURES ************************************/

/************************* FUNCTION PROTOTYPES ********************************/
extern void  processDrive(UINT8 use_deadzone);

#endif /* __ws_drive_h_ */


