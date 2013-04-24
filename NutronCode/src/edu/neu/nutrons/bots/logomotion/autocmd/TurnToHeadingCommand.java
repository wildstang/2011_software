/*
 * Turn to an absolute heading
 */
package edu.neu.nutrons.bots.logomotion.autocmd;


/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class TurnToHeadingCommand extends TurnDegreesCommand {

    double wantedHeading;
    public TurnToHeadingCommand(double heading, double maxRate, double timeout){
        super(0,maxRate,timeout);
        wantedHeading = heading;
    }


    // IT would be better to do this the other way around, but this is easier...
    
    public void init() {
        super.init();
        this.angle = wantedHeading - gyro.getAbsoluteAngle();
        
    }

}
