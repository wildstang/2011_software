/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package edu.neu.nutrons.bots.logomotion;

import edu.neu.nutrons.bots.logomotion.autocmd.*;
import edu.neu.nutrons.lib.*;
import edu.wpi.first.wpilibj.*;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Nutrons2011 extends IterativeRobot {

    AutoModeController ac = new AutoModeController();
    OperatorController oc = new OperatorController();
    AutoModeSelectionController amsc = new AutoModeSelectionController();
    BotConfig config = new BotConfig("settings.txt");
    int loops = 0;
    ControlMap cb = ControlBoard.getInstance();
    Robot bot = Robot.getInstance();

    public void robotInit() {
    }

    public void disabledInit() {
        bot.dBase.stop();
        bot.elev.setSpeed(0);
        bot.compressor.stop();
        ac.flush();
       
    }

    public void disabledPeriodic() {
        Nashboard.handleSD();
        Nashboard.getInstance().handle();
        PIDTuner.getInstance().handle();

        amsc.handle();
    }

    public void autonomousInit() {
        bot.compressor.start();
        bot.dBase.gyro.resetAbsolute(); // so we can turn the robot on before positioning it
        // Get the auto mode controller
        ac = amsc.getAC();
    }

    public void teleopInit() {
        bot.compressor.start();
        bot.minibotDeployer.startTeleopTimer();
    }

    public void autonomousPeriodic() {
        ac.handle();
        bot.handle();
        Nashboard.handleSD();
    }

    public void teleopPeriodic() {
        oc.handle();
        bot.handle();
        Nashboard.handleSD();
        Nashboard.getInstance().handle();
    }

    
}
