/*
 * Turn a certain amount of degrees, with encoders
 */
package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.bots.logomotion.Robot;
import edu.neu.nutrons.lib.AutoModeCommand;
import edu.neu.nutrons.lib.Helpers;
import edu.neu.nutrons.lib.PID;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class TurnDegreesWithEncodersCommand implements AutoModeCommand {

    Robot bot = Robot.getInstance();
    double gain = 1.75;
    double scale = 90. / 3.;
    PID pid = new PID(gain, 0, 0);
    double startLPos, startRPos;
    double degrees;
    double maxRate;

    public TurnDegreesWithEncodersCommand(double degrees, double maxRate) {
        this.degrees = degrees;
        this.maxRate = maxRate;
    }

    public boolean doWork() {
        double curAngle = scale * ((bot.dBase.lMotor.getPos() - startLPos) - (bot.dBase.rMotor.getPos() - startRPos));
        double turnPower = Helpers.limitAbs(pid.calculate(degrees, curAngle), maxRate);
        bot.dBase.drive(0, turnPower, true);
        return Math.abs(degrees - curAngle) < 2;
    }

    public void init() {
        startLPos = bot.dBase.lMotor.getPos();
        startRPos = bot.dBase.rMotor.getPos();
    }

    public void finish() {
        bot.dBase.stop();
    }
}
