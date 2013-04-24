/*
 * Jag Drive
 *
 * Drive With Jags
 */
package edu.neu.nutrons.bots.logomotion.drivetrain;

import edu.neu.nutrons.lib.MotorMechanism;
import edu.wpi.first.wpilibj.*;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class JagDrive implements MotorMechanism {

    Jaguar dA;
    Jaguar dB;
    Encoder enc;
    Timer timer = new Timer();
    double lastTime = 0;
    double lastPos = 0;

    public JagDrive(int portA, int portB, int encPortA, int encPortB) {
        dA = new Jaguar(portA);
        dB = new Jaguar(portB);
        enc = new Encoder(encPortA, encPortB);
        enc.start();
        timer.start();
    }

    public void set(double speed) {
        dA.set(speed);
        dB.set(speed);
    }

    public double getPos() {
        double ret = enc.get();
        ret *= (((4 * Math.PI) / 12) / 250); // ticks/s * feet/ticks = feet/s
        return ret;
    }

    public double getRate() {
        double curPos = this.getPos();
        double curTime = timer.get();
        double ret = (curPos - lastPos) / (curTime - lastTime);
        lastPos = curPos;
        lastTime = curTime;
        return ret;
    }

    public boolean getUpperLimit() {
        return false;
    }

    public boolean getLowerLimit() {
        return false;
    }

    public void setInvertedSensor(boolean inverted) {
        enc.setReverseDirection(inverted);
    }
}
