/*
 * Drive Distance
 */
package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.bots.logomotion.Robot;
import edu.neu.nutrons.bots.logomotion.drivetrain.DriveStraightHelper;
import edu.neu.nutrons.lib.AutoModeCommand;
import edu.neu.nutrons.lib.Helpers;
import edu.neu.nutrons.lib.PID;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class DriveDistanceNoTimeoutCommand implements AutoModeCommand {

    double distance;
    double firstPos;
    boolean firstWork = true;
    double maxSpeed;
    int i = 0;
    Robot bot;
    DriveStraightHelper dsh;
    PID disController;
    boolean doCoast = false;

    public DriveDistanceNoTimeoutCommand(double distance, double maxSpeed) {
        this(distance,maxSpeed,false); //stop the bot
    }
    public DriveDistanceNoTimeoutCommand(double distance, double maxSpeed, boolean coastAtEnd) {
        this.distance = distance;
        this.maxSpeed = maxSpeed;
        bot = Robot.getInstance();
        disController = new PID(.8, .01, 0, .8, .3);
        doCoast = coastAtEnd; //coast the bot
    }

    private double getPos() {
        return (bot.dBase.lMotor.getPos() + bot.dBase.rMotor.getPos()) / 2;
    }

    public boolean doWork() {

        double dir = (distance <= 0) ? -1 : 1;

        // make it drive...

        double speed = disController.calculate(distance, (this.getPos() - firstPos));
        if(doCoast){
            speed = maxSpeed; //simple enough
        }
        speed = Helpers.limitAbs(speed, maxSpeed);
        bot.dBase.drive(speed, dsh.calcTurn(), false);

        return Math.abs(this.getPos() - firstPos) >= Math.abs(distance);
    }

    public void init() {
        firstPos = this.getPos();
        dsh = new DriveStraightHelper();
    }

    public void finish() {
        bot.dBase.stop();
    }
}
