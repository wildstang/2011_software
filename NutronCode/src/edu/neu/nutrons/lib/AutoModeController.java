/*
 * This is a generic Auto Mode Controller
 *
 * It runs a queue of auto mode commands
 *
 * You can write commands into it, then ask it to run them
 */
package edu.neu.nutrons.lib;

import edu.wpi.first.wpilibj.Timer;

/**
 *
 * @author NUTRONS_PROGRAMMING
 */
public class AutoModeController {
    // Variables

    NutronsQueue cmdList = new NutronsQueue();
    AutoModeCommand curCmd = null;

    // Timeout stuff
    Timer timeoutTimer = new Timer();
    AutoModeCommand timeoutCommand = null;
    double timeoutTime = 100;
    boolean firstRunOfController = true;
    AutoModeCommandRunner toRunner = null;

    // Add commands
    public void addCommand(AutoModeCommand cmd) {
        cmdList.push(cmd);
    }

    public void setTimeoutCommand(AutoModeCommand toCmd, double time) {
        timeoutCommand = toCmd;
        timeoutTime = time;
    }

    public void flush() {
        cmdList.removeAllElements();
        curCmd = null;
    }

    // Execute commands
    public void handle() {
        boolean firstRun = false;
        if (curCmd == null) {
            curCmd = (AutoModeCommand) cmdList.pop();
            if (curCmd != null) {
                System.out.println("Popped a command: " + curCmd);
            }
            firstRun = true;
        }

        if (curCmd != null) {
            if (firstRun) {
                curCmd.init();
                firstRun = false;
            }
            if (curCmd.doWork()) {
                // this will happen when command is done
                // Will grab next command on next call of handle()
                curCmd.finish();
                curCmd = null;
                System.out.println("work done");
            }
        } else {
            // Maybe add something for do nothing?
        }

        // Timeout command handling!

        if (timeoutCommand != null) {
            if (firstRunOfController) {
                timeoutTimer.start();
                firstRunOfController = false;
                toRunner = new AutoModeCommandRunner(timeoutCommand);
            }
            if (timeoutTimer.get() >= timeoutTime) { // only run him when the timeout happens!
                boolean result = toRunner.doWork();
                if(result){
                    timeoutCommand = null; // dont do any more work on this command
                }
            }
        }

    }
}
