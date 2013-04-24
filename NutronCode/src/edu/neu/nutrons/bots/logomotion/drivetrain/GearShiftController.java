/*
 * Framework for automatic shifting. Never finished.
 */

package edu.neu.nutrons.bots.logomotion.drivetrain;

import edu.neu.nutrons.bots.logomotion.Robot;
import edu.wpi.first.wpilibj.Timer;

/**
 *
 * @author ziv
 */
public class GearShiftController {

    // 3/28/11: Structure is here to implement auto, but right now acts just like manual
    
    final int LOW_GEAR = 0;
    final int HIGH_GEAR = 1;
    private int state = 0;
    private boolean curGear = false;
    private boolean needTimerReset = true;
    Timer tSinceShift = new Timer();

    public void autoShift() {
        if(needTimerReset) {
                tSinceShift.stop();
                tSinceShift.reset();
                tSinceShift.start();
        }
        if(curGear) {
            if(shiftHighConditions()) {
                needTimerReset = true;
                Robot.getInstance().dBase.setHighGear();
                curGear = true;
            }
        }
        else {
            if(shiftLowConditions()) {
                needTimerReset = true;
                Robot.getInstance().dBase.setLowGear();
                curGear = false;
            }
        }
    }

    private boolean shiftHighConditions() {
        // Change to implement automatic shifting (3/28/11)
        // Probably better to use probes than to have over 9000 arguments
        return true;
    }

    private boolean shiftLowConditions() {
        // Change to implement automatic shifting (3/28/11)
        return false;
    }

    public void manShift(boolean highGear) {
        needTimerReset = true; // Manual stuff should be disregarded by auto
        curGear = highGear;
        if(curGear) {
            Robot.getInstance().dBase.setHighGear();
        }
        else {
            Robot.getInstance().dBase.setLowGear();
        }
    }
}
