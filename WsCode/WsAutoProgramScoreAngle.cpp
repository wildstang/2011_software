#include "WsAutoProgramScoreAngle.h"
#include "WsPid.h"

WsAutoProgramScoreAngle::WsAutoProgramScoreAngle()
{
    if(ap_calib->isCompetitionRobot() == true)
    {
        ap_driveLowPID = new WsPid(.003, .0008, 0, 35, 35); // LOW GEAR
        ap_driveLowPID->setMinDoneCycles(3);

        ap_driveHighPID = new WsPid(.0010, .0035, .035, 35, 35); // HIGH GEAR
        ap_driveHighPID->setMinDoneCycles(1);
        
        ap_rotatePID = new WsPid(.000055,
                                 .000045,
                                 .000000, 1000 * 5, 1000 * 5); // HIGH GEAR
        /*
        ap_rotatePID = new WsPid(.0000134,
                                 .000050,
                                 .000008, 1000 * 3, 1000 * 3); // LOW GEAR
                                 */
        ap_rotatePID->setMinDoneCycles(5);
    }
    else
    {
        ap_driveLowPID = new WsPid(.0022, .0005, 0, 35, 35); // LOW GEAR
        ap_driveLowPID->setMinDoneCycles(5);

        ap_driveHighPID = new WsPid(.0010, .0035, .035, 35, 35); // HIGH GEAR
        ap_driveHighPID->setMinDoneCycles(1);
        
        ap_rotatePID = new WsPid(.000055,
                                 .000045,
                                 .000000, 1000 * 5, 1000 * 5); // HIGH GEAR
        /*
        ap_rotatePID = new WsPid(.0000134,
                                 .000050,
                                 .000008, 1000 * 3, 1000 * 3); // LOW GEAR
                                 */
        ap_rotatePID->setMinDoneCycles(5);
    }
}

WsAutoProgramScoreAngle::~WsAutoProgramScoreAngle()
{
    delete ap_driveLowPID;
    ap_driveLowPID = NULL;
    
    delete ap_driveHighPID;
    ap_driveHighPID = NULL;
    
    delete ap_rotatePID;
    ap_rotatePID = NULL;
}

void WsAutoProgramScoreAngle::initParams(void)
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

    INT32 driveAndRaiseDist = 0;


    printf("START %s %s %s - ",
            a_rackPosition == RACK_LEFT ? "L" : "R",
            a_colPosition == COL_LEFT ? "L" : a_colPosition == COL_MID ? "M" : "R",
            a_pegHeight == PEG_MID ? "M" : "H");


    if(a_rackPosition == RACK_LEFT)
    {
        switch(a_colPosition)
        {
            case COL_LEFT:
                driveAndRaiseDist = 1630;
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
                // INVALID
                validProgram = false;
                break;
            case COL_RIGHT:
                driveAndRaiseDist = 1530;
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
                // INVALID
                validProgram = false;
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
    testStep.throttle = 1;
    testStep.wheel = 0;
    testStep.shifter = WsDriveBase6WD::SHIFT_STATE_LOW;
    testStep.driveTimeout = 5;
    testStep.driveEncoderDist = 1500;
    testStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    testStep.drivePid = ap_driveLowPID;
    testStep.rotateAngle = 0;
    testStep.larmPosition = WsLarm::POSITION_NONE;
    testStep.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    testStep.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;
    
    testStopStep.driveType = AUTO_DRIVE_TIME;
    testStopStep.throttle = 1;
    testStopStep.wheel = 0;
    testStopStep.shifter = WsDriveBase6WD::SHIFT_STATE_LOW;
    testStopStep.driveTimeout = .1;
    testStopStep.driveEncoderDist = 0;
    testStopStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    testStopStep.drivePid = NULL;
    testStopStep.rotateAngle = 0;
    testStopStep.larmPosition = WsLarm::POSITION_NONE;
    testStopStep.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    testStopStep.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;

    initialDriveStep.driveType = AUTO_DRIVE_ENCODER;
    initialDriveStep.throttle = .8;
    initialDriveStep.wheel = 0;
    initialDriveStep.shifter = WsDriveBase6WD::SHIFT_STATE_LOW;
    initialDriveStep.driveTimeout = 5;
    initialDriveStep.driveEncoderDist = 875;
    initialDriveStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    //initialDriveStep.drivePid = ap_testDrivePID;
    //initialDriveStep.rotateAngle = 0;
    initialDriveStep.larmPosition = larmPlaceTubePosition;
    initialDriveStep.waitForLarm = false;
    initialDriveStep.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    initialDriveStep.rollerClawRelease = WsRollerClaw::CLAW_CLOSE;

    driveAndRaiseStep.driveType = AUTO_DRIVE_DIST_PID;
    driveAndRaiseStep.throttle = .6;
    driveAndRaiseStep.wheel = 0;
    driveAndRaiseStep.shifter = WsDriveBase6WD::SHIFT_STATE_LOW;
    driveAndRaiseStep.driveTimeout = 6;
    driveAndRaiseStep.driveEncoderDist = driveAndRaiseDist;
    driveAndRaiseStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    driveAndRaiseStep.drivePid = ap_driveLowPID;
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
    placeTubeStep.throttle = -.3;
    placeTubeStep.wheel = 0;
    placeTubeStep.shifter = WsDriveBase6WD::SHIFT_STATE_LOW;
    placeTubeStep.driveTimeout = 4;
    placeTubeStep.driveEncoderDist = -100; // Causes us to pass drive immediately
    placeTubeStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    placeTubeStep.drivePid = ap_driveLowPID;
    //placeTubeStep.rotateAngle = 0;
    placeTubeStep.larmPosition = larmReleaseTubePosition;
    placeTubeStep.waitForLarm = false;
    placeTubeStep.rollerClawSpeed = WsRollerClaw::ROLLER_OUT_SLOW;
    placeTubeStep.rollerClawRelease = WsRollerClaw::CLAW_OPEN;

    releaseTubeStep.driveType = AUTO_DRIVE_ENCODER;
    releaseTubeStep.throttle = -.7;
    releaseTubeStep.wheel = 0;
    releaseTubeStep.shifter = WsDriveBase6WD::SHIFT_STATE_LOW;
    releaseTubeStep.driveTimeout = 4;
    releaseTubeStep.driveEncoderDist = -300;
    releaseTubeStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    //releaseTubeStep.drivePid = ap_driveLowPID;
    //releaseTubeStep.rotateAngle = 0;
    releaseTubeStep.larmPosition = WsLarm::POSITION_HOME;
    releaseTubeStep.waitForLarm = false;
    releaseTubeStep.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    releaseTubeStep.rollerClawRelease = WsRollerClaw::CLAW_OPEN;

    retreatStep.driveType = AUTO_DRIVE_ENCODER;
    retreatStep.throttle = -.5;
    retreatStep.wheel = 0;
    retreatStep.shifter = WsDriveBase6WD::SHIFT_STATE_LOW;
    retreatStep.driveTimeout = 5;
    retreatStep.driveEncoderDist = -600;
    retreatStep.driveEncoderLoc = WsDriveBase6WD::ENC_LOC_R;
    //retreat.drivePid = ap_driveLowPID;
    //retreatStep.rotateAngle = 0;
    retreatStep.larmPosition = WsLarm::POSITION_HOME;
    retreatStep.rollerClawSpeed = WsRollerClaw::ROLLER_OFF;
    retreatStep.rollerClawRelease = WsRollerClaw::CLAW_OPEN;

    //addStep(testStep);
    //addStep(testStopStep);
    addStep(initialDriveStep);
    addStep(driveAndRaiseStep);
    //addStep(stopAtPegStep);
    addStep(placeTubeStep);
    addStep(releaseTubeStep);
    addStep(retreatStep);
    /*
    */

}
