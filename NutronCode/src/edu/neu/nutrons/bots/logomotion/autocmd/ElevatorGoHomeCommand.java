/*
 * Send the elevator to its home position
 */
package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.lib.AutoModeCommand;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class ElevatorGoHomeCommand implements AutoModeCommand {

    public boolean doWork() {
        //  ElevatorController.getInstance().
        return true;
    }

    public void init() {
    }

    public void finish() {
    }
}
