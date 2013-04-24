/*
 * This moves the elevator to a scoring position
 */
package edu.neu.nutrons.bots.logomotion.elevator.cmd;

import edu.neu.nutrons.bots.logomotion.elevator.Elevator;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class ElevatorScoringCommand extends ElevatorCommand {

    boolean offset = false;
    double basePos;
    private double adjustment = 0;

    public ElevatorScoringCommand(double pos,  boolean wrist, boolean miniwrist) {
        super(pos,wrist, miniwrist);
        scoring = true;
        basePos = pos;
    }

    public void doOffset() {
        if(!offset) {
            basePos += Elevator.OFFSET_AMT;
            pos = basePos + adjustment;
        }
        offset = true;
    }

    public void setAdjustment(double adjustment) {
        this.adjustment = adjustment;
        pos = basePos + this.adjustment;
    }
}
