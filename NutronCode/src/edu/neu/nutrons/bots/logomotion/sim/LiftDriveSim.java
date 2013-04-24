/*
 *
 * Lift Drive Sim
 * 
 * This was a super basic simulator used to test elevator control logic
 * before it ever touched the robot.
 */
package edu.neu.nutrons.bots.logomotion.sim;

import edu.neu.nutrons.lib.MotorMechanism;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class LiftDriveSim implements MotorMechanism {

    double pos = 0;
    double speed = 0;
    private final double range = 1.0;
    private final double totalTravelTime = 2.5;
    private final double updateRate = 50.0;
    final double gain = (range / totalTravelTime) / updateRate;

    public void set(double speed) {
        this.speed = speed;
    }

    public double getPos() {
        pos += speed * gain;
        if(pos > 1.0) {
            pos = 1.0;
        }
        else if(pos < 0.0) {
            pos = 0.0;
        }
        return pos;
    }

    public double getRate() {
        return speed * updateRate * gain;
    }

    public boolean getUpperLimit() {
        return pos >= 1.0;
    }

    public boolean getLowerLimit() {
        return pos <= 0.0;
    }

    public void setInvertedSensor(boolean inverted) {
    }
}
