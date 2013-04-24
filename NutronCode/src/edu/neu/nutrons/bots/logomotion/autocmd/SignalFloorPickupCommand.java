/*
 * Start a floor pickup
 */

package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.bots.logomotion.elevator.ElevatorController;
import edu.neu.nutrons.lib.AutoModeCommand;

/**
 *
 * @author Tom
 */
public class SignalFloorPickupCommand implements AutoModeCommand{

    public boolean doWork() {
        ElevatorController.getInstance().doFloor();
        return true;
    }

    public void init() {
    }

    public void finish() {
    }

}
