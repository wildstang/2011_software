/*
 * Ask for the elevator to go to a position. Dont block.
 */
package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.bots.logomotion.elevator.ElevatorController;
import edu.neu.nutrons.lib.AutoModeCommand;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class SignalElevatorPosCommand implements AutoModeCommand {

    double wantedPos = 0;

    public SignalElevatorPosCommand(double pos) {
        wantedPos = pos;
    }

    public boolean doWork() {
        ElevatorController.getInstance().gotoScoringPosition(wantedPos);
        return true;
    }

    public void init() {
        // Init code for this command goes here!
    }

    public void finish() {
        // Clean up goes here!
    }
}
