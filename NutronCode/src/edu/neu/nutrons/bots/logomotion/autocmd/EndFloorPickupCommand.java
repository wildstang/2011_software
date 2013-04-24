/*
 * End a floor pickup routine
 */

package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.bots.logomotion.elevator.ElevatorController;
import edu.neu.nutrons.lib.AutoModeCommand;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class EndFloorPickupCommand implements AutoModeCommand {

    public boolean doWork() {
        ElevatorController.getInstance().stopFloor();
        return true;
    }

    public void init() {
    }

    public void finish() {
    }

}
