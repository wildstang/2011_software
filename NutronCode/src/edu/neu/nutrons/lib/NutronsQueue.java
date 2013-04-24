/*
 * NutronsQueue
 *
 * This J2ME doesnt have a queue implementation,
 * so we made one
 */
package edu.neu.nutrons.lib;

import java.util.NoSuchElementException;
import java.util.Vector;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class NutronsQueue extends Vector {

    public void push(Object obj) {
        this.addElement(obj);
    }

    public Object pop() {
        if(this.isEmpty()) {
            return null;
        }
        try {
            Object ret = this.firstElement();
            this.removeElementAt(0);
            return ret;
        }
        catch(NoSuchElementException e) {
            e.printStackTrace();
            return null;
        }
    }
}
