/*
 * Gamepad Control Board
 *
 * This is another control board driver,
 * but this time with a gamepad as the elevator control
 */
package edu.neu.nutrons.bots.logomotion;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.SmartDashboard;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class GamepadControlBoard extends ControlBoard {

    Joystick pad = new Joystick(1);

    public boolean wantManualOveride() {
        return Math.abs(getElevatorThrottle()) > .1 || getWrist();
    }

    public double getElevatorThrottle() {
        SmartDashboard.log(pad.getRawAxis(4), "ElevSpeedGamepad");
        return pad.getRawAxis(4); // right y
    }

    public boolean getWrist() {
        return pad.getRawButton(7);
    }

    public boolean getMiniwrist() {
        return !getWrist();
    }

    public double getClawSpeed() {
        return pad.getRawAxis(2); // left y
    }

    public boolean getHomeBtn() {
        return pad.getRawAxis(6) > 0.1;
    }

    public boolean getLowBtn() {
        return pad.getRawButton(2);
    }

    public boolean getMidBtn() {
        return pad.getRawButton(3);
    }

    public boolean getHighBtn() {
        return pad.getRawButton(4);
    }

    public boolean getShiftBtn() {
        return pad.getRawAxis(6) < -0.1;
    } // dpad y

    public boolean getFloorBtn() {
        return pad.getRawButton(5);
    }

    public boolean getCapBtn() {
        return pad.getRawButton(6);
    }

    public boolean getHumanBtn() {
        return pad.getRawAxis(5) > 0.1;
    }
}
