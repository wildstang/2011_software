/*
 * Turn fast to a threshold
 */

package edu.neu.nutrons.bots.logomotion.autocmd;

/**
 *
 * @author ziv
 */
public class TurnUntilThresholdCommand extends TurnDegreesCommand{
    public TurnUntilThresholdCommand(double degrees, double maxRate, double timeout){
        super(degrees,maxRate,timeout);
        super.pid.setGains(pGain * 1.7, 0, dGain); // give the pGain a kick to make it turn a bit faster. this should kill the need for I
    }

    public boolean doWork(){
        boolean result = super.doWork();
        if(Math.abs(gyro.getAngle()) >= Math.abs(angle)){
            return true;
        }
        return result;
    }
}