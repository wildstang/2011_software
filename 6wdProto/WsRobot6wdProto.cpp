#include <stdio.h>
#include "WsRobot6wdProto.h"
#include "WsJoystick.h"
#include "WsButton.h"
#include "WsStickyButton.h"
#include "WsMultiStickyButton.h"
#include "WsTapButton.h"
#include "WsLimitSwitch.h"
#include "WsLineTrackerSensor.h"
#include "WsUltrasonic.h"

#define TEST_STATE_MACHINES 0
#define TEST_SENSORS 1

WsRobot6wdProto::WsRobot6wdProto(void)
{
    printf("WsRobot6wdProto Constructor Started\n");
    /************************* Start of object construction ************************/
    
    /********************************** Inputs *************************************/
    
    ap_rightStick = new WsJoystick(1);
    ap_leftStick = new WsJoystick(2);
    
    ap_driveGamepad = new Gamepad(3);
    
    ap_antiTurboButton = new WsButton(ap_driveGamepad, Gamepad::kLeftTrigger);
    ap_stickyButton = new WsStickyButton(ap_driveGamepad, Gamepad::kXButton);
    ap_multiStickyButton = new WsMultiStickyButton(ap_driveGamepad, 
            Gamepad::kXButton,
            Gamepad::kCircleButton);
    ap_tapButton = new WsTapButton(ap_driveGamepad,  Gamepad::kXButton);
    
    ap_fwdCycleTapButton = new WsTapButton(ap_driveGamepad,  Gamepad::kRightBumper);
    ap_revCycleTapButton = new WsTapButton(ap_driveGamepad,  Gamepad::kLeftBumper);
    /********************************** Outputs *************************************/
    
    ap_scDriveFL = new Jaguar(3);
    ap_scDriveBL = new Jaguar(4);
    ap_scDriveFR = new Jaguar(1);
    ap_scDriveBR = new Jaguar(2);
    
#if USE_ROBOT_DRIVE
    ap_robotDrive = new RobotDrive( ap_scDriveFL,
            ap_scDriveBL,
            ap_scDriveFR,
            ap_scDriveBR);
    ap_robotDrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
    ap_robotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
    
#endif
    ap_stateMachine4Timer = new Timer();
    ap_hwStateMachineTimer = new Timer();
    
    ap_limitSwitch = new WsLimitSwitch(1);
    ap_lineTracker = new WsLineTrackerSensor(2);
    //ap_lineTracker->SetThresholds(550, 650);
    ap_lineTracker->SetThresholds(600);
    
    ap_ultrasonic = new WsUltrasonic(2, 3);
    
    /**************************** End of object construction*************************/
    // Initialize counters to record the number of loops completed in autonomous and teleop modes
    a_autoPeriodicLoops = 0;
    a_disabledPeriodicLoops = 0;
    a_telePeriodicLoops = 0;
    
    a_stateMachine1State = STATE_MACHINE1_STATE_OFF;
    a_stateMachine2State = STATE_MACHINE2_STATE_OFF;
    a_stateMachine3State = STATE_MACHINE3_STATE_OFF;
    a_stateMachine4State = STATE_MACHINE4_STATE_INIT;
    
    a_stateMachine4Direction = STATE_MACHINE4_DIR_FWD;
    
    a_hwStateMachine1State = HW_STATE_MACHINE1_STATE_DRIVE;
    a_hwStateMachine2State = HW_STATE_MACHINE2_STATE_WAIT;
    a_hwStateMachine3State = HW_STATE_MACHINE3_STATE_WAIT;
    a_hwStateMachine4State = HW_STATE_MACHINE4_STATE_WAIT_FOR_START;
    a_hwStateMachine5State = HW_STATE_MACHINE5_STATE_WAIT_FOR_START;
    a_hwStateMachineDirection = 1;
    a_hwStateMachineTurns = 0;
    
    printf("WsRobot6wdProto Constructor Completed\n");
}

WsRobot6wdProto::~WsRobot6wdProto(void)
{
    /********************************** Inputs *************************************/
    
    delete ap_rightStick;
    ap_rightStick = NULL;
    
    delete ap_leftStick;
    ap_leftStick = NULL;
    
    delete ap_driveGamepad;
    ap_driveGamepad = NULL;
    
    delete ap_antiTurboButton;
    ap_antiTurboButton = NULL;
    
    delete ap_stickyButton;
    ap_stickyButton = NULL;
    
    delete ap_multiStickyButton;
    ap_multiStickyButton = NULL;
    
    delete ap_tapButton;
    ap_tapButton = NULL;
    
    delete ap_fwdCycleTapButton;
    ap_fwdCycleTapButton = NULL;
    
    delete ap_revCycleTapButton;
    ap_revCycleTapButton = NULL;
    
    delete ap_limitSwitch;
    ap_limitSwitch = NULL;
    
    delete ap_lineTracker;
    ap_lineTracker = NULL;
    
    delete ap_ultrasonic;
    ap_ultrasonic = NULL;
    
    /********************************** Outputs *************************************/
    delete ap_scDriveFL;
    ap_scDriveFL = NULL;
    
    delete ap_scDriveBL;
    ap_scDriveBL = NULL;
    
    delete ap_scDriveFR;
    ap_scDriveFR = NULL;
    
    delete ap_scDriveBR;
    ap_scDriveBR = NULL;
    
#if USE_ROBOT_DRIVE
    delete ap_robotDrive;
    ap_robotDrive = NULL;
#endif
    
    delete ap_stateMachine4Timer;
    ap_stateMachine4Timer = NULL;
    
    delete ap_hwStateMachineTimer;
    ap_hwStateMachineTimer = NULL;
    
    
}

/********************************** Init Routines *************************************/

void WsRobot6wdProto::RobotInit(void)
{
    printf("RobotInit() completed.\n");
}

void WsRobot6wdProto::DisabledInit(void)
{
    a_disabledPeriodicLoops = 0;
    ap_scDriveFL->Set(0);
    ap_scDriveBL->Set(0);
    ap_scDriveFR->Set(0);
    ap_scDriveBR->Set(0);
    //printf("DisabledInit() completed.\n");
    ap_stateMachine4Timer->Stop();
    ap_hwStateMachineTimer->Stop();
}

void WsRobot6wdProto::AutonomousInit(void)
{
    a_autoPeriodicLoops = 0;
    //printf("AutonomousInit() completed.\n");
}

void WsRobot6wdProto::TeleopInit(void)
{
    a_telePeriodicLoops = 0;
    a_stateMachine1State = STATE_MACHINE1_STATE_OFF;
    a_stateMachine2State = STATE_MACHINE2_STATE_OFF;
    a_stateMachine3State = STATE_MACHINE3_STATE_OFF;
    a_stateMachine4State = STATE_MACHINE4_STATE_INIT;
    ap_stateMachine4Timer->Start();
    ap_stateMachine4Timer->Reset();
    ap_hwStateMachineTimer->Start();
    ap_hwStateMachineTimer->Reset();
    a_hwStateMachine1State = HW_STATE_MACHINE1_STATE_DRIVE;
    a_hwStateMachine2State = HW_STATE_MACHINE2_STATE_WAIT;
    a_hwStateMachine3State = HW_STATE_MACHINE3_STATE_WAIT;
    a_hwStateMachine4State = HW_STATE_MACHINE4_STATE_WAIT_FOR_START;
    a_hwStateMachine5State = HW_STATE_MACHINE5_STATE_WAIT_FOR_START;
    
    //printf("TeleopPeriodicInit() completed.\n");
}

/********************************** Periodic Routines *************************************/

void WsRobot6wdProto::DisabledPeriodic(void)
{
    GetWatchdog().Feed();
    //printf("DisabledPeriodic() %d\n", a_disabledPeriodicLoops);
    
    /*
    printf("LX: %2.2f LY: %2.2f  RX: %2.2f  RY: %2.2f\n",
            ap_driveGamepad->GetX(Gamepad::kLeftHand),
            ap_driveGamepad->GetY(Gamepad::kLeftHand),
            ap_driveGamepad->GetX(Gamepad::kRightHand),
            ap_driveGamepad->GetY(Gamepad::kRightHand));
     */
    
    /*
    printf("LTr: %d LT: %d LB: %d RTr: %d RT: %d RB: %d TB: %d CB: %d SB: %d XB: %d\n",
            ap_driveGamepad->GetTrigger(Gamepad::kLeftHand),
            ap_driveGamepad->GetTop(Gamepad::kLeftHand),
            ap_driveGamepad->GetBumper(Gamepad::kLeftHand),
            ap_driveGamepad->GetTrigger(Gamepad::kRightHand),
            ap_driveGamepad->GetTop(Gamepad::kRightHand),
            ap_driveGamepad->GetBumper(Gamepad::kRightHand),
            ap_driveGamepad->GetTriangleButton(),
            ap_driveGamepad->GetCircleButton(),
            ap_driveGamepad->GetSquareButton(),
            ap_driveGamepad->GetXButton());
     */
    /*
    printf("DPAD: %d\n", ap_driveGamepad->GetDPad());
     */
    
    /*
    printf("Select: %d  Start: %d\n", ap_driveGamepad->GetSelectButton(), ap_driveGamepad->GetStartButton());
    printf("Select: %d  Start: %d\n", ap_driveGamepad->GetButton(Gamepad::kSelectButton), ap_driveGamepad->GetButton(Gamepad::kStartButton));
     */
    
    /*
    int buttonNum;
    for(buttonNum = 1; buttonNum < Gamepad::kNumButtons + 1; buttonNum++)
    {
        printf("%d - %d  ", buttonNum, ap_driveGamepad->GetRawButton(buttonNum));
    }
    printf("\n");
     */
    
    
    /*
    printf("%d\n", ap_antiTurboButton->GetState());
     */
    
    /*
    printf("STICKY: %d  MULTI: %d   TAP: %d\n",
            ap_stickyButton->GetState(),
            ap_multiStickyButton->GetState(),
            ap_tapButton->GetState());
     */
    
    /*
    printf("LIMIT: %d\n",  ap_limitSwitch->Get());
    */
    
    /*
    printf("LINE: %d Dark: %d  Light: %d\n",  ap_lineTracker->Get(),
                                              ap_lineTracker->SeesDark(),
                                              ap_lineTracker->SeesLight());
                                              */
                                            
    /*
    printf("USONIC: %f %d %d\n", ap_ultrasonic->Get(), ap_ultrasonic->IsInRange(10), ap_ultrasonic->IsInRange(8, 12));
    */
    a_disabledPeriodicLoops++;
}

void WsRobot6wdProto::AutonomousPeriodic(void)
{
    GetWatchdog().Feed();
    
    //printf("AutonomousPeriodic() %d\n", a_autoPeriodicLoops);
    a_autoPeriodicLoops++;
}

void WsRobot6wdProto::TeleopPeriodic(void)
{
    float leftSpeed = 0;
    float rightSpeed = 0;
    
    GetWatchdog().Feed();
    
    //printf("TeleopPeriodic() %d\n", a_telePeriodicLoops);
    a_telePeriodicLoops++;
    
    
    /* This is the original code to read the get the Y axis from the joystick objects
       The WsJoystick object takes care of inverting the axis for us so full forward is 1
     */
    /*
       leftSpeed = ap_leftStick->GetY();
       rightSpeed = ap_rightStick->GetY();
     */
    
    /* Get the Y axis from the left and right sticks on the gamepad */
    leftSpeed = ap_driveGamepad->GetY(Gamepad::kLeftHand);
    rightSpeed = ap_driveGamepad->GetY(Gamepad::kRightHand);
    
    // Invert because gamepad has -1 full forward when we want +1
    leftSpeed *= -1;
    rightSpeed *= -1;
    
    //printf("L: %5.2f  R: %5.2f\n", leftSpeed, rightSpeed);
    
    /* When the left trigger (antiTurbo button) is pressed,
       scale the speeds by .5 (half speed)
       When the right trigger is pressed, invert the speeds
       With this implementation, the left trigger overrides the right trigger
     */
    
    /****
      Rather than do what we did originally like this
      if(ap_leftStick->GetTrigger())
      We'll make the logic use the button class so it doesn't
      care which physical button is actually being pressed
     ****/
    
#if TEST_STATE_MACHINES
    //testStateMachine1();
    //testStateMachine2();
    //testStateMachine3();
    //testStateMachine4();
    
    //hwStateMachine1();
    //hwStateMachine2();
    //hwStateMachine3();
    //hwStateMachine4();
    hwStateMachine5();
#elif TEST_SENSORS
    
    
    /********
     * LIMIT SWITCH TEST:
     * - TANK DRIVE CONTROL
     * - STOP DRIVING FORWARD WHEN LIMIT IS PRESSED,
     *   BUT STILL ALLOW REVERSE
    
    if(ap_limitSwitch != NULL)
    {
        if(ap_limitSwitch->Get() == true)
        {
            if(leftSpeed > 0 && rightSpeed > 0)
            {
                leftSpeed = 0;
                rightSpeed = 0;
            }
        }
    }
     ********/
    
    /********
     * LINE SENSOR TEST:
     * - TANK DRIVE CONTROL
     * - STOP DRIVING FORWARD WHEN ON LINE
     *   BUT STILL ALLOW REVERSE
     *
    if(ap_lineTracker != NULL)
    {
        printf("LINE: %d Dark: %d  Light: %d\n",  ap_lineTracker->Get(),
                ap_lineTracker->SeesDark(),
                ap_lineTracker->SeesLight());
        if(leftSpeed > 0 && rightSpeed > 0)
        {
            if(ap_lineTracker->SeesDark() == true)
            {
                leftSpeed *= .5;
            }
            else
            {
                rightSpeed *= .5;
            }
        }
    }
    */
    
    /**
     * ULTRASONIC
     * - DRIVE HALF SPEED AND TRY TO BE 15inches away
     */
    
    printf("USONIC: %f\n", ap_ultrasonic->Get());
    if(ap_ultrasonic->IsInRange(10))
    {
        leftSpeed = -.25;
        rightSpeed = -.25;
        
    }
    else if(ap_ultrasonic->IsInRange(8, 12))
    {
        leftSpeed = 0;
        rightSpeed = 0;
    }
    else
    {
        leftSpeed = .5;
        rightSpeed = .5;
    }
        
        
    
    ap_scDriveFL->Set(leftSpeed);
    ap_scDriveBL->Set(leftSpeed);
    ap_scDriveFR->Set(rightSpeed);
    ap_scDriveBR->Set(rightSpeed);
    
    
    
    
#else
    if(ap_antiTurboButton->GetState())
    {
        leftSpeed *= .5;
        rightSpeed *= .5;
    }
    else if(ap_rightStick->GetTrigger())
    {
        leftSpeed *= -1;
        rightSpeed *= -1;
    }
    
    
    
#if USE_ROBOT_DRIVE
    /*** These are left here for reference ***/
    /* Drive forward at a speed of .25 */
    //ap_robotDrive->Drive(.25, 0);
    /* Drive tank style using the left an right joysticks */
    //ap_robotDrive->TankDrive(ap_leftStick, ap_rightStick);
    ap_robotDrive->TankDrive(ap_driveGamepad, 2, ap_driveGamepad, 4);
    /* Drive arcade style using the  right joysticks */
    //ap_robotDrive->ArcadeDrive(ap_rightStick);
    //ap_robotDrive->ArcadeDrive(ap_driveGamepad);
    /*****************************************/
    //ap_robotDrive->SetLeftRightMotorSpeeds(leftSpeed, rightSpeed);
#else
    /* Set the left and right motor speeds based on the speeds calculated above */
    ap_scDriveFL->Set(leftSpeed);
    ap_scDriveBL->Set(leftSpeed);
    ap_scDriveFR->Set(rightSpeed);
    ap_scDriveBR->Set(rightSpeed);
#endif
#endif
}

/********************************** Continuous Routines *************************************/

void WsRobot6wdProto::DisabledContinuous(void)
{
    // This function is unused, but is included because the default WPILib
    // function has a print in it that makes debugging difficult
}

void WsRobot6wdProto::AutonomousContinuous(void)
{
    // This function is unused, but is included because the default WPILib
    // function has a print in it that makes debugging difficult
}

void WsRobot6wdProto::TeleopContinuous(void)
{
    // This function is unused, but is included because the default WPILib
    // function has a print in it that makes debugging difficult
}

void WsRobot6wdProto::testStateMachine1(void)
{
    StateMachine1StateT nextState = a_stateMachine1State;
    
    switch(a_stateMachine1State)
    {
    case STATE_MACHINE1_STATE_OFF:
        ap_scDriveFL->Set(0);
        ap_scDriveBL->Set(0);
        ap_scDriveFR->Set(0);
        ap_scDriveBR->Set(0);
        
        if(ap_tapButton->GetState() == true)
        {
            nextState = STATE_MACHINE1_STATE_ON;
        }
        break;
    case STATE_MACHINE1_STATE_ON:
        ap_scDriveFL->Set(1);
        ap_scDriveBL->Set(1);
        ap_scDriveFR->Set(1);
        ap_scDriveBR->Set(1);
        
        if(ap_tapButton->GetState() == true)
        {
            nextState = STATE_MACHINE1_STATE_OFF;
        }
        
        break;
    default:
        ap_scDriveFL->Set(0);
        ap_scDriveBL->Set(0);
        ap_scDriveFR->Set(0);
        ap_scDriveBR->Set(0);
        
        nextState = STATE_MACHINE1_STATE_OFF;
        
        break;
    }
    
    a_stateMachine1State = nextState;
}

void WsRobot6wdProto::testStateMachine2(void)
{
    StateMachine2StateT nextState = a_stateMachine2State;
    
    switch(a_stateMachine2State)
    {
    case STATE_MACHINE2_STATE_OFF:
        ap_scDriveFL->Set(0);
        ap_scDriveBL->Set(0);
        ap_scDriveFR->Set(0);
        ap_scDriveBR->Set(0);
        
        if(ap_tapButton->GetState() == true)
        {
            nextState = STATE_MACHINE2_STATE_HALF_FWD;
        }
        break;
    case STATE_MACHINE2_STATE_HALF_FWD:
        ap_scDriveFL->Set(.5);
        ap_scDriveBL->Set(.5);
        ap_scDriveFR->Set(.5);
        ap_scDriveBR->Set(.5);
        
        if(ap_tapButton->GetState() == true)
        {
            nextState = STATE_MACHINE2_STATE_ON;
        }
        break;
    case STATE_MACHINE2_STATE_ON:
        ap_scDriveFL->Set(1);
        ap_scDriveBL->Set(1);
        ap_scDriveFR->Set(1);
        ap_scDriveBR->Set(1);
        
        if(ap_tapButton->GetState() == true)
        {
            nextState = STATE_MACHINE2_STATE_OFF;
        }
        
        break;
    default:
        ap_scDriveFL->Set(0);
        ap_scDriveBL->Set(0);
        ap_scDriveFR->Set(0);
        ap_scDriveBR->Set(0);
        
        nextState = STATE_MACHINE2_STATE_OFF;
        
        break;
    }
    
    a_stateMachine2State = nextState;
}


void WsRobot6wdProto::testStateMachine3(void)
{
    StateMachine3StateT nextState = a_stateMachine3State;
    
    switch(a_stateMachine3State)
    {
    case STATE_MACHINE3_STATE_OFF:
        ap_scDriveFL->Set(0);
        ap_scDriveBL->Set(0);
        ap_scDriveFR->Set(0);
        ap_scDriveBR->Set(0);
        
        if(ap_fwdCycleTapButton->GetState() == true)
        {
            nextState = STATE_MACHINE3_STATE_HALF_FWD;
        }
        else if(ap_revCycleTapButton->GetState() == true)
        {
            nextState = STATE_MACHINE3_STATE_ON;
        }
        break;
    case STATE_MACHINE3_STATE_HALF_FWD:
        ap_scDriveFL->Set(.5);
        ap_scDriveBL->Set(.5);
        ap_scDriveFR->Set(.5);
        ap_scDriveBR->Set(.5);
        
        if(ap_fwdCycleTapButton->GetState() == true)
        {
            nextState = STATE_MACHINE3_STATE_ON;
        }
        else if(ap_revCycleTapButton->GetState() == true)
        {
            nextState = STATE_MACHINE3_STATE_OFF;
        }
        break;
    case STATE_MACHINE3_STATE_ON:
        ap_scDriveFL->Set(1);
        ap_scDriveBL->Set(1);
        ap_scDriveFR->Set(1);
        ap_scDriveBR->Set(1);
        
        if(ap_fwdCycleTapButton->GetState() == true)
        {
            nextState = STATE_MACHINE3_STATE_OFF;
        }
        else if(ap_revCycleTapButton->GetState() == true)
        {
            nextState = STATE_MACHINE3_STATE_HALF_FWD;
        }
        
        break;
    default:
        ap_scDriveFL->Set(0);
        ap_scDriveBL->Set(0);
        ap_scDriveFR->Set(0);
        ap_scDriveBR->Set(0);
        
        nextState = STATE_MACHINE3_STATE_OFF;
        
        break;
    }
    
    a_stateMachine3State = nextState;
}

void WsRobot6wdProto::testStateMachine4(void)
{
    StateMachine4StateT nextState = a_stateMachine4State;
    
    
    if(ap_revCycleTapButton->GetState() == true)
    {
        if(a_stateMachine4Direction == STATE_MACHINE4_DIR_FWD)
        {
            a_stateMachine4Direction = STATE_MACHINE4_DIR_REV;
        }
        else
        {
            a_stateMachine4Direction = STATE_MACHINE4_DIR_FWD;
        }
    }
    
    switch(a_stateMachine4State)
    {
    case STATE_MACHINE4_STATE_INIT:
        ap_scDriveFL->Set(0);
        ap_scDriveBL->Set(0);
        ap_scDriveFR->Set(0);
        ap_scDriveBR->Set(0);
        
        if(ap_fwdCycleTapButton->GetState() == true)
        {
            ap_stateMachine4Timer->Reset();
            nextState = STATE_MACHINE4_STATE_1;
        }
        break;
    case STATE_MACHINE4_STATE_1:
        ap_scDriveFL->Set(0);
        ap_scDriveBL->Set(0);
        ap_scDriveFR->Set(0);
        ap_scDriveBR->Set(0);
        
        if(ap_fwdCycleTapButton->GetState() == true)
        {
            nextState = STATE_MACHINE4_STATE_INIT;
        }
        else if(ap_stateMachine4Timer->HasPeriodPassed(1.0))
        {
            ap_stateMachine4Timer->Reset();
            if(a_stateMachine4Direction == STATE_MACHINE4_DIR_FWD)
            {
                nextState = STATE_MACHINE4_STATE_2;
            }
            else
            {
                nextState = STATE_MACHINE4_STATE_8;
            }
        }
        break;
    case STATE_MACHINE4_STATE_2:
        ap_scDriveFL->Set(1);
        ap_scDriveBL->Set(1);
        ap_scDriveFR->Set(1);
        ap_scDriveBR->Set(1);
        
        //if(ap_fwdCycleTapButton->GetState() == true)
        if(ap_fwdCycleTapButton->GetState() == true)
        {
            nextState = STATE_MACHINE4_STATE_INIT;
        }
        else if(ap_stateMachine4Timer->HasPeriodPassed(1.0))
        {
            ap_stateMachine4Timer->Reset();
            if(a_stateMachine4Direction == STATE_MACHINE4_DIR_FWD)
            {
                nextState = STATE_MACHINE4_STATE_3;
            }
            else
            {
                nextState = STATE_MACHINE4_STATE_1;
            }
        }
        break;
    case STATE_MACHINE4_STATE_3:
        ap_scDriveFL->Set(1);
        ap_scDriveBL->Set(1);
        ap_scDriveFR->Set(0);
        ap_scDriveBR->Set(0);
        
        //if(ap_fwdCycleTapButton->GetState() == true)
        if(ap_fwdCycleTapButton->GetState() == true)
        {
            nextState = STATE_MACHINE4_STATE_INIT;
        }
        else if(ap_stateMachine4Timer->HasPeriodPassed(1.0))
        {
            ap_stateMachine4Timer->Reset();
            if(a_stateMachine4Direction == STATE_MACHINE4_DIR_FWD)
            {
                nextState = STATE_MACHINE4_STATE_4;
            }
            else
            {
                nextState = STATE_MACHINE4_STATE_2;
            }
        }
        break;
    case STATE_MACHINE4_STATE_4:
        ap_scDriveFL->Set(1);
        ap_scDriveBL->Set(1);
        ap_scDriveFR->Set(-1);
        ap_scDriveBR->Set(-1);
        
        //if(ap_fwdCycleTapButton->GetState() == true)
        if(ap_fwdCycleTapButton->GetState() == true)
        {
            nextState = STATE_MACHINE4_STATE_INIT;
        }
        else if(ap_stateMachine4Timer->HasPeriodPassed(1.0))
        {
            ap_stateMachine4Timer->Reset();
            if(a_stateMachine4Direction == STATE_MACHINE4_DIR_FWD)
            {
                nextState = STATE_MACHINE4_STATE_5;
            }
            else
            {
                nextState = STATE_MACHINE4_STATE_3;
            }
        }
        break;
    case STATE_MACHINE4_STATE_5:
        ap_scDriveFL->Set(0);
        ap_scDriveBL->Set(0);
        ap_scDriveFR->Set(-1);
        ap_scDriveBR->Set(-1);
        
        //if(ap_fwdCycleTapButton->GetState() == true)
        if(ap_fwdCycleTapButton->GetState() == true)
        {
            nextState = STATE_MACHINE4_STATE_INIT;
        }
        else if(ap_stateMachine4Timer->HasPeriodPassed(1.0))
        {
            ap_stateMachine4Timer->Reset();
            if(a_stateMachine4Direction == STATE_MACHINE4_DIR_FWD)
            {
                nextState = STATE_MACHINE4_STATE_6;
            }
            else
            {
                nextState = STATE_MACHINE4_STATE_4;
            }
        }
        break;
    case STATE_MACHINE4_STATE_6:
        ap_scDriveFL->Set(-1);
        ap_scDriveBL->Set(-1);
        ap_scDriveFR->Set(-1);
        ap_scDriveBR->Set(-1);
        
        //if(ap_fwdCycleTapButton->GetState() == true)
        if(ap_fwdCycleTapButton->GetState() == true)
        {
            nextState = STATE_MACHINE4_STATE_INIT;
        }
        else if(ap_stateMachine4Timer->HasPeriodPassed(1.0))
        {
            ap_stateMachine4Timer->Reset();
            if(a_stateMachine4Direction == STATE_MACHINE4_DIR_FWD)
            {
                nextState = STATE_MACHINE4_STATE_7;
            }
            else
            {
                nextState = STATE_MACHINE4_STATE_5;
            }
        }
        break;
    case STATE_MACHINE4_STATE_7:
        ap_scDriveFL->Set(-1);
        ap_scDriveBL->Set(-1);
        ap_scDriveFR->Set(0);
        ap_scDriveBR->Set(0);
        
        //if(ap_fwdCycleTapButton->GetState() == true)
        if(ap_fwdCycleTapButton->GetState() == true)
        {
            nextState = STATE_MACHINE4_STATE_INIT;
        }
        else if(ap_stateMachine4Timer->HasPeriodPassed(1.0))
        {
            ap_stateMachine4Timer->Reset();
            if(a_stateMachine4Direction == STATE_MACHINE4_DIR_FWD)
            {
                nextState = STATE_MACHINE4_STATE_8;
            }
            else
            {
                nextState = STATE_MACHINE4_STATE_6;
            }
        }
        break;
    case STATE_MACHINE4_STATE_8:
        ap_scDriveFL->Set(-.5);
        ap_scDriveBL->Set(-.5);
        ap_scDriveFR->Set(-.5);
        ap_scDriveBR->Set(-.5);
        
        //if(ap_fwdCycleTapButton->GetState() == true)
        if(ap_fwdCycleTapButton->GetState() == true)
        {
            nextState = STATE_MACHINE4_STATE_INIT;
        }
        else if(ap_stateMachine4Timer->HasPeriodPassed(1.0))
        {
            ap_stateMachine4Timer->Reset();
            if(a_stateMachine4Direction == STATE_MACHINE4_DIR_FWD)
            {
                nextState = STATE_MACHINE4_STATE_1;
            }
            else
            {
                nextState = STATE_MACHINE4_STATE_7;
            }
        }
        break;
    default:
        ap_scDriveFL->Set(0);
        ap_scDriveBL->Set(0);
        ap_scDriveFR->Set(0);
        ap_scDriveBR->Set(0);
        
        nextState = STATE_MACHINE4_STATE_1;
        
        break;
    }
    
    a_stateMachine4State = nextState;
    printf("DIR: %d  STATE %d\n", a_stateMachine4Direction, a_stateMachine4State);
}

void WsRobot6wdProto::hwStateMachine1(void)
{
    HwStateMachine1StateT nextState = a_hwStateMachine1State;
    
    switch(a_hwStateMachine1State)
    {
        case HW_STATE_MACHINE1_STATE_DRIVE:
            ap_scDriveFL->Set(1);
            ap_scDriveBL->Set(1);
            ap_scDriveFR->Set(1);
            ap_scDriveBR->Set(1);
            if(ap_hwStateMachineTimer->HasPeriodPassed(2.0))
            {
                ap_hwStateMachineTimer->Reset();
                nextState = HW_STATE_MACHINE1_STATE_TURN;
            }
            break;
        case HW_STATE_MACHINE1_STATE_TURN:
            ap_scDriveFL->Set(1);
            ap_scDriveBL->Set(1);
            ap_scDriveFR->Set(-1);
            ap_scDriveBR->Set(-1);
            if(ap_hwStateMachineTimer->HasPeriodPassed(1.0))
            {
                ap_hwStateMachineTimer->Reset();
                nextState = HW_STATE_MACHINE1_STATE_DRIVE;
            }
            break;
        default:
            ap_scDriveFL->Set(0);
            ap_scDriveBL->Set(0);
            ap_scDriveFR->Set(0);
            ap_scDriveBR->Set(0);
            break;
    }
    
    a_hwStateMachine1State = nextState;

}
void WsRobot6wdProto::hwStateMachine2(void)
{
    HwStateMachine2StateT nextState = a_hwStateMachine2State;
    bool buttonA = ap_fwdCycleTapButton->GetState();
    bool buttonB = ap_revCycleTapButton->GetState();
    //bool buttonB = false;
    
    printf("PROBLEM 2 - %d (%d, %d) %d\n", a_hwStateMachine2State, buttonA, buttonB, ap_antiTurboButton->GetState());
    switch(a_hwStateMachine2State)
    {
        case HW_STATE_MACHINE2_STATE_WAIT:
            ap_scDriveFL->Set(0);
            ap_scDriveBL->Set(0);
            ap_scDriveFR->Set(0);
            ap_scDriveBR->Set(0);
            
            if(buttonA == true)
            {
               nextState = HW_STATE_MACHINE2_STATE_SET_DRIVE_CW;
            }
            else if(buttonB == true)
            {
               nextState = HW_STATE_MACHINE2_STATE_SET_DRIVE_CCW;
            }
            
            
            break;
        case HW_STATE_MACHINE2_STATE_SET_DRIVE_CW:
            ap_scDriveFL->Set(0);
            ap_scDriveBL->Set(0);
            ap_scDriveFR->Set(0);
            ap_scDriveBR->Set(0);
            
            a_hwStateMachineDirection = 1;
            ap_hwStateMachineTimer->Reset();
            
            nextState = HW_STATE_MACHINE2_STATE_DRIVE;
            break;
        case HW_STATE_MACHINE2_STATE_SET_DRIVE_CCW:
            ap_scDriveFL->Set(0);
            ap_scDriveBL->Set(0);
            ap_scDriveFR->Set(0);
            ap_scDriveBR->Set(0);
            
            a_hwStateMachineDirection = -1;
            ap_hwStateMachineTimer->Reset();
            
            nextState = HW_STATE_MACHINE2_STATE_DRIVE;
            break;
        case HW_STATE_MACHINE2_STATE_DRIVE:
            ap_scDriveFL->Set(1);
            ap_scDriveBL->Set(1);
            ap_scDriveFR->Set(1);
            ap_scDriveBR->Set(1);
            if(ap_hwStateMachineTimer->HasPeriodPassed(2.0))
            {
                ap_hwStateMachineTimer->Reset();
                nextState = HW_STATE_MACHINE2_STATE_TURN;
            }
            break;
        case HW_STATE_MACHINE2_STATE_TURN:
            ap_scDriveFL->Set(1 * a_hwStateMachineDirection);
            ap_scDriveBL->Set(1 * a_hwStateMachineDirection);
            ap_scDriveFR->Set(-1 * a_hwStateMachineDirection);
            ap_scDriveBR->Set(-1 * a_hwStateMachineDirection);
            if(ap_hwStateMachineTimer->HasPeriodPassed(1.0))
            {
                ap_hwStateMachineTimer->Reset();
                nextState = HW_STATE_MACHINE2_STATE_DRIVE;
            }
            break;
        default:
            ap_scDriveFL->Set(0);
            ap_scDriveBL->Set(0);
            ap_scDriveFR->Set(0);
            ap_scDriveBR->Set(0);
            break;
    }
    
    a_hwStateMachine2State = nextState;

}
void WsRobot6wdProto::hwStateMachine3(void)
{
    HwStateMachine3StateT nextState = a_hwStateMachine3State;
    bool buttonA = ap_fwdCycleTapButton->GetState();
    bool buttonB = ap_revCycleTapButton->GetState();
    //bool buttonB = false;
    
    printf("PROBLEM 3 - %d (%d, %d) %d\n", a_hwStateMachine3State, buttonA, buttonB, ap_antiTurboButton->GetState());
    switch(a_hwStateMachine3State)
    {
        case HW_STATE_MACHINE3_STATE_WAIT:
            ap_scDriveFL->Set(0);
            ap_scDriveBL->Set(0);
            ap_scDriveFR->Set(0);
            ap_scDriveBR->Set(0);
            a_hwStateMachineTurns = 0;
            
            if(buttonA == true)
            {
               nextState = HW_STATE_MACHINE3_STATE_SET_DRIVE_CW;
            }
            else if(buttonB == true)
            {
               nextState = HW_STATE_MACHINE3_STATE_SET_DRIVE_CCW;
            }
            
            
            break;
        case HW_STATE_MACHINE3_STATE_SET_DRIVE_CW:
            ap_scDriveFL->Set(0);
            ap_scDriveBL->Set(0);
            ap_scDriveFR->Set(0);
            ap_scDriveBR->Set(0);
            
            a_hwStateMachineDirection = 1;
            ap_hwStateMachineTimer->Reset();
            
            nextState = HW_STATE_MACHINE3_STATE_DRIVE;
            break;
        case HW_STATE_MACHINE3_STATE_SET_DRIVE_CCW:
            ap_scDriveFL->Set(0);
            ap_scDriveBL->Set(0);
            ap_scDriveFR->Set(0);
            ap_scDriveBR->Set(0);
            
            a_hwStateMachineDirection = -1;
            ap_hwStateMachineTimer->Reset();
            
            nextState = HW_STATE_MACHINE3_STATE_DRIVE;
            break;
        case HW_STATE_MACHINE3_STATE_DRIVE:
            ap_scDriveFL->Set(1);
            ap_scDriveBL->Set(1);
            ap_scDriveFR->Set(1);
            ap_scDriveBR->Set(1);
            if(ap_hwStateMachineTimer->HasPeriodPassed(2.0))
            {
                ap_hwStateMachineTimer->Reset();
                a_hwStateMachineTurns++;
                nextState = HW_STATE_MACHINE3_STATE_TURN;
            }
            break;
        case HW_STATE_MACHINE3_STATE_TURN:
            ap_scDriveFL->Set(1 * a_hwStateMachineDirection);
            ap_scDriveBL->Set(1 * a_hwStateMachineDirection);
            ap_scDriveFR->Set(-1 * a_hwStateMachineDirection);
            ap_scDriveBR->Set(-1 * a_hwStateMachineDirection);
            if(ap_hwStateMachineTimer->HasPeriodPassed(1.0))
            {
                if(a_hwStateMachineTurns < 4)
                {
                    ap_hwStateMachineTimer->Reset();
                    nextState = HW_STATE_MACHINE3_STATE_DRIVE;
                }
                else
                {
                    nextState = HW_STATE_MACHINE3_STATE_WAIT;
                }
            }
            break;
        default:
            ap_scDriveFL->Set(0);
            ap_scDriveBL->Set(0);
            ap_scDriveFR->Set(0);
            ap_scDriveBR->Set(0);
            break;
    }
    
    a_hwStateMachine3State = nextState;

}
void WsRobot6wdProto::hwStateMachine4(void)
{
    HwStateMachine4StateT nextState = a_hwStateMachine4State;
    printf("STATE 4: %d %d\n", a_hwStateMachine4State, ap_antiTurboButton->GetState());
    switch (a_hwStateMachine4State)
    {
        case HW_STATE_MACHINE4_STATE_WAIT_FOR_START:
            ap_scDriveFL->Set(0);
            ap_scDriveBL->Set(0);
            ap_scDriveFR->Set(0);
            ap_scDriveBR->Set(0);
            a_hwStateMachineDirection = 1;
            if(ap_antiTurboButton->GetState() == true)
            {
                nextState = HW_STATE_MACHINE4_STATE_DRIVE;
            }
            break;
        case HW_STATE_MACHINE4_STATE_DRIVE:
            ap_scDriveFL->Set(1 *  a_hwStateMachineDirection);
            ap_scDriveBL->Set(1 *  a_hwStateMachineDirection);
            ap_scDriveFR->Set(1 *  a_hwStateMachineDirection);
            ap_scDriveBR->Set(1 *  a_hwStateMachineDirection);
            if(ap_antiTurboButton->GetState() == false)
            {
                nextState = HW_STATE_MACHINE4_STATE_WAIT_FOR_BUTTON;
            }
            break;
        case HW_STATE_MACHINE4_STATE_WAIT_FOR_BUTTON:
            ap_scDriveFL->Set(0);
            ap_scDriveBL->Set(0);
            ap_scDriveFR->Set(0);
            ap_scDriveBR->Set(0);
            if(ap_antiTurboButton->GetState() == true)
            {
                a_hwStateMachineDirection *= -1;
                nextState = HW_STATE_MACHINE4_STATE_DRIVE;
            }
            break;
        default:
            break;
    }
    a_hwStateMachine4State =  nextState;

}
void WsRobot6wdProto::hwStateMachine5(void)
{
    HwStateMachine5StateT nextState = a_hwStateMachine5State;
    
    switch(a_hwStateMachine5State)
    {
        case HW_STATE_MACHINE5_STATE_WAIT_FOR_START:
            a_hwStateMachineDirection = 1;
            a_hwStateMachineTurns = 0;
            ap_scDriveFL->Set(0);
            ap_scDriveBL->Set(0);
            ap_scDriveFR->Set(0);
            ap_scDriveBR->Set(0);
            
            if(ap_antiTurboButton->GetState() == true)
            {
                nextState = HW_STATE_MACHINE5_STATE_DRIVE;
            }
            
            break;
        case HW_STATE_MACHINE5_STATE_DRIVE:
            ap_scDriveFL->Set(1 * a_hwStateMachineDirection);
            ap_scDriveBL->Set(1 * a_hwStateMachineDirection);
            ap_scDriveFR->Set(1 * a_hwStateMachineDirection);
            ap_scDriveBR->Set(1 * a_hwStateMachineDirection);
            
            if(ap_antiTurboButton->GetState() == false)
            {
                nextState = HW_STATE_MACHINE5_STATE_WAIT_FOR_BUTTON;
            }
            
            break;
        case HW_STATE_MACHINE5_STATE_WAIT_FOR_BUTTON:
            ap_scDriveFL->Set(0);
            ap_scDriveBL->Set(0);
            ap_scDriveFR->Set(0);
            ap_scDriveBR->Set(0);
            
            
            if(ap_antiTurboButton->GetState() == true)
            {
                nextState = HW_STATE_MACHINE5_STATE_DRIVE;
                a_hwStateMachineDirection *= -1;
                
                if( a_hwStateMachineDirection == 1)
                {
                   a_hwStateMachineTurns++;
                }
            }
            
            if(a_hwStateMachineTurns >= 5)
            {
                nextState = HW_STATE_MACHINE5_STATE_DONE;
            }
            
            break;
            
        case HW_STATE_MACHINE5_STATE_DONE:
            ap_scDriveFL->Set(0);
            ap_scDriveBL->Set(0);
            ap_scDriveFR->Set(0);
            ap_scDriveBR->Set(0);
            break;
            
        default:
            ap_scDriveFL->Set(0);
            ap_scDriveBL->Set(0);
            ap_scDriveFR->Set(0);
            ap_scDriveBR->Set(0);
            break;
    }

    a_hwStateMachine5State = nextState;
}
