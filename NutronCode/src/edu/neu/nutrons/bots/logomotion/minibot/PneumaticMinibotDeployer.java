/*
 * Pneumatic Mini Bot Deployer
 *
 * This deplpys a MB using solenoids
 */

package edu.neu.nutrons.bots.logomotion.minibot;

import edu.neu.nutrons.bots.logomotion.BotProperties;
import edu.wpi.first.wpilibj.Solenoid;
import edu.wpi.first.wpilibj.Timer;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class PneumaticMinibotDeployer implements MinibotDeployer {

    Solenoid launch = new Solenoid(BotProperties.MINIBOT_LAUNCH_CHAN_SOLE);
    Solenoid deploy = new Solenoid(BotProperties.MINIBOT_DEPLOY_CHAN_SOLE);
    Timer t = new Timer();
    Timer deployDelayTimer = new Timer();

    final double MATCH_CLOCK_AT_DEPLOY = 10.04; // jump the gun a little
    final double DEPLOY_TIME    = 1.2; //time it takes for deployment mechanism to fall down

    public void startTeleopTimer() {
        t.reset();
        t.start();
    }

    public void deploy() {
        if(!deploy.get()){
            // first time this is done
            deployDelayTimer.start();
        }

        deploy.set(true);

    }

    public void launch() {
        if(deploy.get()) { // has it been deployed?
            launch.set(true);
        }
    }
    public void autoLaunch() {
        if(deploy.get() && deployDelayTimer.get() >= DEPLOY_TIME && t.get() >= 120.0 - MATCH_CLOCK_AT_DEPLOY) {
            // has it been deployed? all th way?
            // is it time yet?
            launch();
        }
    }
}
