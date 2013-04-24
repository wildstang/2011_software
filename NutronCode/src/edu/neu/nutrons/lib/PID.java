/*
 * PID Calculator
 */
package edu.neu.nutrons.lib;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class PID {

    double kP, kI, kD;
    int integralInterval;
    static final int DEFAULT_INTEGRAL_INTERVAL = 100;
    double[] oldErrors;
    double sumError = 0;
    double minI = .1;
    double maxSumError = 0.5;
    int i = 0;
    double lastError;

    public PID(double kP, double kI, double kD, int integralInterval) {
        this.kP = kP;
        this.kI = kI;
        this.kD = kD;
        this.integralInterval = integralInterval;
        oldErrors = new double[integralInterval];
    }

    public PID(double kP, double kI, double kD, double minI, double maxSumError) {
        this.kP = kP;
        this.kI = kI;
        this.kD = kD;
        this.minI = minI;
        this.maxSumError = maxSumError;
    }

    public PID(double kP, double kI, double kD) {
        this.kP = kP;
        this.kI = kI;
        this.kD = kD;
        this.integralInterval = DEFAULT_INTEGRAL_INTERVAL;
        oldErrors = new double[integralInterval];
    }

    public void setGains(double kP, double kI, double kD) {
        this.kP = kP;
        this.kI = kI;
        this.kD = kD;
    }

    public double calculate(double error) {
        /*  sumError += error - oldErrors[i]; // add newest error, subtract oldest error
        oldErrors[i] = error;
        double ret = (kP * error) + (kI * sumError) - (kD * (error - lastError));
        lastError = error;
        i++;
        if(i >= integralInterval) {
        i = 0;
        }
        return ret;*/

        double P = error * kP;

        if(error > minI) {
            sumError = 0;
        }

        sumError += error;

        if(sumError > maxSumError / kI) {
            sumError = maxSumError;
        }
        else if(sumError < -maxSumError / kI) {
            sumError = -maxSumError;
        }

        double I = sumError * kI;
        double D = (error - lastError) * kD;

        lastError = error;

        double ret = P + I + D;
        return ret;
    }

    public double calculate(double setpoint, double curPos) {
        return this.calculate(setpoint - curPos);
    }
}
