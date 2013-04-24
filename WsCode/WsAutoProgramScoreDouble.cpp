#include "WsAutoProgramScoreDouble.h"
#include "WsPid.h"


WsAutoProgramScoreDouble::WsAutoProgramScoreDouble()
{
    if(ap_calib->isCompetitionRobot() == true)
    {
        ap_driveLowPID = new WsPid(.0022, .0005, 0, 35, 35); // LOW GEAR
        ap_driveLowPID->setMinDoneCycles(5);

        ap_driveHighPID = new WsPid(.0125, .005, .13, 5, 5); // HIGH GEAR
        ap_driveHighPID->setIntegralErrorThresh(20);
        ap_driveHighPID->setMinDoneCycles(10);

#if 1
        ap_rotatePID = new WsPid(.000030,
                                 .0030, // .0024
                                 .00028,
                                 1000 * 2,
                                 1000 * 3); // HIGH GEAR
#else
        // ORIGINAL
        ap_rotatePID = new WsPid(.000015,
                                 .0245,
                                 .00030, 1000 * 2, 1000 * 3); // HIGH GEAR
#endif
        /*
        ap_rotatePID = new WsPid(.0000134,
                                 .000050,
                                 .000008, 1000 * 3, 1000 * 3); // LOW GEAR
                                 */
        ap_rotatePID->setMinDoneCycles(3);
    }
    else
    {
        ap_driveLowPID = new WsPid(.0022, .0005, 0, 35, 35); // LOW GEAR
        ap_driveLowPID->setMinDoneCycles(3);

#if 0
        ap_driveHighPID = new WsPid(.0010, .0035, .035, 35, 35); // HIGH GEAR
        ap_driveHighPID->setMinDoneCycles(1);
#else
        ap_driveHighPID = new WsPid(.0125, .005, .13, 5, 5); // HIGH GEAR
        ap_driveHighPID->setIntegralErrorThresh(20);
        ap_driveHighPID->setMinDoneCycles(10);
#endif

        /*
        ap_rotatePID = new WsPid(.000055,
                                 .029500,
                                 .000250, 1000 * 2, 1000 * 3); // HIGH GEAR
                                 */
        
        
        ap_rotatePID = new WsPid(.000045,
                                 .0245,
                                 .00030, 1000 * 2, 1000 * 3); // HIGH GEAR
        /*
        ap_rotatePID = new WsPid(.0000134,
                                 .000050,
                                 .000008, 1000 * 3, 1000 * 3); // LOW GEAR
                                 */
        ap_rotatePID->setIntegralErrorThresh(45 * 1000);
        ap_rotatePID->setMinDoneCycles(3);
    }
}

WsAutoProgramScoreDouble::~WsAutoProgramScoreDouble()
{
    delete ap_driveLowPID;
    ap_driveLowPID = NULL;
    
    delete ap_driveHighPID;
    ap_driveHighPID = NULL;
    
    delete ap_rotatePID;
    ap_rotatePID = NULL;
}

void WsAutoProgramScoreDouble::initParams(void)
{
    WsAutoNStepBase::WsAutoNStepCmdT testTurnStep;
    WsAutoNStepBase::WsAutoNStepCmdT test2Step;
    WsAutoNStepBase::WsAutoNStepCmdT test3Step;
    WsAutoNStepBase::WsAutoNStepCmdT drive1Step;
    WsAutoNStepBase::WsAutoNStepCmdT drive2Step;
    WsAutoNStepBase::WsAutoNStepCmdT drive3Step;
    WsAutoNStepBase::WsAutoNStepCmdT drive4Step;
    //WsAutoNStepBase::WsAutoNStepCmdT driveAndRaiseStep;
    //WsAutoNStepBase::WsAutoNStepCmdT crawl1Step;
    WsAutoNStepBase::WsAutoNStepCmdT placeTubeStep;
    WsAutoNStepBase::WsAutoNStepCmdT releaseTubeStep;
    WsAutoNStepBase::WsAutoNStepCmdT retreatStep;
    WsAutoNStepBase::WsAutoNStepCmdT retreatStopStep;
    WsAutoNStepBase::WsAutoNStepCmdT turnToTube2Step;
    WsAutoNStepBase::WsAutoNStepCmdT getTube2Step;
    WsAutoNStepBase::WsAutoNStepCmdT clampTube2Step;
    WsAutoNStepBase::WsAutoNStepCmdT turnToRackStep;
    WsAutoNStepBase::WsAutoNStepCmdT settleTurnStep;
    WsAutoNStepBase::WsAutoNStepCmdT initialDrive2Step;
    WsAutoNStepBase::WsAutoNStepCmdT driveAndRaise2Step;
    WsAutoNStepBase::WsAutoNStepCmdT placeTube2Step;
    WsAutoNStepBase::WsAutoNStepCmdT releaseTube2Step;
    WsAutoNStepBase::WsAutoNStepCmdT retreat2Step;

    WsAutoNStepBase::initParams();

    WsLarm::PositionT larmPlaceTubePosition = WsLarm::POSITION_NONE;
    WsLarm::PositionT larmPlaceTube2Position = WsLarm::POSITION_NONE;
    WsLarm::PositionT larmReleaseTubePosition = WsLarm::POSITION_NONE;
    WsLarm::PositionT larmReleaseTube2Position = WsLarm::POSITION_NONE;
    WsLarm::PositionT larmRetreatPosition = WsLarm::POSITION_NONE;

    larmPlaceTubePosition = WsLarm::POSITION_SCORE_HIGH2;
    larmPlaceTube2Position = WsLarm::POSITION_SCORE_HIGH1;
    larmReleaseTubePosition = WsLarm::POSITION_RELEASE_HIGH2;
    larmReleaseTube2Position = WsLarm::POSITION_RELEASE_HIGH1;
    larmRetreatPosition = WsLarm::POSITION_HOME;

#if 0
    testTurnStep.driveType = AUTO_DRIVE_ROTATE;
    testTurnStep.throttle = 0;
    testTurnStep.wheel = .5;
    testTurnStep.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    testTurnStep.driveTimeout = 15;
    //testTurnStep.driveEncoderDist = 0;
    //testTurnStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    testTurnStep.drivePid = ap_rotatePID;
    testTurnStep.rotateAngle = 90;
    testTurnStep.waitForLarm = false;
    testTurnStep.larmPosition = WsLarm::POSITION_NONE;
    testTurnStep.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    testTurnStep.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;
#endif
    
    
    testTurnStep.driveType = AUTO_DRIVE_ROTATE;
    testTurnStep.throttle = 0;
    testTurnStep.wheel = -.4;
    testTurnStep.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    testTurnStep.driveTimeout = 3;
    testTurnStep.driveEncoderDist = -2000;
    testTurnStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    testTurnStep.drivePid = ap_rotatePID;
    testTurnStep.rotateAngle = 129;
    testTurnStep.larmPosition = WsLarm::POSITION_PICKUP_FLOOR;
    testTurnStep.waitForLarm = false;
    testTurnStep.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    testTurnStep.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;
    
    

    test2Step.driveType = AUTO_DRIVE_ENCODER;
    test2Step.throttle = .15;
    test2Step.wheel = 0;
    test2Step.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    test2Step.driveTimeout = 20;
    test2Step.driveEncoderDist = 20000;
    test2Step.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    test2Step.drivePid = ap_driveHighPID;
    //test2Step.rotateAngle = 0;
    test2Step.waitForLarm = false;
    test2Step.larmPosition = WsLarm::POSITION_NONE;
    test2Step.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    test2Step.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;
    
    test3Step.driveType = AUTO_DRIVE_DIST_PID;
    test3Step.throttle = .15;
    test3Step.wheel = 0;
    test3Step.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    test3Step.driveTimeout = 6;
    test3Step.driveEncoderDist = 200;
    test3Step.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    test3Step.drivePid = ap_driveHighPID;
    //test3Step.rotateAngle = 0;
    test3Step.waitForLarm = false;
    test3Step.larmPosition = WsLarm::POSITION_SCORE_HIGH1;
    test3Step.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    test3Step.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;

    drive1Step.driveType = AUTO_DRIVE_ENCODER;
    drive1Step.throttle = .7;
    drive1Step.wheel = 0;
    drive1Step.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    drive1Step.driveTimeout = 3;
    drive1Step.driveEncoderDist = 175;
    drive1Step.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    drive1Step.drivePid = ap_driveHighPID;
    drive1Step.waitForLarm = false;
    drive1Step.larmPosition = WsLarm::POSITION_RAISE_HIGH1;
    drive1Step.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    drive1Step.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;
    
    drive2Step.driveType = AUTO_DRIVE_DIST_PID_SHORT_CIRCUIT;
    drive2Step.throttle = .35;
    drive2Step.wheel = 0;
    drive2Step.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    drive2Step.driveTimeout = 5;
    //drive2Step.driveEncoderDist = 2190;
    drive2Step.driveEncoderDist = 2200;
    drive2Step.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    drive2Step.drivePid = ap_driveHighPID;
    drive2Step.waitForLarm = false;
    drive2Step.larmPosition = WsLarm::POSITION_SCORE_HIGH1;
    drive2Step.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    drive2Step.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;
    
    drive3Step.driveType = AUTO_DRIVE_DIST_PID_SHORT_CIRCUIT;
    drive3Step.throttle = .3;
    drive3Step.wheel = 0;
    drive3Step.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    drive3Step.driveTimeout = 15;
    drive3Step.driveEncoderDist = 245;
    drive3Step.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    drive3Step.drivePid = ap_driveHighPID;
    drive3Step.waitForLarm = false;
    drive3Step.larmPosition = WsLarm::POSITION_SCORE_HIGH1;
    drive3Step.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    drive3Step.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;
    
    drive4Step.driveType = AUTO_DRIVE_DIST_PID_SHORT_CIRCUIT;
    drive4Step.throttle = .15;
    drive4Step.wheel = 0;
    drive4Step.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    drive4Step.driveTimeout = 15;
    drive4Step.driveEncoderDist = 250;
    drive4Step.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    drive4Step.drivePid = ap_driveHighPID;
    drive4Step.waitForLarm = false;
    drive4Step.larmPosition = WsLarm::POSITION_SCORE_HIGH1;
    drive4Step.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    drive4Step.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;

#if 0
    driveAndRaiseStep.driveType = AUTO_DRIVE_ENCODER;
    driveAndRaiseStep.throttle = .15;
    driveAndRaiseStep.wheel = 0;
    driveAndRaiseStep.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    driveAndRaiseStep.driveTimeout = 6;
    driveAndRaiseStep.driveEncoderDist = 250;
    driveAndRaiseStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    driveAndRaiseStep.drivePid = ap_driveHighPID;
    //driveAndRaiseStep.rotateAngle = 0;
    driveAndRaiseStep.waitForLarm = false;
    driveAndRaiseStep.larmPosition = WsLarm::POSITION_SCORE_HIGH1;
    driveAndRaiseStep.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    driveAndRaiseStep.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;

    crawl1Step.driveType = AUTO_DRIVE_DIST_PID_SHORT_CIRCUIT;
    crawl1Step.throttle = .15;
    crawl1Step.wheel = 0;
    crawl1Step.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    crawl1Step.driveTimeout = 6;
    crawl1Step.driveEncoderDist = 230;
    crawl1Step.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    crawl1Step.drivePid = ap_driveHighPID;
    //driveAndRaiseStep.rotateAngle = 0;
    crawl1Step.waitForLarm = false;
    crawl1Step.larmPosition = WsLarm::POSITION_SCORE_HIGH1;
    crawl1Step.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    crawl1Step.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;
#endif

    placeTubeStep.driveType = AUTO_DRIVE_ENCODER;
    placeTubeStep.throttle = -.3;
    placeTubeStep.wheel = 0;
    placeTubeStep.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    placeTubeStep.driveTimeout = 4;
    placeTubeStep.driveEncoderDist = -75; // Causes us to pass drive immediately
    placeTubeStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    placeTubeStep.drivePid = ap_driveHighPID;
    //placeTubeStep.rotateAngle = 0;
    placeTubeStep.larmPosition = WsLarm::POSITION_RELEASE_HIGH1;
    placeTubeStep.waitForLarm = false; // change to true if we drop too soon
    placeTubeStep.rollerClawSpeed = WsRollerClaw::ROLLER_OUT_SLOW;
    placeTubeStep.rollerClawRelease = WsRollerClaw::CLAW_OPEN;

    releaseTubeStep.driveType = AUTO_DRIVE_ENCODER;
    releaseTubeStep.throttle = -.35;
    releaseTubeStep.wheel = 0;
    releaseTubeStep.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    releaseTubeStep.driveTimeout = 4;
    releaseTubeStep.driveEncoderDist = -75;
    releaseTubeStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    //releaseTubeStep.drivePid = ap_driveLowPID;
    //releaseTubeStep.rotateAngle = 0;
    //releaseTubeStep.larmPosition = larmReleaseTubePosition;
    releaseTubeStep.larmPosition = WsLarm::POSITION_RELEASE_HIGH1;
    releaseTubeStep.waitForLarm = false;
    releaseTubeStep.rollerClawSpeed = WsRollerClaw::ROLLER_OUT_SLOW;
    releaseTubeStep.rollerClawRelease = WsRollerClaw::CLAW_OPEN;

    retreatStep.driveType = AUTO_DRIVE_DIST_PID_SHORT_CIRCUIT;
    retreatStep.throttle = -.65;
    retreatStep.wheel = 0;
    retreatStep.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    retreatStep.driveTimeout = 5;
    retreatStep.driveEncoderDist =  -1220; // -1170;
    //retreatStep.driveEncoderDist = -1130;
    retreatStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    retreatStep.drivePid = ap_driveHighPID;
    //retreatStep.rotateAngle = 0;
    retreatStep.waitForLarm = false;
    retreatStep.larmPosition = WsLarm::POSITION_PICKUP_FLOOR;
    retreatStep.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    retreatStep.rollerClawRelease = WsRollerClaw::CLAW_OPEN;

    retreatStopStep.driveType = AUTO_DRIVE_TIME;
    retreatStopStep.throttle = 1;
    retreatStopStep.wheel = 0;
    retreatStopStep.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    retreatStopStep.driveTimeout = .1;
    //retreatStopStep.driveEncoderDist = -2100;
    //retreatStopStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    //retreatStopStep.drivePid = ap_driveLowPID;
    //retreatStopStep.rotateAngle = 0;
    retreatStopStep.larmPosition = WsLarm::POSITION_PICKUP_FLOOR;
    retreatStopStep.rollerClawSpeed = WsRollerClaw::ROLLER_OUT;
    retreatStopStep.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;
    
    turnToTube2Step.driveType = AUTO_DRIVE_ROTATE;
    turnToTube2Step.throttle = 0;
    turnToTube2Step.wheel = -.4;
    turnToTube2Step.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    turnToTube2Step.driveTimeout = 3;
    turnToTube2Step.driveEncoderDist = -2000;
    turnToTube2Step.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    turnToTube2Step.drivePid = ap_rotatePID;
    turnToTube2Step.rotateAngle = 129;
    turnToTube2Step.larmPosition = WsLarm::POSITION_PICKUP_FLOOR;
    turnToTube2Step.waitForLarm = false;
    turnToTube2Step.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    turnToTube2Step.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;
    
    getTube2Step.driveType = AUTO_DRIVE_ENCODER_DISABLE_STRAIGHT;
    getTube2Step.throttle = .24;
    getTube2Step.wheel = 0;
    getTube2Step.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    getTube2Step.driveTimeout = 2;
    if(ap_calib->isCompetitionRobot() == true)
    {
     getTube2Step.driveEncoderDist = 190;
    }
    else
    {
        getTube2Step.driveEncoderDist = 160;
    }
    getTube2Step.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    //getTube2Step.drivePid = ap_driveLowPID;
    //getTube2Step.rotateAngle = 0;
    getTube2Step.waitForLarm = false;
    getTube2Step.larmPosition = WsLarm::POSITION_PICKUP_FLOOR;
    getTube2Step.rollerClawSpeed = WsRollerClaw::ROLLER_IN;
    getTube2Step.rollerClawRelease = WsRollerClaw::CLAW_OPEN;
    
    clampTube2Step.driveType = AUTO_DRIVE_TIME;
    clampTube2Step.throttle = -.2;
    clampTube2Step.wheel = 0;
    clampTube2Step.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    clampTube2Step.driveTimeout = .1;
    //clampTube2Step.driveEncoderDist = 250;
    //clampTube2Step.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    //getTube2Step.drivePid = ap_driveLowPID;
    //getTube2Step.rotateAngle = 0;
    clampTube2Step.waitForLarm = false;
    clampTube2Step.larmPosition = WsLarm::POSITION_PICKUP_FLOOR;
    clampTube2Step.rollerClawSpeed = WsRollerClaw::ROLLER_IN;
    clampTube2Step.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;
    
    turnToRackStep.driveType = AUTO_DRIVE_ROTATE;
    turnToRackStep.throttle = 0;
    turnToRackStep.wheel = .4;
    turnToRackStep.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    turnToRackStep.driveTimeout = 3;
    //turnToRackStep.driveEncoderDist = 0;
    //turnToRackStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    turnToRackStep.drivePid = ap_rotatePID;
    turnToRackStep.waitForLarm = false;
    //turnToRackStep.rotateAngle = -115;
    turnToRackStep.rotateAngle = -110;
    turnToRackStep.larmPosition = WsLarm::POSITION_HOME;
    turnToRackStep.rollerClawSpeed = WsRollerClaw::ROLLER_IN;
    turnToRackStep.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;
    
    settleTurnStep.driveType = AUTO_DRIVE_TIME;
    settleTurnStep.throttle = 0;
    settleTurnStep.wheel = 0;
    settleTurnStep.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    settleTurnStep.driveTimeout = .5;
    //settleTurnStep.driveEncoderDist = 0;
    //settleTurnStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    //settleTurnStep.drivePid = ap_rotatePID;
    //settleTurnStep.rotateAngle = 0;
    settleTurnStep.waitForLarm = false;
    settleTurnStep.larmPosition = WsLarm::POSITION_RAISE_HIGH1;
    settleTurnStep.rollerClawSpeed = WsRollerClaw::ROLLER_IN;
    settleTurnStep.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;

    initialDrive2Step.driveType = AUTO_DRIVE_DIST_PID_SHORT_CIRCUIT;
    initialDrive2Step.throttle = .7;
    initialDrive2Step.wheel = 0;
    initialDrive2Step.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    initialDrive2Step.driveTimeout = 5;
    //initialDrive2Step.driveEncoderDist = 1200;
    initialDrive2Step.driveEncoderDist = 1350;//1300;
    initialDrive2Step.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    initialDrive2Step.drivePid = ap_driveHighPID;
    //initialDrive2Step.rotateAngle = 0;
    initialDrive2Step.waitForLarm = false;
    initialDrive2Step.larmPosition = WsLarm::POSITION_RAISE_HIGH1;
    //initialDrive2Step.larmPosition = larmPlaceTube2Position;
    initialDrive2Step.waitForLarm = false;
    initialDrive2Step.rollerClawSpeed = WsRollerClaw::ROLLER_IN;
    initialDrive2Step.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;

    driveAndRaise2Step.driveType = AUTO_DRIVE_DIST_PID_SHORT_CIRCUIT;
    driveAndRaise2Step.throttle = .25;
    driveAndRaise2Step.wheel = 0;
    driveAndRaise2Step.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    driveAndRaise2Step.driveTimeout = 4;
    //driveAndRaise2Step.driveEncoderDist = 370;
    driveAndRaise2Step.driveEncoderDist = 420;
    driveAndRaise2Step.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    driveAndRaise2Step.drivePid = ap_driveHighPID;
    //driveAndRaise2Step.rotateAngle = 0;
    driveAndRaise2Step.larmPosition = WsLarm::POSITION_SCORE_HIGH1;
    //driveAndRaise2Step.larmPosition = larmPlaceTube2Position;
    driveAndRaise2Step.waitForLarm = false;
    driveAndRaise2Step.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    driveAndRaise2Step.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;

    placeTube2Step.driveType = AUTO_DRIVE_ENCODER;
    placeTube2Step.throttle = -.15;
    placeTube2Step.wheel = 0;
    placeTube2Step.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    placeTube2Step.driveTimeout = 2;
    placeTube2Step.driveEncoderDist = -150; // Causes us to pass drive immediately
    placeTube2Step.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    placeTube2Step.drivePid = ap_driveHighPID;
    //placeTubeStep.rotateAngle = 0;
    placeTube2Step.larmPosition = WsLarm::POSITION_RELEASE_HIGH1;
    placeTube2Step.waitForLarm = false; // change to true if we drop too soon
    placeTube2Step.rollerClawSpeed = WsRollerClaw::ROLLER_OUT_SLOW;
    placeTube2Step.rollerClawRelease = WsRollerClaw::CLAW_OPEN;

    releaseTube2Step.driveType = AUTO_DRIVE_ENCODER;
    releaseTube2Step.throttle = -.5;
    releaseTube2Step.wheel = 0;
    releaseTube2Step.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    releaseTube2Step.driveTimeout = 4;
    releaseTube2Step.driveEncoderDist = -200; // Causes us to pass drive immediately
    releaseTube2Step.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    releaseTube2Step.drivePid = ap_driveHighPID;
    //releaseTubeStep.rotateAngle = 0;
    releaseTube2Step.larmPosition = WsLarm::POSITION_RELEASE_HIGH1;
    releaseTube2Step.waitForLarm = false; // change to true if we drop too soon
    releaseTube2Step.rollerClawSpeed = WsRollerClaw::ROLLER_OUT_SLOW;
    releaseTube2Step.rollerClawRelease = WsRollerClaw::CLAW_OPEN;


#if 0
    addStep(testTurnStep);
    //addStep(test2Step);
    //addStep(test3Step);
#else
    addStep(drive1Step);
    addStep(drive2Step);
    //addStep(drive3Step);
    //addStep(drive4Step);
    //addStep(driveAndRaiseStep);
    //addStep(crawl1Step);
    addStep(placeTubeStep);
    addStep(releaseTubeStep);
    //addStep(retreatStopStep);
    addStep(retreatStep);
    addStep(turnToTube2Step);
    addStep(getTube2Step);
    addStep(clampTube2Step);
    addStep(turnToRackStep);
    addStep(settleTurnStep);
    addStep(initialDrive2Step);
    addStep(driveAndRaise2Step);
    addStep(placeTube2Step);
    addStep(releaseTube2Step);
    addStep(retreat2Step);
#endif

    WsAutoNStepBase::WsAutoNStepCmdT shortCircuitStep;
    shortCircuitStep.driveType = AUTO_DRIVE_ENCODER;
    shortCircuitStep.throttle = -.3;
    shortCircuitStep.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    shortCircuitStep.driveEncoderDist = -100;
    shortCircuitStep.wheel = 0;
    shortCircuitStep.driveTimeout = 5;
    shortCircuitStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    shortCircuitStep.waitForLarm = true;
    shortCircuitStep.larmPosition = WsLarm::POSITION_NONE;
    shortCircuitStep.rollerClawSpeed = WsRollerClaw::ROLLER_OUT;
    shortCircuitStep.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;

    setShortCircuit(14.7, shortCircuitStep);


}
