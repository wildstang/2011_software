/*
 * Shift the drive gearbox to low gear.
 */
package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.bots.logomotion.Robot;
import edu.neu.nutrons.lib.AutoModeCommand;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class ShiftLowCommand implements AutoModeCommand {

    public boolean doWork() {
        Robot.getInstance().dBase.setLowGear();
        return true;
    }

    public void init() {
    }

    public void finish() {
    }
}
