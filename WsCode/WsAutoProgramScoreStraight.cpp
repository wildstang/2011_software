#include "WsAutoProgramScoreStraight.h"
#include "WsPid.h"

#define USE_HIGH_GEAR 1


WsAutoProgramScoreStraight::WsAutoProgramScoreStraight()
{
    if(ap_calib->isCompetitionRobot() == true)
    {
        ap_driveLowPID = new WsPid(.003, .0008, 0, 35, 35); // LOW GEAR
        ap_driveLowPID->setMinDoneCycles(3);

        ap_driveHighPID = new WsPid(.0125, .005, .13, 5, 5); // HIGH GEAR
        ap_driveHighPID->setIntegralErrorThresh(20);
        ap_driveHighPID->setMinDoneCycles(10);

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
    else
    {
        ap_driveLowPID = new WsPid(.0022, .0005, 0, 35, 35); // LOW GEAR
        ap_driveLowPID->setMinDoneCycles(5);

        ap_driveHighPID = new WsPid(.0125, .005, .13, 5, 5); // HIGH GEAR
        ap_driveHighPID->setIntegralErrorThresh(20);
        ap_driveHighPID->setMinDoneCycles(10);

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

WsAutoProgramScoreStraight::~WsAutoProgramScoreStraight()
{
    delete ap_driveLowPID;
    ap_driveLowPID = NULL;
    
    delete ap_driveHighPID;
    ap_driveHighPID = NULL;
    
    delete ap_rotatePID;
    ap_rotatePID = NULL;
}

void WsAutoProgramScoreStraight::initParams(void)
{
    bool validProgram = true;
    WsAutoNStepBase::WsAutoNStepCmdT testStep;
    WsAutoNStepBase::WsAutoNStepCmdT testStopStep;
    WsAutoNStepBase::WsAutoNStepCmdT initialDriveStep;
    WsAutoNStepBase::WsAutoNStepCmdT driveAndRaiseStep;
    WsAutoNStepBase::WsAutoNStepCmdT stopAtPegStep;
    WsAutoNStepBase::WsAutoNStepCmdT placeTubeStep;
    WsAutoNStepBase::WsAutoNStepCmdT releaseTubeStep;
    WsAutoNStepBase::WsAutoNStepCmdT retreatStep;

    WsAutoNStepBase::initParams();

    WsLarm::PositionT larmPlaceTubePosition = WsLarm::POSITION_NONE;
    WsLarm::PositionT larmReleaseTubePosition = WsLarm::POSITION_NONE;
    WsLarm::PositionT larmRetreatPosition = WsLarm::POSITION_NONE;
    printf("START %s %s %s - ",
            a_rackPosition == RACK_LEFT ? "L" : "R",
            a_colPosition == COL_LEFT ? "L" : a_colPosition == COL_MID ? "M" : "R",
            a_pegHeight == PEG_MID ? "M" : "H");


    if(a_rackPosition == RACK_LEFT)
    {
        switch(a_colPosition)
        {
            case COL_LEFT:
                // INVALID
                validProgram = false;
                break;
            case COL_MID:
                switch(a_pegHeight)
                {
                    case PEG_LOW:
                        larmPlaceTubePosition = WsLarm::POSITION_SCORE_LOW2;
                        larmReleaseTubePosition = WsLarm::POSITION_RELEASE_LOW2;
                        larmRetreatPosition = WsLarm::POSITION_HOME;
                        break;
                    case PEG_MID:
                        larmPlaceTubePosition = WsLarm::POSITION_SCORE_MID2;
                        larmReleaseTubePosition = WsLarm::POSITION_RELEASE_MID2;
                        larmRetreatPosition = WsLarm::POSITION_HOME;
                        break;
                    case PEG_HIGH:
                        larmPlaceTubePosition = WsLarm::POSITION_SCORE_HIGH2;
                        larmReleaseTubePosition = WsLarm::POSITION_RELEASE_HIGH2;
                        larmRetreatPosition = WsLarm::POSITION_HOME;
                        break;
                    default:
                        break;
                }
                break;
            case COL_RIGHT:
                switch(a_pegHeight)
                {
                    case PEG_LOW:
                        larmPlaceTubePosition = WsLarm::POSITION_SCORE_LOW1;
                        larmReleaseTubePosition = WsLarm::POSITION_RELEASE_LOW1;
                        larmRetreatPosition = WsLarm::POSITION_HOME;
                        break;
                    case PEG_MID:
                        larmPlaceTubePosition = WsLarm::POSITION_SCORE_MID1;
                        larmReleaseTubePosition = WsLarm::POSITION_RELEASE_MID1;
                        larmRetreatPosition = WsLarm::POSITION_HOME;
                        break;
                    case PEG_HIGH:
                        larmPlaceTubePosition = WsLarm::POSITION_SCORE_HIGH1;
                        larmReleaseTubePosition = WsLarm::POSITION_RELEASE_HIGH1;
                        larmRetreatPosition = WsLarm::POSITION_HOME;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    else
    {
        switch(a_colPosition)
        {
            case COL_LEFT:
                switch(a_pegHeight)
                {
                    case PEG_LOW:
                        larmPlaceTubePosition = WsLarm::POSITION_SCORE_LOW1;
                        larmReleaseTubePosition = WsLarm::POSITION_RELEASE_LOW1;
                        larmRetreatPosition = WsLarm::POSITION_HOME;
                        break;
                    case PEG_MID:
                        larmPlaceTubePosition = WsLarm::POSITION_SCORE_MID1;
                        larmReleaseTubePosition = WsLarm::POSITION_RELEASE_MID1;
                        larmRetreatPosition = WsLarm::POSITION_HOME;
                        break;
                    case PEG_HIGH:
                        larmPlaceTubePosition = WsLarm::POSITION_SCORE_HIGH1;
                        larmReleaseTubePosition = WsLarm::POSITION_RELEASE_HIGH1;
                        larmRetreatPosition = WsLarm::POSITION_HOME;
                        break;
                    default:
                        break;
                }
                break;
            case COL_MID:
                switch(a_pegHeight)
                {
                    case PEG_LOW:
                        larmPlaceTubePosition = WsLarm::POSITION_SCORE_LOW2;
                        larmReleaseTubePosition = WsLarm::POSITION_RELEASE_LOW2;
                        larmRetreatPosition = WsLarm::POSITION_HOME;
                        break;
                    case PEG_MID:
                        larmPlaceTubePosition = WsLarm::POSITION_SCORE_MID2;
                        larmReleaseTubePosition = WsLarm::POSITION_RELEASE_MID2;
                        larmRetreatPosition = WsLarm::POSITION_HOME;
                        break;
                    case PEG_HIGH:
                        larmPlaceTubePosition = WsLarm::POSITION_SCORE_HIGH2;
                        larmReleaseTubePosition = WsLarm::POSITION_RELEASE_HIGH2;
                        larmRetreatPosition = WsLarm::POSITION_HOME;
                        break;
                    default:
                        break;
                }
                break;
            case COL_RIGHT:
                // INVALID
                validProgram = false;
                break;
            default:
                break;
        }
    }

    if(validProgram == false)
    {
        printf("INVALID PROGRAM\n");
        return;
    }


    printf("PLACE POS %d\n", larmPlaceTubePosition);
    testStep.driveType = AUTO_DRIVE_DIST_PID;
    testStep.throttle = .75;
    testStep.wheel = 0;
    testStep.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    testStep.driveTimeout = 7;
    testStep.driveEncoderDist = 2000;
    testStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    testStep.drivePid = ap_driveHighPID;
    //testStep.rotateAngle = 180;
    testStep.larmPosition = WsLarm::POSITION_NONE;
    testStep.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    testStep.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;
    
    testStopStep.driveType = AUTO_DRIVE_TIME;
    testStopStep.throttle = -1;
    testStopStep.wheel = 0;
    testStopStep.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    testStopStep.driveTimeout = .2;
    testStopStep.driveEncoderDist = 0;
    testStopStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    testStopStep.drivePid = NULL;
    testStopStep.rotateAngle = 0;
    testStopStep.larmPosition = WsLarm::POSITION_NONE;
    testStopStep.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    testStopStep.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;



    initialDriveStep.driveType = AUTO_DRIVE_ENCODER;
#if USE_HIGH_GEAR
    //initialDriveStep.throttle = .6;
    initialDriveStep.throttle = .7;
    initialDriveStep.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    initialDriveStep.driveEncoderDist = 175;
#else
    initialDriveStep.throttle = .8;
    initialDriveStep.shifter = WsDriveBase6WD::SHIFT_STATE_LOW;
    initialDriveStep.driveEncoderDist = 875;
#endif
    initialDriveStep.wheel = 0;
    initialDriveStep.driveTimeout = 5;
    initialDriveStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    //initialDriveStep.drivePid = ap_testDrivePID;
    //initialDriveStep.rotateAngle = 0;
    initialDriveStep.larmPosition = larmPlaceTubePosition;
    initialDriveStep.waitForLarm = false;
    initialDriveStep.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    initialDriveStep.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;

    driveAndRaiseStep.driveType = AUTO_DRIVE_DIST_PID_SHORT_CIRCUIT;
#if USE_HIGH_GEAR
    //driveAndRaiseStep.throttle = .3;
    driveAndRaiseStep.throttle = .35;
    driveAndRaiseStep.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    driveAndRaiseStep.drivePid = ap_driveHighPID;
    //driveAndRaiseStep.driveEncoderDist = 2190; // PROTO VALUE
    //driveAndRaiseStep.driveEncoderDist = 2340;
    driveAndRaiseStep.driveEncoderDist = 2200;
#else
    driveAndRaiseStep.throttle = .6;
    driveAndRaiseStep.shifter = WsDriveBase6WD::SHIFT_STATE_LOW;
    driveAndRaiseStep.drivePid = ap_driveLowPID;
    driveAndRaiseStep.driveEncoderDist = 1490;
#endif
    driveAndRaiseStep.wheel = 0;
    driveAndRaiseStep.driveTimeout = 6;
    //driveAndRaiseStep.driveEncoderDist = 1700;
    driveAndRaiseStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;

    //driveAndRaiseStep.rotateAngle = 0;
    driveAndRaiseStep.waitForLarm = false;
    driveAndRaiseStep.larmPosition = larmPlaceTubePosition;
    driveAndRaiseStep.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    driveAndRaiseStep.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;
    
    stopAtPegStep.driveType = AUTO_DRIVE_TIME;
    stopAtPegStep.throttle = -.75;
    stopAtPegStep.wheel = 0;
    stopAtPegStep.shifter = WsDriveBase6WD::SHIFT_STATE_LOW;
    stopAtPegStep.driveTimeout = .2;
    //stopAtPegStep.driveEncoderDist = 1700;
    //stopAtPegStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    //stopAtPegStep.drivePid = ap_driveLowPID;
    //stopAtPegStep.rotateAngle = 0;
    stopAtPegStep.waitForLarm = true;
    stopAtPegStep.larmPosition = larmPlaceTubePosition;
    stopAtPegStep.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    stopAtPegStep.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;

    placeTubeStep.driveType = AUTO_DRIVE_ENCODER;
    placeTubeStep.wheel = 0;
#if USE_HIGH_GEAR
    placeTubeStep.throttle = -.2;
    placeTubeStep.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    placeTubeStep.drivePid = ap_driveHighPID;
    placeTubeStep.driveEncoderDist = -50;
#else
    placeTubeStep.throttle = -.3;
    placeTubeStep.shifter = WsDriveBase6WD::SHIFT_STATE_LOW;
    placeTubeStep.drivePid = ap_driveLowPID;
    placeTubeStep.driveEncoderDist = -100;
#endif
    placeTubeStep.driveTimeout = 4;
    placeTubeStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    //placeTubeStep.rotateAngle = 0;
    placeTubeStep.larmPosition = larmReleaseTubePosition;
    placeTubeStep.waitForLarm = false; // change to true if we drop too soon
    placeTubeStep.rollerClawSpeed = WsRollerClaw::ROLLER_OUT_SLOW;
    placeTubeStep.rollerClawRelease = WsRollerClaw::CLAW_OPEN;

    releaseTubeStep.driveType = AUTO_DRIVE_ENCODER;
#if USE_HIGH_GEAR
    releaseTubeStep.throttle = -.5;
    releaseTubeStep.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    releaseTubeStep.larmPosition = larmReleaseTubePosition;
    releaseTubeStep.driveEncoderDist = -300;
#else
    releaseTubeStep.throttle = -.7;
    releaseTubeStep.shifter = WsDriveBase6WD::SHIFT_STATE_LOW;
    releaseTubeStep.larmPosition = WsLarm::POSITION_HOME;
    releaseTubeStep.driveEncoderDist = -300;
#endif
    releaseTubeStep.wheel = 0;
    releaseTubeStep.driveTimeout = 4;
    releaseTubeStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    //releaseTubeStep.drivePid = ap_driveLowPID;
    //releaseTubeStep.rotateAngle = 0;
    releaseTubeStep.waitForLarm = false;
    releaseTubeStep.rollerClawSpeed = WsRollerClaw::ROLLER_OUT_SLOW;
    releaseTubeStep.rollerClawRelease = WsRollerClaw::CLAW_OPEN;

    retreatStep.driveType = AUTO_DRIVE_ENCODER;
#if USE_HIGH_GEAR
    retreatStep.throttle = -.5;
    retreatStep.shifter = WsDriveBase6WD::SHIFT_STATE_HIGH;
    retreatStep.driveEncoderDist = -300;
#else
    retreatStep.throttle = -.5;
    retreatStep.shifter = WsDriveBase6WD::SHIFT_STATE_LOW;
    retreatStep.driveEncoderDist = -900;
#endif
    retreatStep.wheel = 0;
    retreatStep.driveTimeout = 5;
    retreatStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    //retreat.drivePid = ap_driveLowPID;
    //retreatStep.rotateAngle = 0;
    retreatStep.waitForLarm = true;
    retreatStep.larmPosition = WsLarm::POSITION_HOME;
    retreatStep.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    retreatStep.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;

    /*
    addStep(testStep);
    addStep(testStopStep);
    */
    addStep(initialDriveStep);
    addStep(driveAndRaiseStep);
    addStep(placeTubeStep);
    addStep(releaseTubeStep);
    addStep(retreatStep);

}
