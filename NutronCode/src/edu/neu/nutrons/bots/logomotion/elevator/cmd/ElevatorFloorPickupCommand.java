/*
 * ElevatorFloorPickupCommand
 *
 * This command causes the elevator to go pick up a tube
 */

package edu.neu.nutrons.bots.logomotion.elevator.cmd;

import edu.neu.nutrons.bots.logomotion.elevator.Elevator;
import edu.wpi.first.wpilibj.Timer;

/**
 *
 * @author Tom
 */
public class ElevatorFloorPickupCommand extends ElevatorCommand {

    Timer mTimer = new Timer();
    boolean firstRun = true;
    final double WRIST_DELAY = .125;
    public ElevatorFloorPickupCommand(){
        super(Elevator.HEIGHT_FLOOR,  true, true);
        mTimer.start();
    }


    public boolean getWrist() {
        if(firstRun) {
            firstRun = false;
            mTimer.start();
        }
        if(mTimer.get() >= WRIST_DELAY){
            return true;
        }
        return false;
    }

    public boolean getMiniwrist() {
        return true;
    }
}
