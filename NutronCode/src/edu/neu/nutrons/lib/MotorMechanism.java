/*
 * MotorMechanism
 *
 * This interface is used to define mechanisms on the robot that have a motor
 * hooked up to some kind of feedback. Using this abstraction allows for sweeping
 * changes in the low level that dont affect control logic, like a simulator
 */

package edu.neu.nutrons.lib;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public interface MotorMechanism {
    public void set(double speed);
    public double getPos();
    public double getRate();
    public boolean getUpperLimit();
    public boolean getLowerLimit();
    public void setInvertedSensor(boolean inverted);
}
