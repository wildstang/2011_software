/*
 * Drive until we pick up a tube
 */

package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.bots.logomotion.Robot;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class DriveUntilPickupCommand extends DriveDistanceCommand {

    public DriveUntilPickupCommand(double maxDistance, double speed, double timeoutInSeconds) {
        super(maxDistance, speed, timeoutInSeconds);
    }

    public boolean doWork() {
        return super.doWork() || Robot.getInstance().elev.claw.hasTube();
    }
}
