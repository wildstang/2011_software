/*
 * Double Command
 *
 * This takes 2 other auto mode commands, and executes them in parallel
 with a time delay between their start
 *
 */


package edu.neu.nutrons.bots.logomotion.autocmd;

import edu.neu.nutrons.lib.AutoModeCommand;
import edu.wpi.first.wpilibj.Timer;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class DoubleCommand implements AutoModeCommand{
    Timer t = new Timer();
    AutoModeCommand firstCmd;
    AutoModeCommand secondCmd;
    double wait;
    boolean secondTriggered = false;

    public DoubleCommand(AutoModeCommand cmd1, double waitTime, AutoModeCommand cmd2){
        firstCmd = cmd1;
        secondCmd = cmd2;
        wait = waitTime;
    }

    public boolean doWork() {
        if(t.get() > wait){
            if(!secondTriggered){
                secondCmd.init();
                secondTriggered = true;
            }
            secondCmd.doWork();
        }
        return firstCmd.doWork();
    }

    public void init() {
        firstCmd.init();
        t.start();
    }

    public void finish() {
        firstCmd.finish();
        secondCmd.finish();
    }

}
