/*
 * ElevatorCommand
 * 
 * This is the base Class for all elevator command
 */
package edu.neu.nutrons.bots.logomotion.elevator.cmd;

import edu.neu.nutrons.bots.logomotion.Nashboard;
import edu.neu.nutrons.lib.Helpers;
import edu.neu.nutrons.lib.PID;
import edu.neu.nutrons.lib.PIDTuner;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class ElevatorCommand {

    double pos; //setpoint
    double lastFB = 0;
   
    boolean wrist;
    boolean miniwrist;
    boolean scoring = false;
    boolean timed = false;
    final double DEADBAND_FRACTION = 150;
    PID pid;

    public ElevatorCommand(double pos, boolean wrist, boolean miniwrist) {

        this.pos = pos;
        
        this.wrist = wrist;
        this.miniwrist = miniwrist;
        // To do: change these!
        pid = new PID(0, 0, 0, 0.05, .5);
    }

    public boolean equals(ElevatorCommand cmd) {
        // Doesn't distinguish between timed commands with different times...
        // ... but it doesn't really matter for what we're doing
        return (this.pos == cmd.pos && this.wrist == cmd.wrist && this.miniwrist == cmd.miniwrist
                &&  this.scoring == cmd.scoring && this.timed == cmd.timed);
    }

    public boolean isDone() {
        // Have we gotten there?
        double error = pos - lastFB;
        boolean ret = (error >= -(1. / DEADBAND_FRACTION)) && (error <= (1. / DEADBAND_FRACTION));
        return ret;
    }

    public double calcSpeed(double realPos) {
        PIDTuner t = PIDTuner.getInstance();

        lastFB = realPos;
        double error = pos - realPos;
        
         double kp = 25;
        double ki = 1.0;
        double kd = 33;
       /* if(error < 0) {
            kd *= 1.5;
            kp /= 2.0;
        }
        * */
        
         
        // Let's try first without changing gains for trip down.
        //double kp =t.getKP(); //16.25;//
        //double ki =t.getKI(); //0.5;//
        //double kd =t.getKD();//30.0;//
        if(realPos < .1) {
            ki = 0;
        }
        pid.setGains(kp, ki, kd);

        Nashboard.getInstance().setPIDDisplay(pos, realPos);
        
        double ret = pid.calculate(error);
        ret = Helpers.limitAbs(ret);
        return ret;
    }

    

    public boolean getWrist() {
        return wrist;
    }

    public boolean getMiniwrist() {
        return miniwrist;
    }

    public double getPos() {
        return pos;
    }

    public double getWantedPos() {
        return this.pos;
    }

    public void doOffset() {
        // Override me!
    }

    public void setAdjustment(double adjustment) {
        // Override me too!
    }
}
