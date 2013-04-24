/*
 * DebouncedDigitalInput
 *
 * This is a simple debouncer for a digital switch.
 * 
 */

package edu.neu.nutrons.lib;

import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.Timer;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class DebouncedDigitalInput extends DigitalInput {

    double debounceTime;
    boolean activeHigh;
    boolean hasBeenTrue = false;
    Timer t = new Timer();

    public DebouncedDigitalInput(int port, double debounceTime, boolean activeHigh) {
        super(port);
        this.activeHigh = activeHigh;
        this.debounceTime = debounceTime;
    }

    public boolean get() {
        boolean triggered = activeHigh ? super.get() : !super.get();
        if(!triggered) {
            t.reset();
            t.stop();
            hasBeenTrue = false;
        }
        else {
            if(!hasBeenTrue) {
                t.start();
            }
            hasBeenTrue = true;
            if(t.get() > debounceTime) {
                return activeHigh ? true : false;
            }
        }
        return activeHigh ? false : true;
    }

}
