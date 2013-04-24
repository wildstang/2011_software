/*
 * Drive and shake.. useful for hitting a peg at weird angles
 */

package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.bots.logomotion.Robot;
import edu.neu.nutrons.lib.Helpers;
import edu.wpi.first.wpilibj.Timer;

/**
 *
 * @author Tom
 */



public class ShimmyDriveCommand{
    double maxTurn;
    double period;
    double speed;
    double timeOut;
    Timer t = new Timer();
    Robot bot = Robot.getInstance();

     public ShimmyDriveCommand( double speed, double maxTurn, double period, double timeOut) {
        this.speed = speed;
        this.maxTurn = maxTurn;
        this.period = period;
        this.timeOut = timeOut;


    }
    
     public boolean doWork() {

        
        speed = Helpers.limitAbs(speed, 1.0);
        double phase = ((t.get() / period) * (2.0 * Math.PI)); // calculate the sin wave
        // For example, period is 0.5 s. Timer reads 0.6.
        // 0.6 / 0.5 = 1.2
        // 1.2 * 2 * PI = 7.53
        // Sin(7.53) = 0.94 , still turning right, about to turn back left
        double turn = Math.sin(phase) * maxTurn;


        bot.dBase.drive(speed, turn, false); //maybe this needs to be true?

        return t.get() > timeOut;
    }

     public void init() {
        t.start();
    }

    public void finish() {
        t.stop();
        bot.dBase.stop();
    }
}
