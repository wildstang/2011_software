/*
 * DriveTrain
 *
 * This class defines how we drive our robot
 *
 * It contains all of the motors and sensors needed for the drive base,
 * and the algorithms used to steer it
 */
package edu.neu.nutrons.bots.logomotion.drivetrain;

import edu.neu.nutrons.bots.logomotion.BotProperties;
import edu.neu.nutrons.lib.MotorMechanism;
import edu.neu.nutrons.lib.MovingAverage;
import edu.neu.nutrons.lib.RelativeGyro;
import edu.wpi.first.wpilibj.AnalogChannel;
import edu.wpi.first.wpilibj.SmartDashboard;
import edu.wpi.first.wpilibj.Solenoid;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public final class DriveTrain { // Final because method called in constructor

    static DriveTrain inst = null;
    public MotorMechanism lMotor = new TwoVictorDrive(3, 4, 3, 4);
    public MotorMechanism rMotor = new OneVictorDrive(2, 1, 2);
    MovingAverage eDif = new MovingAverage(8);
    Solenoid shifter = new Solenoid(2);
    public RelativeGyro gyro = new RelativeGyro(1);
    public AnalogChannel ultrasonic = new AnalogChannel(BotProperties.ULTRASONIC_CHAN);
    boolean highGear = false;
    final double HIGH_GEAR_T_SENS = 1.7;
    final double LOW_GEAR_T_SENS = 1.36;
    public double dsp = 0;
    double tSens = 1.5;
    final double ULTRASONIC_SCALE = 1;

    public DriveTrain() {
        lMotor.setInvertedSensor(true);
        this.setLowGear();
    }

    public static DriveTrain getInstance() {
        if(inst == null) {
            inst = new DriveTrain();
        }
        return inst;
    }

    public void carDrive(double speed, double turn) {
        double rPower = 0;
        double lPower = 0;
        double turnConstant = 1;

        lPower = speed + (turn * turnConstant);
        rPower = speed - (turn * turnConstant);

        driveLR(lPower, rPower);
    }

    public void setTSens(double newTSens) {
        tSens = newTSens;
    }

    // Cheesy Drive - Thanks to Austin Schuh and Teams 254/971. Yeah Buddy!
    // It would not be possible to control a fast drive without this
    public void drive(double throttle, double wheel, boolean quickTurn) {

        double angular_power = 0.0;
        double overPower = 0.0;
        double sensitivity = tSens;
        double rPower = 0.0;
        double lPower = 0.0;

        if(quickTurn) {
            overPower = 1.0;
            sensitivity = 1.0;
            angular_power = wheel;
        }
        else {
            overPower = 0.0;
            angular_power = Math.abs(throttle) * wheel * sensitivity;
        }

        rPower = lPower = throttle;
        lPower += angular_power;
        rPower -= angular_power;

        if(lPower > 1.0) {
            rPower -= overPower * (lPower - 1.0);
            lPower = 1.0;
        }
        else if(rPower > 1.0) {
            lPower -= overPower * (rPower - 1.0);
            rPower = 1.0;
        }
        else if(lPower < -1.0) {
            rPower += overPower * (-1.0 - lPower);
            lPower = -1.0;
        }
        else if(rPower < -1.0) {
            lPower += overPower * (-1.0 - rPower);
            rPower = -1.0;
        }

        driveLR(lPower, rPower);
    }

    public void setHighGear() {
        shift(false);
        tSens = HIGH_GEAR_T_SENS;
    }

    public void setLowGear() {
        shift(true);
        tSens = LOW_GEAR_T_SENS;
    }

    private void shift(boolean wantHighGear) {
        highGear = wantHighGear;
        shifter.set(!highGear);
    }

    public void driveStraight(double speed, double heading) {
        double rawDif = this.lMotor.getRate() - this.rMotor.getRate();
        double cookedDif = eDif.calculate(rawDif);
        double turnPower = cookedDif * dsp;
        this.drive(speed, turnPower, false);
        SmartDashboard.log(dsp, "DSP");
        SmartDashboard.log(turnPower, "TurnPower");
        SmartDashboard.log(rawDif, "RawDif");
        SmartDashboard.log(cookedDif, "CookedDif");
    }

    public void driveLR(double left, double right) {
        lMotor.set(left);
        rMotor.set(-right); // this is flipped
    }

    public void stop() {
        drive(0, 0, false);
    }

    public void handle() {
        SmartDashboard.log(tSens, "Turn Sens");
        SmartDashboard.log(gyro.getAngle(), "Gyro");
    }

    public double getUltrasonic() {
        return ultrasonic.getVoltage() * ULTRASONIC_SCALE;
    }
}
