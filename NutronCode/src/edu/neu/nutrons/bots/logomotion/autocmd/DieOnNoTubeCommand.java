/*
 * DieOnNoTubeCommand
 *
 * This is a simple way to block the execution of automnomous mode
 * if the tube is not in the claw.
 *
 * Useful for checking if the second tube was picked up.
 */

package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.bots.logomotion.Robot;
import edu.neu.nutrons.lib.AutoModeCommand;

/**
 *
 * @author Tom
 */
public class DieOnNoTubeCommand implements AutoModeCommand{

    public boolean doWork() {
        if(Robot.getInstance().elevController.hasTube()){
            return true;
        }
        return false;
    }

    public void init() {
    }

    public void finish() {
    }

}
