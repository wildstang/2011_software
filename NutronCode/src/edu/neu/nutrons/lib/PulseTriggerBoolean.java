/*
 * Pulse Trigger Boolean
 *
 * This is a boolean that will only return true once per cycle.
 */
package edu.neu.nutrons.lib;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class PulseTriggerBoolean {

    private boolean state = false;
    private boolean oldIn = false;

    public void set(boolean in) {
        if(oldIn == false && in == true) {
            state = true;
        }
        else {
            state = false;
        }
        oldIn = in;
    }

    public boolean get() {
        return state;
    }
}
