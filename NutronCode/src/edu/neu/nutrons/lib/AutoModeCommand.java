/*
 * AutoModeCommand Interface
 *
 */

package edu.neu.nutrons.lib;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public interface AutoModeCommand {
    boolean doWork();
    void init();
    void finish();
}
