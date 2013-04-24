/*******************************************************************************
* FILE NAME: ws_includes.h
*
* DESCRIPTION:
*  General structures & enumerations
*
*******************************************************************************/

#ifndef __ws_includes_h_
#define __ws_includes_h_
#include "printf_lib.h"


/******************************* TYPEDEFS *************************************/
typedef unsigned char       UINT8;
typedef char                INT8;
typedef signed short long   SINT24;
typedef unsigned short long UINT24;
typedef unsigned int        UINT16;
typedef int                 INT16;
typedef long int            INT32;
typedef unsigned long int   UINT32;

/******************************** MACROS **************************************/
#define MIN_MAX(variable,min_val,max_val)  MIN((variable),(min_val)); MAX((variable),(max_val))

#define MAX(variable, max_val)  if (variable > (max_val)) variable = (max_val)
#define MIN(variable, min_val)  if (variable < (min_val)) variable = (min_val)

#define MAX_RETURN(value, max_val) ((value) > (max_val) ? (max_val) : (value))
#define MIN_RETURN(value, min_val) ((value) < (min_val) ? (min_val) : (value))

#define DEADZONE(var, zone)  if ((var > (127 - (zone))) && \
                                 (var < (127 + (zone)))) \
                               var = 127

/***************************** DEFINITIONS ************************************/

#define SUCCESS 1
#define FAIL    0

#define ROBOT_ENABLED  0
#define ROBOT_DISABLED 1

#define AUTO_ENABLED   1
#define AUTO_DISABLED  0

#define NUM_PACKETS_PER_SEC 40


/****************************** STRUCTURES ************************************/
typedef struct motor_vals_
{
  INT8                left_drive;
  INT8                right_drive;
  INT8                shoulder;
  INT8                claw;

/************** ADD NEW FUNCTIONALITY ABOVE HERE *********/
} MotorValsType;

extern MotorValsType motor_vals;


/************************* FUNCTION PROTOTYPES ********************************/

#endif /* __ws_includes_h_ */


