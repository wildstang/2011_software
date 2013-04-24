/*
 * Stop picking up off the floor
 */

package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.bots.logomotion.elevator.ElevatorController;
import edu.neu.nutrons.lib.AutoModeCommand;

/**
 *
 * @author ziv
 */
public class SignalElevatorEndFloorCommand implements AutoModeCommand {
    public boolean doWork() {
        ElevatorController.getInstance().stopFloor();
        return true;
    }

    public void init() {
    }

    public void finish() {
    }
}
