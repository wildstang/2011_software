/*
 * This moves the Elevator, but more slow like
 */

package edu.neu.nutrons.bots.logomotion.elevator.cmd;

import edu.neu.nutrons.lib.Helpers;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class ElevatorSlowCommand extends ElevatorCommand {

    double maxSpeed;

    public ElevatorSlowCommand(double pos, boolean wrist, boolean miniwrist, double maxSpeed) {
        super(pos, wrist, miniwrist);
        this.maxSpeed = maxSpeed;
    }

    public double calcSpeed(double realPos) {
        return Helpers.limitAbs(super.calcSpeed(realPos), maxSpeed);
    }
}
