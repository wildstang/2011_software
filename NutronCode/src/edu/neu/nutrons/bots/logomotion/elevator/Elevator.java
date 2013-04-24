/*
 * Elevator
 *
 * This class handles all of the low level control for the elevator
 *
 * It sets motor speeds and such.
 */
package edu.neu.nutrons.bots.logomotion.elevator;

import edu.neu.nutrons.bots.logomotion.BotProperties;
import edu.neu.nutrons.bots.logomotion.elevator.cmd.ElevatorCommand;
import edu.neu.nutrons.lib.Helpers;
import edu.neu.nutrons.lib.MotorMechanism;
import edu.wpi.first.wpilibj.SmartDashboard;
import edu.wpi.first.wpilibj.Solenoid;
import edu.wpi.first.wpilibj.Timer;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class Elevator {

    static Elevator inst = null;
    private ElevatorMotorMechanism liftDrive = new ElevatorMotorMechanism(5, 6, 5, 6);
    private Solenoid wrist = new Solenoid(3); // Check number!
    private Solenoid miniwrist = new Solenoid(1); // Check number!
    public RollerClaw claw = new RollerClaw(7,BotProperties.ROLLER_CLAW_TUBE_SWITCH_CHAN);
    public ElevatorCommand curCmd;
    final static double MAX_SPEED = 1.0;
    final static double CAP_SPEED = .75;


    // preset positions, need to be measured
    public static final double HEIGHT_HOME = -.1;
    public static final double HEIGHT_LOW = -.1;
    public static final double HEIGHT_MID = .42;
    public static final double HEIGHT_HIGH = .908;
    public static final double HEIGHT_FLOOR = -.1;
    public static final double HEIGHT_HUMAN = .5;
    public static final double OFFSET_AMT = .075;
    public static final double SCORING_DROP = .085;
    // time delays, need to be measured
    public static final double TIME_CAP_WRIST = .25;
    public static final double TIME_CAP_CLAW = .25;
    public static final double TIME_FLOOR_CLAW = .25;
    public static final double TIME_HUMAN_CLAW = .25;
    //public static final double SPEED_CLAW_IN = -.85;
    //public static final double SPEED_CLAW_OUT = .85;
    private boolean reverseLiftMotors = true;
    private boolean reverseClawMotor = false;
    private boolean reverseMiniwrist = true;

    private final double ELEVATOR_DOWN_TIMEOUT = 1.0;
    private boolean startedDownTimer = false;
    private Timer downTimer = new Timer();

    public static Elevator getInstance() {
        if(inst == null) {
            inst = new Elevator();
        }
        return inst;
    }

    public void setCommand(ElevatorCommand cmd) {
        curCmd = cmd;
    }

    public void handle() {

        // safety thing
        if(curCmd == null) {
            setSpeed(0);
        }
        else {

            double wantedSpeed = curCmd.calcSpeed(getPos());
            // Helpful for going down
            if(wantedSpeed < 0) {
                wantedSpeed = wantedSpeed / 2.15;
            }
            if(wantedSpeed > 0.7 && getPos() > .7){
                wantedSpeed = 0.7;
            }
            // Bottom logic timeout
            if(wantedSpeed < 0 && getPos() < .2){
                // start elevator timer
                if(!startedDownTimer){
                    downTimer.start();
                    startedDownTimer = true;
                }
                // get elevator timer
                if(downTimer.get() > ELEVATOR_DOWN_TIMEOUT){
                    wantedSpeed = 0;
                }
            }
            else{
                startedDownTimer = false;
                downTimer.stop();
                downTimer.reset();
            }

            if(getPos() <  0 ){
                liftDrive.resetFB();
            }

            

            setWrist(curCmd.getWrist());
            setMiniwrist(curCmd.getMiniwrist());
            setSpeed(wantedSpeed);

            
        }

        // Feedback
        SmartDashboard.log(liftDrive.getPos(), "Elevator Position");
    }

    public boolean isDone() {
        if(curCmd != null) {
            return curCmd.isDone();
        }
        else {
            return true;
        }
    }

    public void doOffset() {
        if(curCmd != null) {
            curCmd.doOffset();
        }
    }

    public void setAdjustment(double adjustment) {
        if(curCmd != null) {
            curCmd.setAdjustment(adjustment);
        }
    }

    public void setSpeed(double speed) {
        liftDrive.set(Helpers.limitAbs((reverseLiftMotors) ? -speed : speed, MAX_SPEED));
    }
    
    public void setWrist(boolean on) {
        wrist.set(on);
    }

    public void setMiniwrist(boolean on) {
        miniwrist.set((reverseMiniwrist ? !on : on));
    }

    public boolean getWrist() {
        return wrist.get();
    }

    public boolean getMiniwrist() {
        return (reverseMiniwrist ? !miniwrist.get() : miniwrist.get());
    }

    public double getPos() {
        return liftDrive.getPos();
    }

    public double getRate() {
        return liftDrive.getRate();
    }
}
