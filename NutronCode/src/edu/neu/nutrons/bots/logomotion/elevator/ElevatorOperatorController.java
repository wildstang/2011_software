/*
 * Elevator Operator Controller
 *
 * This class handles how a human operator can control the elevator
 */
package edu.neu.nutrons.bots.logomotion.elevator;

import edu.neu.nutrons.bots.logomotion.*;
import edu.neu.nutrons.lib.*;
import edu.wpi.first.wpilibj.SmartDashboard;

/**
 *
 * @author Tom
 */
public class ElevatorOperatorController {

    ControlMap cb;
    PulseTriggerBoolean capTrigger = new PulseTriggerBoolean();
    boolean floorWasPushed = false;
    ElevatorController ec = ElevatorController.getInstance();
    private boolean humanWasPushed = false;

    public ElevatorOperatorController(ControlMap cb) {
        this.cb = cb;
    }

    public void handle() {



        // Capping
        capTrigger.set(cb.getCapBtn());
        if(capTrigger.get()) {
            ec.cap();
        }

        // Floor pickup
        if(cb.getFloorBtn()) {
           if(!floorWasPushed) {
               ec.doFloor();
           }
            floorWasPushed = true;
        }
        else {
            if(floorWasPushed) {
                ec.stopFloor();
            }
            floorWasPushed = false;
        }

        // Human player pickup
        if(cb.getHumanBtn()) {
            ec.doHuman();
            humanWasPushed = true;
        }
        else {
            if(humanWasPushed) {
                ec.stopHuman();
            }
            humanWasPushed = false;
        }

        // Scoring position controls
        if(cb.getHighBtn()) {
            ec.gotoScoringPosition(Elevator.HEIGHT_HIGH);
            //System.out.println("high");
        }
        else if(cb.getMidBtn()) {
            ec.gotoScoringPosition(Elevator.HEIGHT_MID);

        }
        else if(cb.getLowBtn()) {
            ec.gotoScoringPosition(Elevator.HEIGHT_LOW);

        }
        else {
            // ec.stopScoringPosition();
        }

        // Only when state is scoring
        // Logic in ElevatorScoringCommand means it will only happen once
        if(cb.getShiftBtn()) {
            ec.doOffset();
        }

        // Only makes a difference when state is scoring
        ec.setAdjustment(cb.getElevatorAdjustment());

        SmartDashboard.log(cb.wantManualOveride(), "Manual OVerride?");
        // Manual override
       
        if(cb.wantManualOveride()) {
            ec.doManual((cb.getElevatorThrottle()), cb.getClawSpeed(), cb.getWrist(), cb.getMiniwrist());
        }

    }
}
