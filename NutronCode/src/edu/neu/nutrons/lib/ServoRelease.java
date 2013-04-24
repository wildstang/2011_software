/*
 * ServoRelease
 *
 * This is a nice abstraction on a servo that allows for locking/unlocking ability
 */

package edu.neu.nutrons.lib;

import edu.wpi.first.wpilibj.Servo;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class ServoRelease {

    Servo servo;
    double lockedAngle;
    double unlockedAngle;
    boolean released = false;
    

    public ServoRelease(int channel, double lockedAngle, double unlockedAngle) {
        servo = new Servo(channel);
        this.lockedAngle = lockedAngle;
        this.unlockedAngle = unlockedAngle;
        servo.setAngle(lockedAngle);
    }

    private void set(boolean unlocked) {
        servo.setAngle(unlocked ? unlockedAngle : lockedAngle);
    }

    public void release() {
        set(true);
        released = true;
    }

    public boolean getState() {
        return released;
    }
}
