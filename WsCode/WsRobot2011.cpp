#include <stdio.h>
#include "DriverStationLCD.h"
#include "WsRobot2011.h"
#include "WsRollerClaw.h"
#include "WsLarm.h"
#include "WsLift.h"
#include "WsArm.h"
#include "WsMinibot.h"
#include "WsDriveVector.h"
#include "WsControlMethod6WD.h"
#include "WsControlMethodLarm.h"
#include "WsControlMethodMinibot.h"
#include "WsDriveBase6WD.h"
#include "WsDashboard.h"
#include "WsAutonomousMgr.h"
#include "WsDriverStationLED.h"
#include "WsShmCamera.h"
#include "WsVisionTask.h"
#include "WsSmartLED.h"

#define ENABLE_DASHBOARD 1
#define ENABLE_VISION_TASK 1

#if ENABLE_VISION_TASK
Task g_visionTask("WsVision", (FUNCPTR)vision_task_main);
#endif


WsRobot2011::WsRobot2011(void)
{
    printf("WsRobot2011 Constructor Started\n");

    ap_smartLed = WsSmartLED::Instance();
    ap_smartLed->assignDigOut(DIG_OUT_LED0, DIG_OUT_LED1, DIG_OUT_LED2, DIG_OUT_LED3);
    ap_smartLed->send();

    a_calibrationMode = false;
    ap_calib = WsCalibration::getInstance();
    /*
#if ENABLE_DASHBOARD
    ap_dashboard = WsDashboard::getInstance(m_ds);
#endif
    ap_dsLcd = DriverStationLCD::GetInstance();
    */
    printf("1\n");

    ap_camera = new WsShmCamera();
#if ENABLE_VISION_TASK
    g_visionTask.Start();
#endif

    printf("2\n");
    
    /********** Inputs *************************************/
    ap_driveVector = new WsDriveVector();
    ap_inputManager = InputManager::Instance();

    printf("3\n");
    /********** OI Inputs **********/
    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_CALIB,
                                    InputManager::GAMEPAD_INDEX_OI,
                                    Gamepad::kTriangleButton,
                                    InputManager::BUTTON_STYLE_STANDARD );

    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_ARM_FEEDBACK_DISABLE,
                                    InputManager::GAMEPAD_INDEX_OI,
                                    Gamepad::kSquareButton,
                                    InputManager::BUTTON_STYLE_STANDARD,
                                    true);

    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_LED_ENABLE,
                                    InputManager::GAMEPAD_INDEX_OI,
                                    Gamepad::kXButton,
                                    InputManager::BUTTON_STYLE_STANDARD,
                                    true);
    
    
    printf("4\n");

    /********** Input Control Methods  *********************/
    ap_controlMethodDrive = new WsControlMethod6WD();
    ap_controlMethodLarm = new WsControlMethodLarm();
    ap_controlMethodMinibot = new WsControlMethodMinibot();
    printf("5\n");
    
    /********** Outputs *************************************/
    /********** Output Objects  *********************/
    ap_larm = NULL;
    ap_lift = NULL;
    ap_arm = NULL;
    ap_driveBase = NULL;
    
    ap_rollerClaw = new WsRollerClaw(SC_CLAW,
                                     SOL_TUBE_RELEASE,
                                     DIG_IN_TUBE_POS);

    ap_arm = new WsArm(SC_ARM_1, SC_ARM_2,
                       ANA_IN_POT_ARM_POS);

    ap_lift = new WsLift(SC_LIFT_1, SC_LIFT_2,
                         DIG_IN_ENC_LIFT_A, DIG_IN_ENC_LIFT_B,
                         DIG_IN_LIFT_BOT, DIG_IN_LIFT_TOP);

    ap_larm = new WsLarm(ap_lift, ap_arm, ap_rollerClaw);

    printf("6\n");
    ap_driveBase = new WsDriveBase6WD( SC_DRIVE_L1, SC_DRIVE_L2,
                                       SC_DRIVE_R1, SC_DRIVE_R2,
                                       DIG_IN_ENC_DRIVE_L_A, DIG_IN_ENC_DRIVE_L_B,
                                       DIG_IN_ENC_DRIVE_R_A, DIG_IN_ENC_DRIVE_R_B,
                                       ANA_IN_GYRO,
                                       SOL_DRIVE_SHIFT );

    printf("7\n");
#if TEST_ANALOG
    ap_testAnalog = new AnalogChannel(ANA_IN_GYRO);
#endif

    ap_minibot = new WsMinibot( DSOL_MINIBOT_DEPLOY_FWD,
                                DSOL_MINIBOT_DEPLOY_REV);

    ap_compressor = new Compressor(DIG_IN_PRESSURE, RELAY_PUMP);
    ap_compressor->Start();

    /********** End of object construction*************************/

    // Initialize counters to record the number of loops completed in autonomous and teleop modes
    a_autoPeriodicLoops = 0;
    a_disabledPeriodicLoops = 0;
    a_telePeriodicLoops = 0;

    /*****  DRIVER CONTROLS ******/
    ap_inputManager->RegisterAxis(InputManager::AXIS_INDEX_DRIVE_THROTTLE,
                                  InputManager::GAMEPAD_INDEX_DRIVER,
                                  Gamepad::kLeftYAxis,
                                  true);

    ap_inputManager->RegisterAxis(InputManager::AXIS_INDEX_DRIVE_TURN,
                                  InputManager::GAMEPAD_INDEX_DRIVER,
                                  Gamepad::kRightXAxis,
                                  false);
    
    ap_inputManager->RegisterDPad(InputManager::DPAD_INDEX_DRIVER,
                                  InputManager::GAMEPAD_INDEX_DRIVER);
    
    vector<Gamepad::ButtonType> shifterButtons;
    shifterButtons.push_back(Gamepad::kRightBumper); // off button
    shifterButtons.push_back(Gamepad::kRightTrigger); // on button
    
    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_DRIVE_SHIFTER,
                                    InputManager::GAMEPAD_INDEX_DRIVER,
                                    shifterButtons,
                                    InputManager::BUTTON_STYLE_MULTISTICKY,
                                    true // invert to make high gear == false
                                    );

    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_DRIVE_TURBO,
                                    InputManager::GAMEPAD_INDEX_DRIVER,
                                    Gamepad::kLeftTrigger,
                                    InputManager::BUTTON_STYLE_STANDARD );
    
    
    /*****  MANUAL LARM CONTROLS ******/
    ap_inputManager->RegisterAxis(InputManager::AXIS_INDEX_ARM,
                                  InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                  Gamepad::kRightYAxis,
                                  true);

    ap_inputManager->RegisterAxis(InputManager::AXIS_INDEX_LIFT,
                                  InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                  Gamepad::kLeftYAxis,
                                  true);

    ap_inputManager->RegisterDPad(InputManager::DPAD_INDEX_MANIPULATOR,
                                  InputManager::GAMEPAD_INDEX_MANIPULATOR);
    
    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_ROLLER_CLAW_IN,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    Gamepad::kRightTrigger,
                                    InputManager::BUTTON_STYLE_STANDARD);

    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_ROLLER_CLAW_OUT,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    Gamepad::kRightBumper,
                                    InputManager::BUTTON_STYLE_STANDARD);

    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_SCORE_TUBE,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    Gamepad::kLeftTrigger,
                                    InputManager::BUTTON_STYLE_STANDARD);

    
    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_MINIBOT_MODE,
                                    InputManager::GAMEPAD_INDEX_OI,
                                    Gamepad::kLeftBumper,
                                    InputManager::BUTTON_STYLE_STANDARD);
    
    /*****  MINIBOT CONTROLS ******/

    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_MINIBOT_DEPLOY,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    Gamepad::kRightTrigger,
                                    InputManager::BUTTON_STYLE_STANDARD);

    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_MINIBOT_RETRACT,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    Gamepad::kLeftTrigger,
                                    InputManager::BUTTON_STYLE_STANDARD);

    /*****  AUTO LARM POSITION INPUTS ******/
    vector<Gamepad::ButtonType> xShiftButtons;
    xShiftButtons.push_back(Gamepad::kXButton); // action button
    xShiftButtons.push_back(Gamepad::kLeftBumper); // shifter button

    vector<Gamepad::ButtonType> squareShiftButtons;
    squareShiftButtons.push_back(Gamepad::kSquareButton); // action button
    squareShiftButtons.push_back(Gamepad::kLeftBumper); // shifter button

    vector<Gamepad::ButtonType> circleShiftButtons;
    circleShiftButtons.push_back(Gamepad::kCircleButton); // action button
    circleShiftButtons.push_back(Gamepad::kLeftBumper); // shifter button

    vector<Gamepad::ButtonType> triangleShiftButtons;
    triangleShiftButtons.push_back(Gamepad::kTriangleButton); // action button
    triangleShiftButtons.push_back(Gamepad::kLeftBumper); // shifter button

    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_LARM_POS_HOME,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    xShiftButtons,
                                    InputManager::BUTTON_STYLE_MULTIFUNCTION_NO_SHIFT);

    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_LARM_POS_FLOOR,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    xShiftButtons,
                                    InputManager::BUTTON_STYLE_MULTIFUNCTION_SHIFT);

    // SCORE 1 BUTTONS
    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_LARM_POS_SCORE_LOW1,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    squareShiftButtons,
                                    InputManager::BUTTON_STYLE_MULTIFUNCTION_NO_SHIFT);

    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_LARM_POS_SCORE_MID1,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    triangleShiftButtons,
                                    InputManager::BUTTON_STYLE_MULTIFUNCTION_NO_SHIFT);

    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_LARM_POS_SCORE_HIGH1,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    circleShiftButtons,
                                    InputManager::BUTTON_STYLE_MULTIFUNCTION_NO_SHIFT);
    // SCORE 2 BUTTONS
    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_LARM_POS_SCORE_LOW2,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    squareShiftButtons,
                                    InputManager::BUTTON_STYLE_MULTIFUNCTION_SHIFT);

    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_LARM_POS_SCORE_MID2,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    triangleShiftButtons,
                                    InputManager::BUTTON_STYLE_MULTIFUNCTION_SHIFT);

    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_LARM_POS_SCORE_HIGH2,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    circleShiftButtons,
                                    InputManager::BUTTON_STYLE_MULTIFUNCTION_SHIFT);

    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_LED_REQUEST_CIRCLE,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    Gamepad::kSelectButton,
                                    InputManager::BUTTON_STYLE_STANDARD);
    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_LED_REQUEST_TRIANGLE,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    Gamepad::kStartButton,
                                    InputManager::BUTTON_STYLE_STANDARD);


    /*****  REGISTER PORT 3 ******/
    ap_inputManager->RegisterDPad(InputManager::DPAD_INDEX_PORT3,
                                  InputManager::GAMEPAD_INDEX_PORT3);

    /*****  REGISTER OI DPAD ******/
    ap_inputManager->RegisterDPad(InputManager::DPAD_INDEX_OI,
                                  InputManager::GAMEPAD_INDEX_OI);


    /**** REGISTER CALIBRATION BUTTONS ****/
    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_ARM_CALIB_BOT,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    Gamepad::kXButton,
                                    InputManager::BUTTON_STYLE_STANDARD);

    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_ARM_CALIB_0,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    Gamepad::kCircleButton,
                                    InputManager::BUTTON_STYLE_STANDARD);

    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_ARM_CALIB_90,
                                    InputManager::GAMEPAD_INDEX_MANIPULATOR,
                                    Gamepad::kTriangleButton,
                                    InputManager::BUTTON_STYLE_STANDARD);

    /**** REGISTER AUTONOMOUS INPUTS ****/
    ap_inputManager->RegisterAxis(InputManager::AXIS_INDEX_AUTO_PROG_SELECTOR,
                                  InputManager::GAMEPAD_INDEX_OI,
                                  Gamepad::kLeftXAxis);

    ap_inputManager->RegisterAxis(InputManager::AXIS_INDEX_AUTO_RACK_SELECTOR,
                                  InputManager::GAMEPAD_INDEX_OI,
                                  Gamepad::kRightYAxis);

    ap_inputManager->RegisterAxis(InputManager::AXIS_INDEX_AUTO_COL_SELECTOR,
                                  InputManager::GAMEPAD_INDEX_OI,
                                  Gamepad::kLeftYAxis);

    ap_inputManager->RegisterAxis(InputManager::AXIS_INDEX_AUTO_HEIGHT_SELECTOR,
                                  InputManager::GAMEPAD_INDEX_OI,
                                  Gamepad::kRightXAxis);

    ap_inputManager->RegisterButton(InputManager::BUTTON_INDEX_AUTO_LOCKIN,
                                    InputManager::GAMEPAD_INDEX_OI,
                                    Gamepad::kCircleButton,
                                    InputManager::BUTTON_STYLE_STANDARD);

    //if(ap_inputManager->GetButtonValue(InputManager::BUTTON_INDEX_LED_ENABLE) == true)
    {
        ap_smartLed->setCommand(WsSmartLED::LED_CODE_INITIALIZED);
        ap_smartLed->send();
    }

#if ENABLE_DASHBOARD
    ap_dashboard = WsDashboard::getInstance(m_ds);
#endif
    ap_dsLcd = DriverStationLCD::GetInstance();

    printf("WsRobot2011 Constructor Completed\n");
}

WsRobot2011::~WsRobot2011(void)
{
    //if(ap_inputManager->GetButtonValue(InputManager::BUTTON_INDEX_LED_ENABLE) == true)
    {
        ap_smartLed->setCommand(WsSmartLED::LED_SHUTDOWN);
        ap_smartLed->send();
    }
    ap_smartLed->Destroy();
    delete ap_smartLed;
    ap_smartLed = NULL;
    
    /********** Inputs **********/
    delete ap_inputManager;
    ap_inputManager = NULL;

    delete ap_driveVector;
    ap_driveVector = NULL;

    delete ap_controlMethodDrive;
    ap_controlMethodDrive = NULL;

    delete ap_controlMethodLarm;
    ap_controlMethodLarm = NULL;
    
    delete ap_controlMethodMinibot;
    ap_controlMethodMinibot = NULL;
    
    /********** Input Control Methods  **********/
    /********** Outputs **********/
    delete ap_larm;
    ap_larm = NULL;

    delete ap_lift;
    ap_lift = NULL;

    delete ap_arm;
    ap_arm = NULL;

    delete ap_rollerClaw;
    ap_rollerClaw = NULL;

    delete ap_driveBase;
    ap_driveBase = NULL;

    delete ap_minibot;
    ap_minibot = NULL;
    
    delete ap_camera;
    ap_camera = NULL;
    
    ap_compressor->Stop();
    delete ap_compressor;
    ap_compressor = NULL;

    

    /********** Internal Variables **********/
    delete ap_dsLockInLed;
    ap_dsLockInLed = NULL;

    delete ap_autonMgr;
    ap_autonMgr = NULL;

#if TEST_ANALOG
    delete ap_testAnalog;
    ap_testAnalog = NULL;
#endif

    WsCalibration::deleteInstance();
    delete ap_calib;
    ap_calib = NULL;
}

/*
 * Init Routines
 */
void WsRobot2011::RobotInit(void)
{
    printf("RobotInit() completed.\n");
    ap_dsLockInLed = new WsDriverStationLED(1);

    /* Autonomous */
    ap_autonMgr = new WsAutonomousMgr(ap_dsLockInLed);

    ap_autonMgr->assignDriveBase(ap_driveBase);
    ap_autonMgr->assignAppendages(ap_larm);
}

void WsRobot2011::DisabledInit(void)
{
    a_disabledPeriodicLoops = 0;
    ap_inputManager->ResetInputs();
    ap_controlMethodLarm->reset();
    ap_controlMethodMinibot->reset(true);
    ap_minibot->reset();
    ap_larm->reset();
    ap_driveBase->reset();
}

void WsRobot2011::AutonomousInit(void)
{
    a_autoPeriodicLoops = 0;
    ap_inputManager->ResetInputs();
    ap_controlMethodLarm->reset();
    ap_controlMethodMinibot->reset(true);
    ap_minibot->reset();
    ap_larm->reset();
    ap_driveBase->reset();
    ap_autonMgr->beginAutonomous();
    //printf("AutonomousInit() completed.\n");
}

void WsRobot2011::TeleopInit(void)
{
    a_telePeriodicLoops = 0;
    ap_inputManager->ResetInputs();
    ap_controlMethodLarm->reset();
    ap_controlMethodMinibot->reset(true);
    ap_minibot->reset();
    ap_larm->reset();
    ap_driveBase->reset();
    //printf("TeleopPeriodicInit() completed.\n");
}

/*
 * Periodic Routines
 */
void WsRobot2011::DisabledPeriodic(void)
{
    GetWatchdog().Feed();

#if ENABLE_DASHBOARD
    ap_dashboard->resetValues();
#endif
    ap_driveBase->readSensors();

    if (ProcessCalibration() == true)
    {
        // Don't need to do anything here
    }
    else
    {
        ProcessIO();

        if(IsDisabled())
        {
            ap_autonMgr->processLockin();
        }

        if (DriverStation::GetInstance()->IsAutonomous())
        {
            // JUST FLIPPED TO AUTONOMOUS
            WsAutoProgramBase::RackPositionT rackPosition;
            WsAutoProgramBase::ColPositionT colPosition;
            WsAutoProgramBase::PegHeightT pegHeight;
            int progNum;
            //char *progName = "Sleeper";
            char autonString[30];
            char progName[PROG_NAME_LEN];
            bool lockState;

            memset(progName, 0, PROG_NAME_LEN);
            memset(autonString, 0, 30);

            rackPosition = ap_autonMgr->getRackPosition();
            colPosition = ap_autonMgr->getColPosition();
            pegHeight = ap_autonMgr->getPegHeight();
            progNum = ap_autonMgr->getProgNum();
            ap_autonMgr->getProgName(progName);
            lockState = ap_autonMgr->getLockState();
            snprintf(autonString, 30, "(%d,%d,%d,%d) %-15s",
                                       rackPosition, colPosition, pegHeight,
                                       progNum, progName);

            ap_dsLcd->Clear();
            ap_dsLcd->Printf(DriverStationLCD::kMain_Line6, 1, "%s L:%d", autonString, lockState);
            ap_dsLcd->Printf(DriverStationLCD::kUser_Line2, 1, "Peg: %d, %d, %d", rackPosition, colPosition, pegHeight);
            ap_dsLcd->Printf(DriverStationLCD::kUser_Line3, 1, "Prog: %d", progNum);
            ap_dsLcd->Printf(DriverStationLCD::kUser_Line4, 1, "Lock: %d", lockState);
            ap_dsLcd->Printf(DriverStationLCD::kUser_Line5, 1, "%-30s", autonString);
            ap_dsLcd->UpdateLCD();
        }
        else
        {
            printLcdRegularData();
        }
    }

#if TEST_ANALOG
    INT64 rawValue;
    UINT32 count;
    ap_testAnalog->GetAccumulatorOutput(&rawValue, &count);
    printf("%d  %d  %f  %f  %lld  %d\n",
    ap_testAnalog->GetValue(),
    ap_testAnalog->GetAverageValue(),
    ap_testAnalog->GetVoltage(),
    ap_testAnalog->GetAverageVoltage(),
    rawValue, count);
#endif
    
    updateSmartLed();

#if ENABLE_DASHBOARD
    ProcessDashboard();
#endif
}

void WsRobot2011::AutonomousPeriodic(void)
{
    GetWatchdog().Feed();
#if ENABLE_DASHBOARD
    ap_dashboard->resetValues();
#endif
    ap_driveBase->readSensors();
    ap_autonMgr->run();
    //printf("AutonomousPeriodic() %d\n", a_autoPeriodicLoops);
    updateSmartLed();
#if ENABLE_DASHBOARD
    ProcessDashboard();
#endif
    a_autoPeriodicLoops++;

}

void WsRobot2011::TeleopPeriodic(void)
{
    GetWatchdog().Feed();
#if ENABLE_DASHBOARD
    ap_dashboard->resetValues();
#endif
    ap_driveBase->readSensors();
    //printf("TeleopPeriodic() %d\n", a_telePeriodicLoops);
    a_telePeriodicLoops++;

    ProcessIO();
    
    updateSmartLed();
    
#if ENABLE_DASHBOARD
    ProcessDashboard();
#endif

}

/*
 * Continuous Routines
 */
void WsRobot2011::DisabledContinuous(void)
{
    // This function is unused, but is included because the default WPILib
    // function has a print in it that makes debugging difficult
}

void WsRobot2011::AutonomousContinuous(void)
{
    // This function is unused, but is included because the default WPILib
    // function has a print in it that makes debugging difficult
}

void WsRobot2011::TeleopContinuous(void)
{
    // This function is unused, but is included because the default WPILib
    // function has a print in it that makes debugging difficult
}

void WsRobot2011::ProcessIO(void)
{
    ap_inputManager->ReadInputs();

    ap_driveVector->Reset();
    ap_controlMethodDrive->getDriveVector(ap_driveVector);

    WsDriveBase6WD::ShifterStateT shifterState = WsDriveBase6WD::SHIFT_STATE_NONE;
    switch(ap_controlMethodDrive->getGearShifterState())
    {
        case WsControlMethod6WD::SHIFT_CMD_LOW:
            shifterState = WsDriveBase6WD::SHIFT_STATE_LOW;
            break;
        case WsControlMethod6WD::SHIFT_CMD_HIGH:
            shifterState = WsDriveBase6WD::SHIFT_STATE_HIGH;
            break;
        default:
            shifterState = WsDriveBase6WD::SHIFT_STATE_NONE;
            break;
    }
    //printf("SHIFTER STATE %d ", shifterState);

    //WsControlMethod6WD::ShifterInputT shifterInputState = ap_controlMethodDrive->getGearShifterState();

    //ap_driveBase->setVector( ap_controlMethodDrive->getThrottle(), ap_controlMethodDrive->getTurnRate(), ap_controlMethodDrive->dashGetTurbo(), true);
    ap_driveBase->setVector( ap_controlMethodDrive->getThrottle(), ap_controlMethodDrive->getTurnRate(), false, true);
    
    ap_driveBase->setShifter(shifterState);
    //printf("\n");

    WsControlMethodMinibot::MinibotInputModeT minibotMode = ap_controlMethodMinibot->getMinibotMode();

    if(minibotMode == WsControlMethodMinibot::MINIBOT_INPUT_MODE_ON)
    {
        ap_controlMethodLarm->reset();
        ap_larm->reset();
        
        WsMinibot::DeployStateT deployState = WsMinibot::DEPLOY_STATE_NONE;
        
        switch(ap_controlMethodMinibot->getDeployState())
        {
            case WsControlMethodMinibot::MINIBOT_DEPLOY_IN:
                deployState = WsMinibot::DEPLOY_STATE_IN;
                break;
            case WsControlMethodMinibot::MINIBOT_DEPLOY_OUT:
                deployState = WsMinibot::DEPLOY_STATE_OUT;
                break;
            default:
                deployState = WsMinibot::DEPLOY_STATE_NONE;
                break;
        }
        
        ap_minibot->setDeployState(deployState);
        
    }
    else
    {
        ap_controlMethodMinibot->reset(false);
        ap_minibot->reset();

        if ( (ap_inputManager->GetButtonValue(InputManager::BUTTON_INDEX_ARM_FEEDBACK_DISABLE) == false) &&
                ap_controlMethodLarm->getLarmMode() == WsControlMethodLarm::LARM_MODE_AUTO)
        {
            WsLarm::PositionT position = ap_controlMethodLarm->getLarmPosition();
            ap_larm->setPosition(position);
            //printf("AUTO - %d ", position);
        }
        else
        {
            float armSpeed = ap_controlMethodLarm->getArmSpeed();
            float liftSpeed = ap_controlMethodLarm->getLiftSpeed();

            ap_larm->setArmSpeed(armSpeed,
                    ap_inputManager->GetButtonValue(InputManager::BUTTON_INDEX_ARM_FEEDBACK_DISABLE));
            ap_larm->setLiftSpeed(liftSpeed,
                    ap_inputManager->GetButtonValue(InputManager::BUTTON_INDEX_ARM_FEEDBACK_DISABLE));
            //printf("MANU - %.3f %.3f  ", armSpeed, liftSpeed);
            /*
               printf("SW: %d ARM: %d LIFT %d\n",
               ap_larm->dashGetTubePoss(),
               ap_larm->getArmPot(),
               ap_larm->getLiftEncoder());
             */
        }

        WsRollerClaw::RollerSpeedT rollerClawCmd = ap_controlMethodLarm->getRollerClawCmd();
        WsRollerClaw::ReleaseStateT clawReleaseState = ap_controlMethodLarm->getClawReleaseState();

        ap_larm->setRollerSpeed(rollerClawCmd);
        ap_larm->setClawReleaseState(clawReleaseState);

        /*     printf("L: %d  R: %d\n",
               ap_driveBase->getEncoderValue(WsDriveBase6WD::ENC_LOC_L),
               ap_driveBase->getEncoderValue(WsDriveBase6WD::ENC_LOC_R));
         */

        /*
           printf("SW: %d ARM: %d LIFT %d\n",
           ap_larm->dashGetTubePoss(),
           ap_larm->getArmPot(),
           ap_larm->getLiftEncoder());
         */
    }


}


bool WsRobot2011::ProcessCalibration(void)
{
    static UINT8 ledCounter = 0;
    //static bool ledOn = false;
    static bool prevCalibrationMode = false;
    static bool saveData = false;

    INT32 currentArm;

    ap_inputManager->ReadInputs();
    a_calibrationMode = ap_inputManager->GetButtonValue( InputManager::BUTTON_INDEX_CALIB );

    currentArm = ap_larm->getArmPot();

    if(currentArm < 0)
    {
        currentArm = 0;
    }

    if(a_calibrationMode == true)
    {
        printf("CALIB ");
        ap_dsLcd->Clear();
        ap_dsLcd->Printf(DriverStationLCD::kUser_Line2, 1,
                         "Arm Calibration Mode");
        ap_dsLcd->Printf(DriverStationLCD::kUser_Line3, 1,
                         "        B   0   90");
        ap_dsLcd->Printf(DriverStationLCD::kUser_Line4, 1,
                         "Saved: %3d %3d %3d",
                         ap_calib->getValue(WsCalibration::ARM_BOTTOM),
                         ap_calib->getValue(WsCalibration::ARM_0_DEG),
                         ap_calib->getValue(WsCalibration::ARM_90_DEG));
        ap_dsLcd->Printf(DriverStationLCD::kUser_Line5, 1,
                         "Curr:      %3d", currentArm);

        if(ap_inputManager->GetButtonValue( InputManager::BUTTON_INDEX_ARM_CALIB_BOT ) == true)
        {
            printf("BOT %d ", currentArm);
            ap_calib->setValue(WsCalibration::ARM_BOTTOM, currentArm);
            saveData = true;
            ap_dsLcd->Printf(DriverStationLCD::kMain_Line6, 1,
                             "Arm Calib B: %3d", currentArm);
            ap_dsLcd->Printf(DriverStationLCD::kUser_Line3, 1,
                             "      -B-        ");
            ap_dsLcd->Printf(DriverStationLCD::kUser_Line6, 1,
                             "B Calib Saved: %3d", currentArm);
        }
        else if( ap_inputManager->GetButtonValue( InputManager::BUTTON_INDEX_ARM_CALIB_0 ) == true)
        {
            ap_calib->setValue(WsCalibration::ARM_0_DEG, currentArm);
            saveData = true;
            ap_dsLcd->Printf(DriverStationLCD::kMain_Line6, 1,
                             "Arm Calib 0: %3d", currentArm);
            ap_dsLcd->Printf(DriverStationLCD::kUser_Line3, 1,
                             "          -0-    ");
            ap_dsLcd->Printf(DriverStationLCD::kUser_Line6, 1,
                             "0 Calib Saved: %3d", currentArm);
        }
        else if(ap_inputManager->GetButtonValue( InputManager::BUTTON_INDEX_ARM_CALIB_90 ) == true)
        {
            ap_calib->setValue(WsCalibration::ARM_90_DEG, currentArm);
            saveData = true;
            ap_dsLcd->Printf(DriverStationLCD::kMain_Line6, 1,
                             "Arm Calib 90: %3d", currentArm);
            ap_dsLcd->Printf(DriverStationLCD::kUser_Line3, 1,
                             "              -90-");
            ap_dsLcd->Printf(DriverStationLCD::kUser_Line6, 1,
                             "90 Calib Saved: %3d", currentArm);
        }
        else
        {
            ap_dsLcd->Printf(DriverStationLCD::kMain_Line6, 1,
                             "Arm Calib (Curr=%3d)", currentArm);
        }
        ap_dsLcd->UpdateLCD();
    }
    //printf("\n");

    if((saveData == true) &&
       (prevCalibrationMode != a_calibrationMode) &&
       (a_calibrationMode == false))
    {
        ap_calib->saveData();
        saveData = false;
    }

#if 1
    if(ledCounter < 50)
    {
        ledCounter++;
    }
    else
    {
        ledCounter = 0;
    }
#endif

    prevCalibrationMode = a_calibrationMode;

    return a_calibrationMode;
}


void WsRobot2011::updateSmartLed()
{
    WsSmartLED::LedCmdT prevCmd = ap_smartLed->getCommand();
    WsSmartLED::LedCmdT cmd = prevCmd;
    static WsSmartLED::LedCmdT tubeRequestCmd = WsSmartLED::LED_OFF;
    static bool minibotLaunched = false;
    static bool minibotLaunchComplete = false;
    static Timer minibotLaunchedTimer;
    static WsControlMethodMinibot::MinibotInputModeT minibotModePrev = WsControlMethodMinibot::MINIBOT_INPUT_MODE_UNINIT;
    static bool ledEnablePrev = false;
    
    WsControlMethodMinibot::MinibotInputModeT minibotMode = ap_controlMethodMinibot->getMinibotMode();
    WsControlMethodMinibot::MinibotDeployStateT minibotDeploy = ap_controlMethodMinibot->getDeployState();
    bool ledEnable = ap_inputManager->GetButtonValue(InputManager::BUTTON_INDEX_LED_ENABLE);

    bool requestRandom = (ap_inputManager->GetDPadValue(InputManager::DPAD_INDEX_MANIPULATOR) == InputManager::DPAD_DIR_LED_REQUEST_RANDOM);
    bool requestTriangle = ap_inputManager->GetButtonValue(InputManager::BUTTON_INDEX_LED_REQUEST_TRIANGLE);
    bool requestCircle = ap_inputManager->GetButtonValue(InputManager::BUTTON_INDEX_LED_REQUEST_CIRCLE);
    bool requestSquare = (ap_inputManager->GetDPadValue(InputManager::DPAD_INDEX_MANIPULATOR) == InputManager::DPAD_DIR_LED_REQUEST_SQUARE);
    bool hasTube = ap_larm->getTubePossessed();

    static bool flashlightMode = false;
    static bool flashlightButton = false;
    static bool flashlightButtonPrev = false;

    flashlightButton = requestCircle;
    
    if(IsDisabled())
    {
        tubeRequestCmd = WsSmartLED::LED_OFF;
        minibotLaunched = false;
        minibotLaunchComplete = false;
        minibotLaunchedTimer.Stop();
        minibotLaunchedTimer.Reset();

        if(ap_autonMgr->getLockState() == true)
        {
            UINT8 progNum = ap_autonMgr->getProgNum();
            if(progNum == 2 ||
               progNum == 5 ||
               progNum == 7)
            {
                cmd = WsSmartLED::LED_AUTO_SINGLE;
            }
            if(progNum == 4)
            {
                cmd = WsSmartLED::LED_AUTO_DOUBLE_1;
            }
        }
        else if(flashlightButton == true && flashlightButtonPrev == false)
        {
            flashlightMode = !flashlightMode;
        }
        else if(flashlightMode == true)
        {
            cmd = WsSmartLED::LED_FLASHLIGHT;
        }
        else
        {
            cmd = WsSmartLED::LED_CODE_INITIALIZED;
        }

    }
    else if (DriverStation::GetInstance()->IsAutonomous())
    {
        ledEnable = true; // Needed since switch turns off in auto
        tubeRequestCmd = WsSmartLED::LED_OFF;
        minibotLaunched = false;
        minibotLaunchComplete = false;
        minibotLaunchedTimer.Stop();
        minibotLaunchedTimer.Reset();
        flashlightMode = false;

        if(ap_autonMgr->getLockState() == true)
        {
            // Auto running and locked in
            UINT8 progNum = ap_autonMgr->getProgNum();
            if(progNum == 2 ||
               progNum == 5 ||
               progNum == 7)
            {
                cmd = WsSmartLED::LED_AUTO_SINGLE;
            }
            else if(progNum == 4)
            {
                cmd = WsSmartLED::LED_AUTO_DOUBLE_1;
            }
            else
            {
                // Sleeper or other program
                cmd = WsSmartLED::LED_DONT_CARE;
            }

            if(ap_autonMgr->isDone() == true)
            {
                cmd = WsSmartLED::LED_AUTO_DONE;
            }


        }
        else
        {
            // Auto running but not locked in
            cmd = WsSmartLED::LED_DONT_CARE;
        }

        


    }
    else
    {
        flashlightMode = false;

        // Just turned the switch back on after being off.  Initialize to don't care and let somebody override
        if (ledEnablePrev == false && ledEnable == true) // 0 is up
        {
            cmd = WsSmartLED::LED_DONT_CARE;
        }


        if(prevCmd == WsSmartLED::LED_CODE_INITIALIZED ||
           prevCmd == WsSmartLED::LED_AUTO_SINGLE ||
           prevCmd == WsSmartLED::LED_AUTO_DOUBLE_1 ||
           prevCmd == WsSmartLED::LED_AUTO_DOUBLE_2 ||
           prevCmd == WsSmartLED::LED_AUTO_DONE ||
           prevCmd == WsSmartLED::LED_FLASHLIGHT)
        {
            // Just entered teleop
            cmd = WsSmartLED::LED_DONT_CARE;
            minibotLaunchedTimer.Stop();
            minibotLaunchedTimer.Reset();
        }

        // First check to see if we have a tube or not
        // If we don't and we previously did, clear the
        // state
        if(hasTube == true)
        {
            cmd = WsSmartLED::LED_HAS_TUBE;
        }
        else
        {
            if(prevCmd == WsSmartLED::LED_HAS_TUBE)
            {
                cmd = WsSmartLED::LED_DONT_CARE;
            }
        }


        // Process tube request buttons this overrides
        // any previous state
        if(requestRandom == true)
        {
            cmd = WsSmartLED::LED_DONT_CARE;
        }
        else if(requestCircle && requestTriangle)
        {
            cmd = WsSmartLED::LED_OFF;
            tubeRequestCmd = WsSmartLED::LED_REQUEST_GREEN;
        }
        else if(requestTriangle == true)
        {
            if(tubeRequestCmd != WsSmartLED::LED_REQUEST_GREEN)
            {
                cmd = WsSmartLED::LED_OFF;
                tubeRequestCmd = WsSmartLED::LED_REQUEST_TRIANGLE;
            }
        }
        else if(requestCircle == true)
        {
            if(tubeRequestCmd != WsSmartLED::LED_REQUEST_GREEN)
            {
                cmd = WsSmartLED::LED_OFF;
                tubeRequestCmd = WsSmartLED::LED_REQUEST_CIRCLE;
            }
        }
        else if(requestSquare == true)
        {
            cmd = WsSmartLED::LED_OFF;
            tubeRequestCmd = WsSmartLED::LED_REQUEST_SQUARE;
        }
        else
        {
            // No request
            if ((ledEnablePrev == true && ledEnable == true) &&
                prevCmd == WsSmartLED::LED_OFF)
            {
                // A request button was being held
                // and was just released.  Go to the
                // requested state
                cmd = tubeRequestCmd;
            }
        }


        // Minibot mode being on overrides everything else
        if(minibotMode == WsControlMethodMinibot::MINIBOT_INPUT_MODE_ON)
        {
            if(minibotLaunched == true)
            {
                if(minibotLaunchComplete == true)
                {
                    cmd = WsSmartLED::LED_MINIBOT_COMPLETE;
                }
                else if(minibotLaunchedTimer.HasPeriodPassed(1.5))
                {
                    // When the minibot was launched, we start a timer
                    // when that timer expires switch to the minibot complete
                    // state and stop the timer
                    cmd = WsSmartLED::LED_MINIBOT_COMPLETE;
                    minibotLaunchComplete = true;
                }
                else
                {
                    // Timer hasn't expired yet
                    cmd = WsSmartLED::LED_MINIBOT_LAUNCHED;
                }

            }
            else if(minibotDeploy == WsControlMethodMinibot::MINIBOT_DEPLOY_OUT)
            {
                // We're launching the minibot.  Set the variables and start the timer
                // on the initial press
                cmd = WsSmartLED::LED_MINIBOT_LAUNCHED;
                if(minibotLaunched == false)
                {
                    minibotLaunched = true;
                    minibotLaunchComplete = false;
                    minibotLaunchedTimer.Reset();
                    minibotLaunchedTimer.Start();
                }
            }
            else
            {
                cmd = WsSmartLED::LED_MINIBOT_ENABLED;
            }
        }
        else
        {
            if(minibotModePrev == WsControlMethodMinibot::MINIBOT_INPUT_MODE_ON)
            {
                cmd = WsSmartLED::LED_DONT_CARE;
                minibotLaunched = false;
                minibotLaunchComplete = false;
            }
            /*
            if(minibotLaunched == true)
            {
                // If the minibot mode is off and we've already launched
                // the drivers have taken control again.  get back to a
                // don't care state
                minibotLaunched = false;
                minibotLaunchComplete = false;
                cmd = WsSmartLED::LED_DONT_CARE;
            }
            */
            minibotLaunchedTimer.Stop();
            minibotLaunchedTimer.Reset();
        }
    }

    if(ledEnable == false && !flashlightMode) // 0 is up
    {
        cmd = WsSmartLED::LED_OFF;
        minibotLaunched = false;
        minibotLaunchComplete = false;
        tubeRequestCmd = WsSmartLED::LED_OFF;
    }

    ap_smartLed->setCommand(cmd);
    ap_smartLed->send();

    minibotModePrev = minibotMode;
    ledEnablePrev = ledEnable;
    flashlightButtonPrev = flashlightButton;
}

void WsRobot2011::printLcdRegularData(void)
{
  INT32 armPot = ap_larm->getArmPot();
  INT32 liftPos = ap_larm->getLiftEncoder();
  ap_dsLcd->Clear();

  ap_dsLcd->Printf(DriverStationLCD::kMain_Line6, 1, "Arm pot: %3d",
      armPot);
  ap_dsLcd->Printf(DriverStationLCD::kUser_Line2, 1, "Lift enc: %3d",
      liftPos);
  ap_dsLcd->UpdateLCD();
}

void WsRobot2011::ProcessDashboard(void)
{
    // ORDER MATTERS!!!
    dashboardDisplayInputs();
    dashboardDisplayOutput();
    dashboardDisplaySensors();
    dashboardDisplayDriveStraight();
    dashboardDisplayLarm();
    dashboardDisplayAutonomous();
    dashboardDisplayMinibot();
    dashboardDisplayMisc();

    // ADD ANY NECESSARY CLUSTERS ABOVE HERE
    ap_dashboard->update();
}

void WsRobot2011::dashboardDisplayInputs(void)
{
    // Drive values set in control method
    ap_dashboard->setValue(IDX_IN_DRIVE_THROTTLE, ap_controlMethodDrive->dashGetThrottle());
    ap_dashboard->setValue(IDX_IN_DRIVE_TURN, ap_controlMethodDrive->dashGetTurn());
    ap_dashboard->setValue(IDX_IN_DRIVE_TURBO, ap_controlMethodDrive->dashGetTurbo());
    ap_dashboard->setValue(IDX_IN_DRIVE_SHIFTER, ap_controlMethodDrive->dashGetShifter());
}

void WsRobot2011::dashboardDisplayOutput(void)
{
    // Drive outputs set in drive base

    float leftSpeed = 0;
    float rightSpeed = 0;


    ap_driveBase->dashGetOutputSpeeds(&leftSpeed, &rightSpeed);

    ap_dashboard->setValue(IDX_OUT_DRIVE_RIGHT, rightSpeed);
    ap_dashboard->setValue(IDX_OUT_DRIVE_LEFT, leftSpeed);
    ap_dashboard->setValue(IDX_OUT_DRIVE_SHIFTER, ap_driveBase->dashGetShifter());


    // larm outputs set in larm output class
    ap_dashboard->setValue(IDX_OUT_CLAW_SPEED, 0);
    ap_dashboard->setValue(IDX_OUT_CLAW_RELEASE, 0);
    ap_dashboard->setValue(IDX_OUT_LIFT_SPEED, 0);
    ap_dashboard->setValue(IDX_OUT_ARM_SPEED, 0);
}

void WsRobot2011::dashboardDisplaySensors(void)
{
    INT32 leftEnc = 0;
    INT32 rightEnc = 0;

    ap_driveBase->dashGetEncoderVals(&leftEnc, &rightEnc);

    ap_dashboard->setValue(IDX_SENSOR_ENC_LEFT, leftEnc);
    ap_dashboard->setValue(IDX_SENSOR_ENC_RIGHT, rightEnc);
    ap_dashboard->setValue(IDX_SENSOR_GYRO_ANGLE, ap_driveBase->dashGetGyroAngle());
    ap_dashboard->setValue(IDX_SENSOR_SW_TUBE_POSS, ap_larm->dashGetTubePoss());
    ap_dashboard->setValue(IDX_SENSOR_ENC_LIFT, ap_larm->dashGetLiftEncoder());
    ap_dashboard->setValue(IDX_SENSOR_POT_ARM, ap_larm->dashGetArmPot());
    ap_dashboard->setValue(IDX_SENSOR_SW_LIFT_BOT, ap_larm->dashGetLiftSwBot());
    ap_dashboard->setValue(IDX_SENSOR_SW_LIFT_TOP, ap_larm->dashGetLiftSwTop());
}

void WsRobot2011::dashboardDisplayDriveStraight(void)
{
    float cmd_left = 0;
    float cmd_right = 0;
    float adj_left = 0;
    float adj_right = 0;
    INT32 enc_snap = 0;
    INT32 enc_diff = 0;

    ap_driveBase->dashGetDriveStraightParams( &cmd_left,
                                              &cmd_right,
                                              &adj_left,
                                              &adj_right,
                                              &enc_snap,
                                              &enc_diff);

    ap_dashboard->setValue(IDX_DRIVESTRAIGHT_CMD_SPEED_LEFT, cmd_left);
    ap_dashboard->setValue(IDX_DRIVESTRAIGHT_CMD_SPEED_RIGHT, cmd_right);
    ap_dashboard->setValue(IDX_DRIVESTRAIGHT_ADJ_SPEED_LEFT, adj_left);
    ap_dashboard->setValue(IDX_DRIVESTRAIGHT_ADJ_SPEED_RIGHT, adj_right);
    ap_dashboard->setValue(IDX_DRIVESTRAIGHT_ENC_SNAPPED_DIFF, enc_snap);
    ap_dashboard->setValue(IDX_DRIVESTRAIGHT_ENC_CURR_DIFF, enc_diff);

}

void WsRobot2011::dashboardDisplayLarm(void)
{
    ap_dashboard->setValue(IDX_LARM_SETPOINT_ARM, ap_larm->dashGetArmSetpoint());
    ap_dashboard->setValue(IDX_LARM_SETPOINT_LIFT, ap_larm->dashGetLiftSetpoint());
    ap_dashboard->setValue(IDX_LARM_POSITION, ap_larm->dashGetLarmPosition());
    ap_dashboard->setValue(IDX_LARM_ARM_IN_POSITION, ap_larm->dashGetArmInPosition());
    ap_dashboard->setValue(IDX_LARM_LIFT_IN_POSITION, ap_larm->dashGetLiftInPosition());
    ap_dashboard->setValue(IDX_LARM_ARM_ANGLE, ap_larm->dashGetArmAngle());
}

void WsRobot2011::dashboardDisplayAutonomous(void)
{
    ap_dashboard->setValue(IDX_AUTO_PROG_NUM, (UINT32)ap_autonMgr->getProgNum());
    ap_dashboard->setValue(IDX_AUTO_RACK_LOC, (UINT32)ap_autonMgr->getRackPosition());
    ap_dashboard->setValue(IDX_AUTO_COL_LOC, (UINT32)ap_autonMgr->getColPosition());
    ap_dashboard->setValue(IDX_AUTO_PEG_HEIGHT, (UINT32)ap_autonMgr->getPegHeight());
    ap_dashboard->setValue(IDX_AUTO_START_DELAY, ap_autonMgr->getStartDelay());
    ap_dashboard->setValue(IDX_AUTO_LOCK, ap_dsLockInLed->getState());
}

void WsRobot2011::dashboardDisplayMinibot(void)
{
    ap_dashboard->setValue(IDX_MINIBOT_MODE, (UINT32) ap_controlMethodMinibot->getMinibotMode());
}

void WsRobot2011::dashboardDisplayMisc(void)
{
    ap_dashboard->setValue(IDX_LED_CMD, (UINT32) ap_smartLed->getOutputValue());
}
