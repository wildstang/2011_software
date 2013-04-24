#if !defined(_WSROBOT2011_H)
#define _WSROBOT2011_H

#include "WPILib.h"
#include "InputManager.h"
class DriverStationLCD;
class WsAutonomousMgr;
class WsDriverStationLED;
class WsSmartLED;
#define TEST_ANALOG 0

#define SC_DRIVE_L1 1
#define SC_DRIVE_L2 2
#define SC_DRIVE_R1 3
#define SC_DRIVE_R2 4
#define SC_LIFT_1   5 // WINDOW
#define SC_LIFT_2   6 // BB
#define SC_ARM_1    7  // WINDOW
#define SC_ARM_2    8  // BB
#define SC_CLAW     9

#define RELAY_PUMP 1

#define ANA_IN_POT_ARM_POS   1
#define ANA_IN_GYRO          2
#define ANA_IN_GYRO_TEST     3

#define DIG_IN_PRESSURE      1
#define DIG_IN_ENC_DRIVE_L_A 2
#define DIG_IN_ENC_DRIVE_L_B 3
#define DIG_IN_ENC_DRIVE_R_A 4
#define DIG_IN_ENC_DRIVE_R_B 5
#define DIG_IN_ENC_LIFT_A    6
#define DIG_IN_ENC_LIFT_B    7
#define DIG_IN_LIFT_TOP      8
#define DIG_IN_LIFT_BOT      9
#define DIG_IN_TUBE_POS      10
#define DIG_OUT_LED0         11
#define DIG_OUT_LED1         12
#define DIG_OUT_LED2         13
#define DIG_OUT_LED3         14




#define SOL_DRIVE_SHIFT              1
#define SOL_TUBE_RELEASE             2
#define DSOL_MINIBOT_DEPLOY_FWD      3
#define DSOL_MINIBOT_DEPLOY_REV      4


class WsCalibration;
class WsLarm;
class WsLift;
class WsArm;
class WsMinibot;
class WsRollerClaw;
class WsDriveVector;
class WsControlMethod6WD;
class WsControlMethodLarm;
class WsControlMethodMinibot;
class WsDriveBase6WD;
class WsDashboard;
class WsShmCamera;

class WsRobot2011 : public IterativeRobot
{
    public:
        WsRobot2011(void);

        /********** Init Routines **********/
        void RobotInit(void);
        void DisabledInit(void);
        void AutonomousInit(void);
        void TeleopInit(void);

        /********** Periodic Routines **********/
        void DisabledPeriodic(void);
        void AutonomousPeriodic(void);
        void TeleopPeriodic(void);

        /********** Continuous Routines **********/
        void DisabledContinuous(void);
        void AutonomousContinuous(void);
        void TeleopContinuous(void);

    protected:
        void ProcessIO(void);
        void ProcessDashboard(void);
        bool ProcessCalibration(void);

        /********** Inputs **********/
        InputManager* ap_inputManager;

        /********** Input Control Methods **********/
        WsControlMethod6WD *ap_controlMethodDrive;
        WsControlMethodLarm *ap_controlMethodLarm;
        WsControlMethodMinibot *ap_controlMethodMinibot;

        /********** Robot Side Sensor Inputs **********/
        
        WsShmCamera* ap_camera;
        
        /********** Outputs **********/
        /********** Output Objects **********/
        WsLift *ap_lift;
        WsArm *ap_arm;
        WsRollerClaw *ap_rollerClaw;
        WsLarm *ap_larm;
        WsDriveBase6WD *ap_driveBase;
        WsMinibot *ap_minibot;

        Compressor *ap_compressor;

        /********** Internal Variables **********/
        WsCalibration *ap_calib;
        WsDriveVector *ap_driveVector;

        WsAutonomousMgr* ap_autonMgr;
#if TEST_ANALOG
        AnalogChannel *ap_testAnalog;
#endif

        // Local variables to count the number of periodic loops performed
        UINT32 a_autoPeriodicLoops;
        UINT32 a_disabledPeriodicLoops;
        UINT32 a_telePeriodicLoops;

        DigitalInput* testDiginA;
        DigitalInput* testDiginB;

    private:
        ~WsRobot2011(void);

        void updateSmartLed();

        void dashboardDisplayInputs(void);
        void dashboardDisplayOutput(void);
        void dashboardDisplaySensors(void);
        void dashboardDisplayDriveStraight(void);
        void dashboardDisplayLarm(void);
        void dashboardDisplayAutonomous(void);
        void dashboardDisplayMinibot(void);
        void dashboardDisplayMisc(void);
        void printLcdRegularData(void);

        DriverStationLCD *ap_dsLcd;
        WsDriverStationLED *ap_dsLockInLed;
        WsDashboard *ap_dashboard;
        WsSmartLED *ap_smartLed;
        bool a_calibrationMode;
};

START_ROBOT_CLASS(WsRobot2011);

#endif  //_WSROBOT2011_H

