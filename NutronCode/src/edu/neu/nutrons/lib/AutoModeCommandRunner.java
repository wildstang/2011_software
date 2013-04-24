/*
 * AutoModeCommandRunner
 *
 * This helps run automode commands
 */

package edu.neu.nutrons.lib;

/**
 *
 * @author Tom
 */
public class AutoModeCommandRunner {
    AutoModeCommand cmd;
    boolean firstRun = true;
    boolean cmdDone = false;

    public AutoModeCommandRunner(AutoModeCommand myCmd){
        cmd = myCmd;
    }

    public boolean  doWork(){
        if(cmdDone){
            return true; // dont do any more work on it.
        }

        if(firstRun){
            cmd.init();
            firstRun = false;
        }
        boolean done = cmd.doWork();

        if(done){
            cmd.finish();
            cmdDone = true;
        }
        return done;
    }

}
