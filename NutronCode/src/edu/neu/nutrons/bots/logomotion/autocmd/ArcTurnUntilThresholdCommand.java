/*
 * ArcTurnUntilThresholdCommand
 */

package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.bots.logomotion.Robot;
import edu.neu.nutrons.lib.AutoModeCommand;
import edu.wpi.first.wpilibj.Gyro;
import edu.wpi.first.wpilibj.Timer;

/**
 *
 *@author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class ArcTurnUntilThresholdCommand implements AutoModeCommand {

    double angle;
    double speed;
    double turnPower;
    double timeoutInSeconds;
    int sign;
    Gyro gyro = Robot.getInstance().dBase.gyro;
    Timer timeout = new Timer();

    public ArcTurnUntilThresholdCommand(double angleClockwise, double speed, double absTurnPower, double timeoutInSeconds) {
        this.angle = angleClockwise;
        this.speed = speed;
        this.turnPower = Math.abs(absTurnPower);
        this.timeoutInSeconds = timeoutInSeconds;
        sign = (angle > 0) ? 1 : -1;
    }

    public boolean doWork() {
        Robot.getInstance().dBase.drive(speed, sign*Math.abs(turnPower), true);
        return timeout.get() > timeoutInSeconds || (Math.abs(gyro.getAngle()) > Math.abs(angle));
    }

    public void init() {
        timeout.start();
        gyro.reset();
    }

    public void finish() {
    }

}
