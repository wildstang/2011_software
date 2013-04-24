/*
 * Servo Mini Bot Deployer
 *
 * This class deploys an MB using Nutrons Servo Releases
 *
 */

package edu.neu.nutrons.bots.logomotion.minibot;

import edu.neu.nutrons.bots.logomotion.BotProperties;
import edu.neu.nutrons.lib.ServoRelease;
import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.Timer;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class ServoMinibotDeployer implements MinibotDeployer {

    ServoRelease launch = new ServoRelease(BotProperties.MINIBOT_LAUNCH_CHAN, 130, 0);
    ServoRelease deploy = new ServoRelease(BotProperties.MINIBOT_DEPLOY_CHAN, 95, 0);
    Timer t = new Timer();
    Timer deployDelayTimer = new Timer();
    DigitalInput poleSwitch = new DigitalInput(12);

    final double MATCH_CLOCK_AT_DEPLOY = 10.04;
    final double DEPLOY_TIME    = 1.2; //time it takes for deployment mechanism to fall down
   

    public void startTeleopTimer() {
        t.reset();
        t.start();
    }

    public void deploy() {
        if(!deploy.getState()){
            // first time this is done
            deployDelayTimer.start();
        }

        deploy.release();

    }

    private boolean poleSwitchEngaged(){
        // Safeguard for touching pole - limit switch
        return true; //poleSwitch.get();
    }

    public void forceLaunch(){
         if(deploy.getState()) { // has it been deployed?
             launch.release();
        }
    }

    public void launch() {
        if(poleSwitchEngaged() || t.get() > 118.6){
            forceLaunch();
        }
    }
    public void autoLaunch() {
        if(deploy.getState() && deployDelayTimer.get() >= DEPLOY_TIME && t.get() >= 120.0 - MATCH_CLOCK_AT_DEPLOY) { 
            // has it been deployed? all the way?
            // is it time yet?
            launch();
        }
    }
}
