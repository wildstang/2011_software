/*
 * Block for an amount of time
 */
package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.lib.AutoModeCommand;
import edu.wpi.first.wpilibj.Timer;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class WaitCommand implements AutoModeCommand {

    Timer t = new Timer();
    boolean first = true;
    double timeToWait = 0;

    public WaitCommand(double timeInSeconds) {
        timeToWait = timeInSeconds;
    }

    public boolean doWork() {
        return t.get() >= timeToWait;
    }

    public void init() {
        // Do something?
        t.start();
    }

    public void finish() {
        // Do something?
    }
}
