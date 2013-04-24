/*
 * This just makes the elevator hang out
 */
package edu.neu.nutrons.bots.logomotion.elevator.cmd;

/**
 *
 * @author Tom
 */
public class IdleElevatorCommand extends ElevatorCommand {

    public IdleElevatorCommand(boolean wrist, boolean miniWrist) {
        super(0, wrist, miniWrist);
        // I don't think we need this -Ziv
        // scoring = true;
    }

    public double calcSpeed(double realPos) {
        // To do: implement PID
        return 0;
    }
}
