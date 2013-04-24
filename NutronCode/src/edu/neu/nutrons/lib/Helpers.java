/*
 * Some math functions
 */
package edu.neu.nutrons.lib;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class Helpers {

    public static double limitAbs(double in, double limit) {
        if(limit < 0) {
            limit *= -1;
        }
        if(in < -limit) {
            in = -limit;
        }
        if(in > limit) {
            in = limit;
        }
        return in;
    }

    public static double limitAbs(double in) {
        return limitAbs(in, 1.0);
    }

    public static double deadband(double value, double deadband, double center) {
        return (value < (center + deadband) && value > (center - deadband))
                ? center : value;
    }

    public static double radiansFromDegrees(double degrees){
        return (degrees * Math.PI) / 180.0;
    }
}
