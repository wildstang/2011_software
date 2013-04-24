/*
 * Minibot Deployer Interface
 *
 * This interface defines how some mechanical system that launches our minibot
 * should work. Implementations should support both manual and automatic timed launching
 */

package edu.neu.nutrons.bots.logomotion.minibot;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public interface MinibotDeployer {
        public void startTeleopTimer();

    public void deploy();

    public void launch();
    public void autoLaunch();



}
