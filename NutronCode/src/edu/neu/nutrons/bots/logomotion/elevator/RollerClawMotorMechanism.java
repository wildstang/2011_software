/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package edu.neu.nutrons.bots.logomotion.elevator;

import edu.neu.nutrons.lib.MotorMechanism;
import edu.wpi.first.wpilibj.*;

/**
 *
 * @author ziv
 */
public class RollerClawMotorMechanism implements MotorMechanism {

    // Basically just a speed controller wrapper, seeing as we won't use encoders probably
    Victor motor;

    public RollerClawMotorMechanism(int vicPort) {
        motor = new Victor(vicPort);
    }

    public void set(double speed) {
        motor.set(speed);
    }

    public double getPos() {
        return 0;
    }

    public double getRate() {
        return 0;
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
