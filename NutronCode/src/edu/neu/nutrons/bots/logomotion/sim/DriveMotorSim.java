/*
 * This is a simple sim of a drive motor
 */
package edu.neu.nutrons.bots.logomotion.sim;

import edu.neu.nutrons.lib.MotorMechanism;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class DriveMotorSim implements MotorMechanism {

    double pos = 0;
    double speed = 0;

    public void set(double speed) {
        this.speed = speed;
    }

    public double getPos() {
        pos += speed;
        return pos;
    }

    public double getRate() {
        return speed;
    }

    public boolean getUpperLimit() {
        return false;
    }

    public boolean getLowerLimit() {
        return false;
    }

    public void setInvertedSensor(boolean inverted) {
    }
}
