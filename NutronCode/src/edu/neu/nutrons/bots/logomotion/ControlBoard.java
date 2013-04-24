/*
 * ControlBoard
 *
 * This class implements the ControlMap interface and
 * is a driver for our driver control board,
 * which consists of 2 joysticks for base driving (one for throttle, one for turn),
 * a custom button box for elevator control, and another joystick for elevator manual
 * over ride
 */
package edu.neu.nutrons.bots.logomotion;

import edu.neu.nutrons.bots.logomotion.elevator.RollerClaw;
import edu.neu.nutrons.lib.Helpers;
import edu.neu.nutrons.lib.PulseTriggerBoolean;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.DriverStationEnhancedIO;
import edu.wpi.first.wpilibj.DriverStationEnhancedIO.EnhancedIOException;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.SmartDashboard;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class ControlBoard implements ControlMap {

    DriverStationEnhancedIO io = DriverStation.getInstance().getEnhancedIO();
    private static ControlBoard instance;
    PulseTriggerBoolean[] buttonsDown;
    PulseTriggerBoolean[] buttonsUp;
    Joystick js = new Joystick(1);

    // Private for singleton
    protected ControlBoard() {
    }

    // Singleton instance
    public static ControlBoard getInstance() {
        if(instance == null) {
            instance = new ControlBoard();
        }
        return instance;
    }

    // Note: methods are public if and only if they're in the interface
    static double scaleAnalog(double voltageIn) {
        double normalized = (2 * voltageIn / 3.25) - 1;
        return normalized;
    }

    static double capAndBand(double value) {
        value = Helpers.deadband(value, .06, -1);
        value = Helpers.deadband(value, .06, 0);
        value = Helpers.deadband(value, .06, 1);
        return Helpers.limitAbs(value);
    }

    public double getThrottle() {
        double throttle = 0;
        try {
            throttle = io.getAnalogIn(3);
        }
        catch(EnhancedIOException ex) {
            return 0;
        }
        SmartDashboard.log(throttle, "RawThrottle");
        double refined = capAndBand(scaleAnalog(throttle));
        SmartDashboard.log(refined, "CookedThrottle");
        return refined;
    }

    public boolean getQuickTurn() {
        boolean qt = false;
        try {
            qt = !io.getDigital(1); //active low
            SmartDashboard.log(qt, "QuickTurn");
        }
        catch(EnhancedIOException ex) {
        }
        return qt;
    }

    public double getSpin() {
        double spin = 0;
        try {
            spin = io.getAnalogIn(1);
            SmartDashboard.log(spin, "RawSpin");
        }
        catch(EnhancedIOException ex) {
            return 0;
        }
        double refined = capAndBand(scaleAnalog(spin));
        SmartDashboard.log(refined, "CookedSpin");
        return refined;
    }

    public boolean getHighGear() {
        boolean hg = false;
        try {
            hg = !io.getDigital(3); //active low
            SmartDashboard.log(hg, "HighGear");
        }
        catch(EnhancedIOException ex) {
        }
        return hg;
    }

    public boolean getLowGear() {
        boolean lg = false;
        try {
            lg = !io.getDigital(5); //active low
            SmartDashboard.log(lg, "LowGear");
        }
        catch(EnhancedIOException ex) {
        }
        return lg;
    }

    public boolean getHomeBtn() {
        return getLowBtn();
    }

    public boolean getLowBtn() {
        try {
            return !io.getDigital(2);
        }
        catch(EnhancedIOException ex) {
            return false;
        }
    }

    public boolean getMidBtn() {
        try {
            return !io.getDigital(4);
        }
        catch(EnhancedIOException ex) {
            return false;
        }
    }

    public boolean getHighBtn() {
        try {
            return !io.getDigital(7);
        }
        catch(EnhancedIOException ex) {
            return false;
        }
    }

    public boolean getShiftBtn() {
        try {
            return !io.getDigital(6);
        }
        catch(EnhancedIOException ex) {
            return false;
        }
    }

    public boolean getFloorBtn() {
        try {
            return !io.getDigital(8);
        }
        catch(EnhancedIOException ex) {
            return false;
        }
    }

    public boolean getCapBtn() {
        try {
            return !io.getDigital(10);
        }
        catch(EnhancedIOException ex) {
            return false;
        }
    }

    public boolean getHumanBtn() {
        try {
            return !io.getDigital(12);
        }
        catch(EnhancedIOException ex) {
            return false;
        }
    }

    public boolean wantManualOveride() {
        return Math.abs(getElevatorThrottle()) > .12 || getWrist() || getClawIn() || getClawOut();
    }

    public double getElevatorThrottle() {
        SmartDashboard.log(js.getY(), "JS Elev Speed");
        return Helpers.deadband(js.getY(), .10125, 0);
    }

    public boolean getMiniwrist() {
        // always opposed to wrist
        return js.getRawButton(2);
    }

    public boolean getWrist() {
        return js.getRawButton(3) || js.getRawButton(4) || js.getRawButton(5);
    }

    public double getClawSpeed() {
        // Intake if wrist is down, spit out if wrist is up, but only if trigger is pressed
        // Will probably change, but I don't have the joystick with me so I didn't want to make button mapping yet -Ziv
        if(getClawIn())
            return RollerClaw.SPEED_CLAW_IN;
        if(getClawOut())
            return RollerClaw.SPEED_CLAW_RELEASE;
        return 0;
    }

    public boolean getClawIn(){
        return ( js.getRawButton(6) || js.getRawButton(7));
    }

    public boolean getClawOut(){
        return js.getRawButton(1);
    }

    public boolean getMinibotDeploy() {
        try {
            return !io.getDigital(14);
        }
        catch(EnhancedIOException ex) {
            return false;
        }
    }
    
    public boolean getMinibotLaunch() {
        try {
            return !io.getDigital(16);
        }
        catch(EnhancedIOException ex) {
            return false;
        }
    }

    public double getElevatorAdjustment() {
        // TODO: link this to an analog input, may need deadband or value smoothing
        return 0;
    }
}
