/*
 * Elevator Manual command
 *
 * This command can be processed by the elevator but also has external hooks
 * for a manual drive
 */
package edu.neu.nutrons.bots.logomotion.elevator.cmd;

import edu.neu.nutrons.lib.Helpers;

/**
 *
 * @author Tom
 */
public class ElevatorManualCommand extends ElevatorCommand {

    double speed;

    public ElevatorManualCommand() {
        super(0, false, false);
    }

    public double calcSpeed(double realPos) {
        return Helpers.limitAbs(speed);
    }

    public void setSpeed(double newSpeed) {
        speed = newSpeed;
    }


    public void setWrist(boolean newWrist) {
        wrist = newWrist;
    }

    public void setMiniwrist(boolean newMiniwrist) {
        miniwrist = newMiniwrist;
    }


}
