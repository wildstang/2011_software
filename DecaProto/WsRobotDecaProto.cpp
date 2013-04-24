#include <stdio.h>
#include "WsRobotDecaProto.h"


WsRobotDecaProto::WsRobotDecaProto(void)
{
    printf("WsRobotDecaProto Constructor Started\n");
    /************************* Start of object construction ************************/
    
    /********************************** Inputs *************************************/
    
    ap_driveGamepad = new Gamepad(1);
    
    /********************************** Input Control Methods  *********************/
    
    ap_driveBaseInput = new WsControlMethodDeca();
    ap_driveBaseInput->assignInputs(ap_driveGamepad,
                                    //Gamepad::kLeftYAxis, Gamepad::kRightXAxis,   // HALODRIVE
                                    Gamepad::kRightYAxis, Gamepad::kRightXAxis, // NORMAL SINGLESTICK
                                    Gamepad::kLeftTrigger, Gamepad::kRightXAxis);
                        
            
    
    /********************************** Outputs *************************************/
    
    ap_scDriveR1 = new Jaguar(1);
    ap_scDriveR2 = new Jaguar(2);
    ap_scDriveL1 = new Jaguar(3);
    ap_scDriveL2 = new Jaguar(4);
    
    ap_scDeca1 = new Victor(5);
    ap_scDeca2 = new Victor(6);
    ap_solDeca = new Solenoid(1);
    
    
    
    
    /********************************** Output Objects  *********************/
    
    ap_driveBaseOutput = new WsDriveBaseDeca();
    ap_driveBaseOutput->assignControllers( ap_scDriveL1,
                                           ap_scDriveL2,
                                           ap_scDriveR1,
                                           ap_scDriveR2,
                                           ap_scDeca1,
                                           ap_scDeca2,
                                           ap_solDeca);
                                           
    
        /*
    ap_robotDrive = new RobotDrive( ap_scDriveFL,
            ap_scDriveBL,
            ap_scDriveFR,
            ap_scDriveBR);
    ap_robotDrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
    ap_robotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
    */
    
    
    /**************************** End of object construction*************************/
    // Initialize counters to record the number of loops completed in autonomous and teleop modes
    a_autoPeriodicLoops = 0;
    a_disabledPeriodicLoops = 0;
    a_telePeriodicLoops = 0;
    
    
    printf("WsRobotDecaProto Constructor Completed\n");
}

WsRobotDecaProto::~WsRobotDecaProto(void)
{
    /********************************** Inputs *************************************/
    
    delete ap_driveGamepad;
    ap_driveGamepad = NULL;
    
    /********************************** Input Control Methods  *********************/
    
    delete ap_driveBaseInput;
    ap_driveBaseInput = NULL;
 
    /********************************** Outputs *************************************/
    
    delete ap_scDriveL1;
    ap_scDriveL1 = NULL;
    
    delete ap_scDriveR1;
    ap_scDriveR1 = NULL;
    
    delete ap_scDriveL2;
    ap_scDriveL2 = NULL;
    
    delete ap_scDriveR2;
    ap_scDriveR2 = NULL;
    
    delete ap_scDeca1;
    ap_scDeca1 = NULL;
    
    delete ap_scDeca2;
    ap_scDeca2 = NULL;
    
    delete ap_solDeca;
    ap_solDeca = NULL;
}

/********************************** Init Routines *************************************/

void WsRobotDecaProto::RobotInit(void)
{
    printf("RobotInit() completed.\n");
}

void WsRobotDecaProto::DisabledInit(void)
{
    a_disabledPeriodicLoops = 0;
}

void WsRobotDecaProto::AutonomousInit(void)
{
    a_autoPeriodicLoops = 0;
    //printf("AutonomousInit() completed.\n");
}

void WsRobotDecaProto::TeleopInit(void)
{
    a_telePeriodicLoops = 0;
    
    //printf("TeleopPeriodicInit() completed.\n");
}

/********************************** Periodic Routines *************************************/

void WsRobotDecaProto::DisabledPeriodic(void)
{
    WsDriveVector driveVector;
    WsDriveVector decaVector;
    WsControlMethodDeca::WsDecaStateT decaState; 
    
    GetWatchdog().Feed();
    ap_driveBaseInput->readInputs();
    
    ap_driveBaseInput->getDriveVector(&driveVector);
    ap_driveBaseInput->getDecaState(&decaState, &decaVector);
    
    
    /*
    printf("Drive D: %f S: %f  Deca <%d> S: %f\n",
            driveVector.a_direction,
            driveVector.a_speed,
            decaState,
            decaVector.a_speed);
            */
    
    ap_driveBaseOutput->setOutputs(&driveVector, &decaVector, decaState);
    
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
    a_disabledPeriodicLoops++;
}

void WsRobotDecaProto::AutonomousPeriodic(void)
{
    GetWatchdog().Feed();
    
    //printf("AutonomousPeriodic() %d\n", a_autoPeriodicLoops);
    a_autoPeriodicLoops++;
}

void WsRobotDecaProto::TeleopPeriodic(void)
{
    WsDriveVector driveVector;
    WsDriveVector decaVector;
    WsControlMethodDeca::WsDecaStateT decaState; 
    
    GetWatchdog().Feed();
    
    //printf("TeleopPeriodic() %d\n", a_telePeriodicLoops);
    a_telePeriodicLoops++;
    
    ap_driveBaseInput->readInputs();
    
    ap_driveBaseInput->getDriveVector(&driveVector);
    ap_driveBaseInput->getDecaState(&decaState, &decaVector);
    
    ap_driveBaseOutput->setOutputs(&driveVector, &decaVector, decaState);
}

/********************************** Continuous Routines *************************************/

void WsRobotDecaProto::DisabledContinuous(void)
{
    // This function is unused, but is included because the default WPILib
    // function has a print in it that makes debugging difficult
}

void WsRobotDecaProto::AutonomousContinuous(void)
{
    // This function is unused, but is included because the default WPILib
    // function has a print in it that makes debugging difficult
}

void WsRobotDecaProto::TeleopContinuous(void)
{
    // This function is unused, but is included because the default WPILib
    // function has a print in it that makes debugging difficult
}
