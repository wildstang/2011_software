/*
 * This is an elevator command that times out
 */
package edu.neu.nutrons.bots.logomotion.elevator.cmd;

import edu.wpi.first.wpilibj.Timer;

/**
 * stopTime is relative to when command is created and placed in queue
 *
 * @author NUTRONS_PROGRAMMING
 */
public class ElevatorWithTimeoutCommand extends ElevatorCommand {

    double stopTime;
    Timer timer;

    public ElevatorWithTimeoutCommand(double pos, boolean wrist, boolean miniwrist, double stopTime) {
        super(pos, wrist, miniwrist);
        timed = true;
        timer = new Timer();
        this.stopTime = stopTime;
        timer.start();
    }

    public boolean isDone() {
        if(timer.get() > stopTime) {
            return true;
        }
        else {
            return super.isDone();
        }
    }
}
