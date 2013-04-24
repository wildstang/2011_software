/*
 * OperatorController
 *
 * This class defines how the control board inputs relate to controlling the robot
 *
 * This is essentially glue code between the ControlBoard and Robot Class
 *
 * Note: This is for driving and minibot deplpyment only!
 */

package edu.neu.nutrons.bots.logomotion;

import com.sun.squawk.util.MathUtils;
import edu.neu.nutrons.bots.logomotion.drivetrain.DriveStraightHelper;
import edu.neu.nutrons.bots.logomotion.elevator.*;
import edu.neu.nutrons.lib.Helpers;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class OperatorController {

    ControlMap cb = ControlBoard.getInstance();
    ElevatorOperatorController elevOpController = new ElevatorOperatorController(cb);
    Robot bot;
    DriveStraightHelper dsh = null;
    double spinSlope = 1;
    double spinPower = 1;

    OperatorController() {
        this.bot = Robot.getInstance();
    }



    void handle() {
        
        // Drive
        if(cb.getHighGear())
            bot.dBase.setHighGear();
        else
            bot.dBase.setLowGear();

        if(cb.getQuickTurn())
            bot.dBase.gyro.reset();
   
        bot.dBase.drive(cb.getThrottle(), cb.getSpin(), cb.getQuickTurn());

        if(cb.getMinibotDeploy() && cb.getMinibotLaunch()){
            bot.minibotDeployer.forceLaunch();
        }
        else if(cb.getMinibotDeploy()) {
            bot.minibotDeployer.deploy();
            bot.minibotDeployer.autoLaunch();
        }
        else if(cb.getMinibotLaunch()) {
            bot.minibotDeployer.launch();
        }

        elevOpController.handle();
        
    }
}
