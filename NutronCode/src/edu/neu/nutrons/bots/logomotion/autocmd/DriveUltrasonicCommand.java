/*
 *Drive until an ultrasonic threshold
 */

package edu.neu.nutrons.bots.logomotion.autocmd;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class DriveUltrasonicCommand extends DriveDistanceCommand {

    double USDistance;

    DriveUltrasonicCommand(double ultrasonicDistance, double maxDriveDistance, double speed, double timeoutInSeconds) {
        super(maxDriveDistance, speed, timeoutInSeconds);
        USDistance = ultrasonicDistance;
    }

    public boolean doWork() {
        return super.doWork() || bot.dBase.getUltrasonic() < USDistance;
    }
}
