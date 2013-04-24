/*
 * ElevatorController
 *
 * This class handles all of the control logic for the elevator
 */
package edu.neu.nutrons.bots.logomotion.elevator;

import edu.wpi.first.wpilibj.*;
import edu.neu.nutrons.bots.logomotion.elevator.cmd.*;

public class ElevatorController {

    static ElevatorController inst = null;
    final int IDLE = 0;
    final int SCORING = 1;
    final int CAPPING = 2;
    final int FLOOR = 3;
    final int HOLD = 4;
    final int FLOOR_DONE = 5;
    final int MANUAL = 6;
    final int HUMAN = 7;
    final int HUMAN_DONE = 8;
    int state = IDLE;
    Timer sTimer = new Timer();
    boolean resetTimer = true;
    boolean firstRun = false;
    boolean doScoring = false;
    boolean capTube = false;
    // control bits
    boolean stopFloor = false;
    boolean stopMoving = false;
    boolean continueManual = false;
    double scorePos = 0.0;
    double manualClaw = 0;

    Elevator elev = Elevator.getInstance();
    RollerClaw claw = Elevator.getInstance().claw;
    ElevatorManualCommand manualCmd = new ElevatorManualCommand();

    private boolean stopHuman = false;

    public static ElevatorController getInstance() {
        if(inst == null) {
            inst = new ElevatorController();
        }
        return inst;
    }

    public void handle() {
        int nextState = state;
        ElevatorCommand nc = null;

        if(resetTimer) {
            resetTimer = false;
            firstRun = true;
            sTimer.stop();
            sTimer.reset();
            sTimer.start();
        }

        switch(state) {
            case IDLE:
                nc = new IdleElevatorCommand(elev.getWrist(), elev.getMiniwrist());
                break;

            case SCORING:
                if(firstRun) {
                    nc = new ElevatorScoringCommand(scorePos, false, false);
                }

                if(!doScoring) {
                    nextState = HOLD;
                }

                if(sTimer.get() > 10) {
                    nextState = IDLE;
                }
                break;

            case CAPPING:
                if(firstRun) {
                    nc = new ElevatorSlowCommand(elev.getPos() - Elevator.SCORING_DROP, false, false, Elevator.CAP_SPEED);
                    claw.scoreTube();
                }
                if(sTimer.get() > 10) {
                    nextState = IDLE;
                }

                break;

            case FLOOR:
                if(firstRun) {
                    nc = new ElevatorFloorPickupCommand();
                    claw.aquireTube();
                }

                if(claw.hasTube()){
                    nextState = FLOOR_DONE;
                }

                if(stopFloor) {
                    nextState = FLOOR_DONE;
                }
               
                break;

            case FLOOR_DONE:
               
                nc = new ElevatorCommand(elev.getPos(), false, false);
                claw.stopAquiringTube(); // stop sucking in if you dont already have it!
                nextState = IDLE;
                break;

            case HOLD:
                if(firstRun) {
                    nc = new IdleElevatorCommand(elev.getWrist(), elev.getMiniwrist());
                }
                nextState = IDLE;
                break;

            case MANUAL:
                nc = manualCmd;
                if(!continueManual) {
                    nextState = IDLE;
                    manualCmd.setWrist(false);
                    manualCmd.setMiniwrist(false);
                    manualClaw = 0;
                }
                if(manualClaw != 0){
                    claw.manualDrive(manualClaw);
                }
                continueManual = false;

                break;

            case HUMAN:
                if(firstRun) {
                    nc = new ElevatorCommand(Elevator.HEIGHT_HUMAN, true, true);
                    claw.aquireTube();
                }
                else if(stopHuman) {
                    nextState = HUMAN_DONE;
                }
                break;

            case HUMAN_DONE:
                stopHuman = false;
                if(firstRun) {
                    claw.stopAquiringTube();
                    nc = new ElevatorCommand(Elevator.HEIGHT_HUMAN, true, true);
                }
                break;

            default:
                nextState = IDLE;

        }

        firstRun = false;
        stopFloor = false;

        // Tube capping should work from anything
        if(capTube) {
            nextState = CAPPING;
            capTube = false;
        }

        // Reset stuff when a new state is transitioned to
        if(nextState != state) {
            setState(nextState);
        }

        // Set a new command if needed
        if(nc != null) {
            elev.setCommand(nc);
        }

       claw.handle();

        SmartDashboard.log(state, "ElevController State");

    }

    public void doFloor() {
        setState(FLOOR);

    }

    public void stopFloor() {
        stopFloor = true;
    }

    public void doHuman() {
        setState(HUMAN);

    }

    public void stopHuman() {
        stopHuman = true;
    }

    public void gotoScoringPosition(double scoringPos) {
        forceSetState(SCORING);
        scorePos = scoringPos;
        doScoring = true;
    }

    public void stopScoringPosition() {
        doScoring = false;
    }

    public void doOffset() {
        elev.doOffset();
    }

    public void setAdjustment(double adjustment) {
        elev.setAdjustment(adjustment);
    }

    public void cap() {
        capTube = true;
    }

    public void goIdle() {
        setState(IDLE);
    }

    public void quickReleaseTube(){
        claw.releaseTube();
    }

    public void doManual(double throttle, double clawSpeed, boolean wrist, boolean miniwrist) {
        manualCmd.setSpeed(throttle);
        manualClaw = clawSpeed;
        manualCmd.setWrist(wrist);
        manualCmd.setMiniwrist(miniwrist);
        continueManual = true;
        setState(MANUAL);
    }

    private void setState(int newState) {
        if(state != newState) {
            resetTimer = true;
        }
        state = newState;

    }

    private void forceSetState(int newState) {
        resetTimer = true;
        state = newState;
    }

    public boolean hasTube(){
        return claw.hasTube();
    }
}
