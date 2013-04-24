/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.neu.nutrons.bots.logomotion.elevator;

import edu.neu.nutrons.lib.MotorMechanism;
import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.Jaguar;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class ElevatorMotorMechanism implements MotorMechanism {

    Jaguar motorA;
    Jaguar motorB;
    Encoder enc;
    final boolean invertedMotor = true;

    public ElevatorMotorMechanism(int jagAPort, int jagBPort, int encAPort, int encBPort) {
        motorA = new Jaguar(jagAPort);
        motorB = new Jaguar(jagBPort);
        enc = new Encoder(encAPort, encBPort, false, Encoder.EncodingType.k4X);
        enc.start();

    }

    public void set(double speed) {
        if(getUpperLimit() && speed > 0) {
            setMotors(0);
        }
        else if(getLowerLimit() && speed < 0) {
            setMotors(0);
        }
        else {
            setMotors(speed);
        }

    }

    public double getPos() {
        double ret = enc.get() / (12500. * 1.0);
        /*if( ret < 0){
            enc.reset();
            ret = 0;
        }
         * 
         */
        return ret;
    }

    public double getRate() {
        return 0;
    }

    public boolean getUpperLimit() {
        return false;// || getPos() >= 1.0;
    }

    public boolean getLowerLimit() {
        return false;// || getPos() <= 0.0;
    }

    public void setInvertedSensor(boolean inverted) {
        enc.setReverseDirection(inverted);
    }

    public void resetFB(){
        enc.reset();
    }

    private void setMotors(double speed) {
        if(invertedMotor) {
            speed = -speed;
        }
        motorA.set(speed);
        motorB.set(speed);
    }
}
