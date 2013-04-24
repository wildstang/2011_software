/*
 * Drive Distance Fast
 *
 * This drives in high gear. But, it takes a second to shift up as we get better
 * acceleration in low gear. Its what the driver would do, without a driver.
 */

package edu.neu.nutrons.bots.logomotion.autocmd;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class DriveDistanceFastAndCoastCommand extends DriveDistanceAndCoastCommand {
    boolean needToShift = false;
    static final double SHIFT_DELAY = 1.0;

    public DriveDistanceFastAndCoastCommand(double distance, double speed, double timeoutInSeconds) {
        super(distance, speed,timeoutInSeconds);
    }

    public boolean doWork() {
        if(needToShift && t.get() > SHIFT_DELAY) {
            bot.dBase.setHighGear();
            needToShift = false;
        }
        return super.doWork();
    }
}
