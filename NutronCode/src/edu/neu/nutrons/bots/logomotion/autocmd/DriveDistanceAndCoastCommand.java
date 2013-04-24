/*
 * Drive a certain distance, then coast
 */

package edu.neu.nutrons.bots.logomotion.autocmd;

/**
 *
 * @author Tom
 */
public class DriveDistanceAndCoastCommand extends DriveDistanceCommand{
     public DriveDistanceAndCoastCommand(double distance, double speed, double timeoutInSeconds) {
        super(distance, speed,timeoutInSeconds);
        super.doCoast = true;
    }
}
