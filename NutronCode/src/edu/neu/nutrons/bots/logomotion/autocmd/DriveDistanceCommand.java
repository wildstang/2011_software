/*
 *  Drive Distance Command
 *
 * This command will cause the robot to drive a specific distance
 */
package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.wpi.first.wpilibj.Timer;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class DriveDistanceCommand extends DriveDistanceNoTimeoutCommand {

    double timeout = 0.0;
    Timer t = new Timer();

    public DriveDistanceCommand(double distance, double speed, double timeoutInSeconds) {
        super(distance, speed);
        timeout = timeoutInSeconds;
    }
    
    public DriveDistanceCommand(double distance, double speed) {
        super(distance, speed);
        timeout = 15.;
    }

    public void init() {
        super.init();
        t.start();

    }

    public boolean doWork() {
        return super.doWork() || t.get() > timeout;
    }
}
