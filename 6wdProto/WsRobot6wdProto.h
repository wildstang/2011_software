#if !defined(_WSROBOT6WDPROTO_H)
#define _WSROBOT6WDPROTO_H

#include "WPILib.h"
#include "Gamepad.h"
#include "WsButton.h"

class WsLimitSwitch;
class WsLineTrackerSensor;
class WsUltrasonic;

#define USE_ROBOT_DRIVE 0


class WsRobot6wdProto : public IterativeRobot
{
    public:
        WsRobot6wdProto(void);

        /********************************** Init Routines *************************************/

        void RobotInit(void);
        void DisabledInit(void);
        void AutonomousInit(void);
        void TeleopInit(void);

        /********************************** Periodic Routines *************************************/

        void DisabledPeriodic(void);
        void AutonomousPeriodic(void);
        void TeleopPeriodic(void);

        /********************************** Continuous Routines *************************************/

        void DisabledContinuous(void);
        void AutonomousContinuous(void);
        void TeleopContinuous(void);

    protected:
        /********************************** Inputs *************************************/

        Joystick   *ap_rightStick;
        Joystick   *ap_leftStick;
        
        Gamepad    *ap_driveGamepad;
        
        WsButton   *ap_antiTurboButton;
        WsButton   *ap_stickyButton;
        WsButton   *ap_multiStickyButton;
        WsButton   *ap_tapButton;
        WsButton   *ap_fwdCycleTapButton;
        WsButton   *ap_revCycleTapButton;
        
        /************************** Robot Side Sensor Inputs ***************************/
        WsLimitSwitch *ap_limitSwitch;
        WsLineTrackerSensor *ap_lineTracker;
        WsUltrasonic *ap_ultrasonic;
        
        

        /********************************** Outputs *************************************/

#if USE_ROBOT_DRIVE
        RobotDrive *ap_robotDrive;
#endif
        
        SpeedController *ap_scDriveFL;
        SpeedController *ap_scDriveFR;
        SpeedController *ap_scDriveBL;
        SpeedController *ap_scDriveBR;


        /********************************** Internal Variables *************************************/
        // Local variables to count the number of periodic loops performed
        UINT32 a_autoPeriodicLoops;
        UINT32 a_disabledPeriodicLoops;
        UINT32 a_telePeriodicLoops;
        
        Timer* ap_stateMachine4Timer;
        Timer* ap_hwStateMachineTimer;

    private:
        ~WsRobot6wdProto(void);
        void testStateMachine1(void);
        void testStateMachine2(void);
        void testStateMachine3(void);
        void testStateMachine4(void);
        
        void hwStateMachine1(void);
        void hwStateMachine2(void);
        void hwStateMachine3(void);
        void hwStateMachine4(void);
        void hwStateMachine5(void);
        
        typedef enum
        {
            STATE_MACHINE1_STATE_OFF,
            STATE_MACHINE1_STATE_ON
        } StateMachine1StateT;
        
        typedef enum
        {
            STATE_MACHINE2_STATE_OFF,
            STATE_MACHINE2_STATE_HALF_FWD,
            STATE_MACHINE2_STATE_ON
        } StateMachine2StateT;
        
        typedef enum
        {
            STATE_MACHINE3_STATE_OFF,
            STATE_MACHINE3_STATE_HALF_FWD,
            STATE_MACHINE3_STATE_ON
        } StateMachine3StateT;
        
        typedef enum
        {
            STATE_MACHINE4_STATE_INIT,
            STATE_MACHINE4_STATE_1,
            STATE_MACHINE4_STATE_2,
            STATE_MACHINE4_STATE_3,
            STATE_MACHINE4_STATE_4,
            STATE_MACHINE4_STATE_5,
            STATE_MACHINE4_STATE_6,
            STATE_MACHINE4_STATE_7,
            STATE_MACHINE4_STATE_8,
        } StateMachine4StateT;
                 
                 
        StateMachine1StateT a_stateMachine1State;
        StateMachine2StateT a_stateMachine2State;
        StateMachine3StateT a_stateMachine3State;
        StateMachine4StateT a_stateMachine4State;
        
        typedef enum
        {
            STATE_MACHINE4_DIR_FWD,
            STATE_MACHINE4_DIR_REV,
        } StateMachine4DirectionT;
        
        StateMachine4DirectionT a_stateMachine4Direction;
        
        typedef enum
        {
            HW_STATE_MACHINE1_STATE_DRIVE,
            HW_STATE_MACHINE1_STATE_TURN,
        } HwStateMachine1StateT;
        typedef enum
        {
            HW_STATE_MACHINE2_STATE_WAIT,
            HW_STATE_MACHINE2_STATE_SET_DRIVE_CW,
            HW_STATE_MACHINE2_STATE_SET_DRIVE_CCW,
            HW_STATE_MACHINE2_STATE_DRIVE,
            HW_STATE_MACHINE2_STATE_TURN,
        } HwStateMachine2StateT;
        
        typedef enum
        {
            HW_STATE_MACHINE3_STATE_WAIT,
            HW_STATE_MACHINE3_STATE_SET_DRIVE_CW,
            HW_STATE_MACHINE3_STATE_SET_DRIVE_CCW,
            HW_STATE_MACHINE3_STATE_DRIVE,
            HW_STATE_MACHINE3_STATE_TURN,
        } HwStateMachine3StateT;
        
        typedef enum
        {
            HW_STATE_MACHINE4_STATE_WAIT_FOR_START,
            HW_STATE_MACHINE4_STATE_DRIVE,
            HW_STATE_MACHINE4_STATE_WAIT_FOR_BUTTON,
        } HwStateMachine4StateT;
        
        typedef enum
        {
            HW_STATE_MACHINE5_STATE_WAIT_FOR_START,
            HW_STATE_MACHINE5_STATE_DRIVE,
            HW_STATE_MACHINE5_STATE_WAIT_FOR_BUTTON,
            HW_STATE_MACHINE5_STATE_DONE,
        } HwStateMachine5StateT;
        
        HwStateMachine1StateT a_hwStateMachine1State;
        HwStateMachine2StateT a_hwStateMachine2State;
        HwStateMachine3StateT a_hwStateMachine3State;
        HwStateMachine4StateT a_hwStateMachine4State;
        HwStateMachine5StateT a_hwStateMachine5State;
        int a_hwStateMachineDirection;
        int a_hwStateMachineTurns;
        
};

START_ROBOT_CLASS(WsRobot6wdProto);

#endif  //_WSROBOT6WDPROTO_H

