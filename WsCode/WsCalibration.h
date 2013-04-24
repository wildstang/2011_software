//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang 2009
//  @ File Name : WsCalibration.h
//  @ Date : 1/19/2009
//  @ Author : 
//
//


#if !defined(_WSCALIBRATION_H)
#define _WSCALIBRATION_H

#include <stdio.h>

#define CALIBRATION_FILENAME "/ws_calib"
#define PROTO_FILENAME "/ws_proto"
#define OLD_ROBOT_FILENAME "/ws_old"

/**
* This is a singleton that handles anything on the robot that requires calibration
*/
class WsCalibration
{
public:
    typedef enum
    {
        ARM_BOTTOM = 0,
        ARM_0_DEG,
        ARM_90_DEG,

        /* do not change the line below */
        MAX_NUM_VALUES,
    } CalibrationIndexT;

    virtual ~WsCalibration();
    static WsCalibration* getInstance();
    static void deleteInstance();
    void saveData();
    void readData();
    void printValues();
    bool isCompetitionRobot(void );
    bool isOldRobot(void );
    UINT32 getValue(CalibrationIndexT index);
    void setValue(CalibrationIndexT index, UINT32 value);

protected:
    WsCalibration();

    UINT32 a_data[MAX_NUM_VALUES]; /*!< An internal data array that holds the configuration values*/
    bool a_competitionRobot;       /*!< An internal flag that denotes whether the current robot is competition or proto*/
    bool a_oldRobot;               /*!< An internal flag that denotes whether the current robot is 2011 or 2010*/

private:
    static WsCalibration* ap_instance; /*!< The singleton instance */
};

#endif  //_WSCALIBRATION_H