/*
 * Tell the grabber to pick up off the ground
 */

package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.bots.logomotion.elevator.ElevatorController;
import edu.neu.nutrons.lib.AutoModeCommand;

/**
 *
 * @author ziv
 */
public class SignalElevatorStartFloorCommand implements AutoModeCommand {

    public boolean doWork() {
        ElevatorController.getInstance().doFloor();
        return true;
    }

    public void init() {
    }

    public void finish() {
    }


}
