/*
 * Release the tube as quick as possible
 */

package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.bots.logomotion.elevator.ElevatorController;
import edu.neu.nutrons.lib.AutoModeCommand;

/**
 *
 * @author Tom
 */
public class ReleaseTubeCommand implements AutoModeCommand {
public boolean doWork() {
        ElevatorController.getInstance().quickReleaseTube();
        return true;
    }

    public void init() {
    }

    public void finish() {
    }
}
