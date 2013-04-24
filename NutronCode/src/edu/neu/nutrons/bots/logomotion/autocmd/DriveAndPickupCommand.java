/*
 * Drive and Pickup command
 *
 * This drives while the pickup mechanism is running
 */

package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.bots.logomotion.Robot;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class DriveAndPickupCommand extends DriveDistanceCommand {



    public void init(){
        Robot.getInstance().elevController.doFloor();
    }

    public DriveAndPickupCommand(double distance, double speed, double timeoutInSeconds) {
        super(distance, speed, timeoutInSeconds);
    }

    public void finish(){
        Robot.getInstance().elevController.stopFloor();
    }
}
