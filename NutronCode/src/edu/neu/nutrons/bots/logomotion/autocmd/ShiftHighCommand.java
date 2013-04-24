/*
 * Shift the drive gearbox to high gear
 */
package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.bots.logomotion.Robot;
import edu.neu.nutrons.lib.AutoModeCommand;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class ShiftHighCommand implements AutoModeCommand {

    public boolean doWork() {
        Robot.getInstance().dBase.setHighGear();
        return true;
    }

    public void init() {
    }

    public void finish() {
    }
}
