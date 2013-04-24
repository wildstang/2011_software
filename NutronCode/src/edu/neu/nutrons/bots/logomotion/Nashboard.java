/*
 * Nashboard
 *
 * This class handles all of the dashboardy/diagnostic things
 */

package edu.neu.nutrons.bots.logomotion;

import edu.neu.nutrons.lib.PIDTuner;
import edu.wpi.first.wpilibj.Dashboard;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.SmartDashboard;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class Nashboard {
    public double setpoint, curPos;
    private static Nashboard inst = null;

    public static Nashboard getInstance(){
        if(inst == null){
            inst = new Nashboard();
        }
        return inst;
    }

    public void setPIDDisplay(double setpoint, double curPos){
        this.setpoint = setpoint; this.curPos = curPos;
    }

    public void handle(){

        Dashboard lowDashData = DriverStation.getInstance().getDashboardPackerLow();
        lowDashData.addCluster();
        {
            lowDashData.addCluster(); // Elevator
            {
                lowDashData.addCluster(); // setpoint and pos
                {
                    lowDashData.addFloat((float)setpoint);
                    lowDashData.addFloat((float)curPos);
                }
                    lowDashData.finalizeCluster();
                    lowDashData.addCluster(); // PID gains
                {
                    lowDashData.addFloat((float)PIDTuner.getInstance().getKP());
                    lowDashData.addFloat((float)PIDTuner.getInstance().getKI());
                    lowDashData.addFloat((float)PIDTuner.getInstance().getKD());
                }
                lowDashData.finalizeCluster();
            }
            lowDashData.finalizeCluster();
        }
        lowDashData.finalizeCluster();
        lowDashData.commit();

    }

    public static void handleSD(){
        SmartDashboard.log(Robot.getInstance().dBase.lMotor.getPos(), "Left Encoder Position");
        SmartDashboard.log(Robot.getInstance().dBase.rMotor.getPos(), "Right Encoder Position");
        SmartDashboard.log(Robot.getInstance().dBase.lMotor.getRate(), "Left Encoder Rate");
        SmartDashboard.log(Robot.getInstance().dBase.rMotor.getRate(), "Right Encoder Rate");
    }
}
