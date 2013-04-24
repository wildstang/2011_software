/*
 * Drive Straight Helper
 *
 * This calculates how much to pump into the the turn control to drive straight
 */
package edu.neu.nutrons.bots.logomotion.drivetrain;

import edu.neu.nutrons.bots.logomotion.Robot;
import edu.neu.nutrons.lib.PID;
import edu.wpi.first.wpilibj.SmartDashboard;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class DriveStraightHelper {

    double lStart = 0;
    double rStart = 0;
    public double gain = -.82;
    public PID pid;

    public DriveStraightHelper() {
        lStart = Robot.getInstance().dBase.lMotor.getPos();
        rStart = Robot.getInstance().dBase.rMotor.getPos();
        pid = new PID(gain, 0, 0);
    }

    public double calcTurn() {
        double curL = Robot.getInstance().dBase.lMotor.getPos() - lStart;
        double curR = Robot.getInstance().dBase.rMotor.getPos() - rStart;

        double error = curL - curR;
        SmartDashboard.log(error, "PosError");

        return pid.calculate(error);
    }
}
