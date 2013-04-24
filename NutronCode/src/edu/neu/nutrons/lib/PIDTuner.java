/*
 * PID Tuner
 *
 * This allows PID gains to be tuned using a joystick
 */
package edu.neu.nutrons.lib;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.SmartDashboard;

/**
 *
 * @author Tom
 */
public class PIDTuner {

    public static PIDTuner inst = null;
    Joystick js = null;
    double kp, ki, kd;
    final double INCREMENT = .25;
    PulseTriggerBoolean pTrigUp = new PulseTriggerBoolean();
    PulseTriggerBoolean iTrigUp = new PulseTriggerBoolean();
    PulseTriggerBoolean dTrigUp = new PulseTriggerBoolean();
    PulseTriggerBoolean pTrigD = new PulseTriggerBoolean();
    PulseTriggerBoolean iTrigD = new PulseTriggerBoolean();
    PulseTriggerBoolean dTrigD = new PulseTriggerBoolean();

    private PIDTuner(int port) {
        js = new Joystick(port);
        kp = 20;
        ki = 0.8; // old elevator vals
        kd = 30;
    }

    public static PIDTuner getInstance() {
        if(inst == null) {
            inst = new PIDTuner(4);
        }
        return inst;
    }

    public void handle() {
        pTrigUp.set(js.getRawButton(4));
        pTrigD.set(js.getRawButton(5));
        iTrigUp.set(js.getRawButton(6));
        iTrigD.set(js.getRawButton(7));
        dTrigUp.set(js.getRawButton(11));
        dTrigD.set(js.getRawButton(10));

        if(pTrigUp.get()) {
            kp += INCREMENT;
        }
        else if(pTrigD.get()) {
            kp -= INCREMENT;
        }

        if(iTrigUp.get()) {
            ki += INCREMENT / 10;
        }
        else if(iTrigD.get()) {
            ki -= INCREMENT / 10;
        }

        if(dTrigUp.get()) {
            kd += INCREMENT * 2;
        }
        else if(dTrigD.get()) {
            kd -= INCREMENT * 2;
        }

        if(kp <= 0.0) {
            kp = 0;
        }
        if(ki <= 0.0) {
            ki = 0;
        }
        if(kd <= 0.0) {
            kd = 0;
        }

        SmartDashboard.log(kp, "PIDTuner kP");
        SmartDashboard.log(ki, "PIDTuner kI");
        SmartDashboard.log(kd, "PIDTuner kD");

    }

    public double getKP() {
        return kp;
    }

    public double getKI() {
        return ki;
    }

    public double getKD() {
        return kd;
    }
}
