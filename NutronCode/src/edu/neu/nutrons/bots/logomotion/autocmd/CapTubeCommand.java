/*
 * Cap Tube Command
 *
 * This caps a tube. Duh, winning.
 */
package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.bots.logomotion.elevator.ElevatorController;
import edu.neu.nutrons.lib.AutoModeCommand;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class CapTubeCommand implements AutoModeCommand {

    public boolean doWork() {
        ElevatorController.getInstance().cap();
        return true;
    }

    public void init() {
    }

    public void finish() {
    }
}
