/*
 * Turn a certain amount of degrees, with a gyro
 */
package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.bots.logomotion.Nashboard;
import edu.neu.nutrons.bots.logomotion.Robot;
import edu.neu.nutrons.lib.AutoModeCommand;
import edu.neu.nutrons.lib.Helpers;
import edu.neu.nutrons.lib.PID;
import edu.neu.nutrons.lib.PIDTuner;
import edu.neu.nutrons.lib.RelativeGyro;
import edu.wpi.first.wpilibj.Gyro;
import edu.wpi.first.wpilibj.SmartDashboard;
import edu.wpi.first.wpilibj.Timer;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class TurnDegreesCommand implements AutoModeCommand {

    final double pGain = 0.09;
    final double iGain = 0.015;
    final double dGain = 0.4;
    RelativeGyro gyro = Robot.getInstance().dBase.gyro;
    PID pid = new PID(pGain, iGain, dGain, 6, .83);
    PIDTuner tuner = PIDTuner.getInstance();
    Timer timeSinceAlmost = new Timer();
    Timer timeout = new Timer();
    boolean almostDone = false;
    double angle, maxRate, timeoutInSeconds;
    final double speedDeadband = .1;
    double angleDeadband = 2.0;
    double settleTime = .125;
    double lastError = 0;

    public TurnDegreesCommand(double angle, double maxRate, double timeoutInSeconds) {
        this.angle = angle;
        this.maxRate = maxRate;
        this.timeoutInSeconds = timeoutInSeconds;
    }

    public boolean doWork() {
        //  pid.setGains(tuner.getKP(), tuner.getKI(), tuner.getKD());
        double error = angle - gyro.getAngle();
        double speed = maxRate * Helpers.limitAbs(pid.calculate(error));
        if(Math.abs(error - lastError) < speedDeadband && Math.abs(error) < angleDeadband) {

            if(!almostDone) {
                timeSinceAlmost.start();
            }
            almostDone = true;
            SmartDashboard.log(true, "EndLogic");
        }
        else {
            almostDone = false;
            timeSinceAlmost.stop();
            timeSinceAlmost.reset();
            SmartDashboard.log(false, "EndLogic");

        }
        SmartDashboard.log(timeSinceAlmost.get(), "TimeSinceAlmost");
        //Nashboard.getInstance().setPIDDisplay(angle, gyro.getAngle());
        Robot.getInstance().dBase.drive(0, speed, true);
        SmartDashboard.log(error, "TurnToHeading Error");
        lastError = error;
        return timeSinceAlmost.get() > settleTime || timeout.get() > timeoutInSeconds;
    }

    public void init() {
        timeout.start();
        gyro.reset();
    }

    public void finish() {
        Robot.getInstance().dBase.stop();
    }
}
