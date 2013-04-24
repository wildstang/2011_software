/*
 * Robot
 *
 * This class defines and holds the multiple sub systems for a robot
 */

package edu.neu.nutrons.bots.logomotion;

import edu.neu.nutrons.bots.logomotion.minibot.ServoMinibotDeployer;
import edu.neu.nutrons.bots.logomotion.drivetrain.DriveTrain;
import edu.neu.nutrons.bots.logomotion.elevator.Elevator;
import edu.neu.nutrons.bots.logomotion.elevator.ElevatorController;
import edu.wpi.first.wpilibj.Compressor;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class Robot {
    public DriveTrain dBase;
    public Elevator elev;
    public ElevatorController elevController;
    public ServoMinibotDeployer minibotDeployer;
    static private Robot instance = null;
    Compressor compressor = new Compressor(BotProperties.PRESSURE_SWITCH_CHAN, BotProperties.COMP_RELAY_CHAN);

    protected Robot(){
        dBase = DriveTrain.getInstance();
        elev = Elevator.getInstance();
        elevController = ElevatorController.getInstance();
        minibotDeployer = new ServoMinibotDeployer();
        
    }

    public static Robot getInstance(){
        if(instance == null) {
            instance = new Robot();
            
        }
       
        return instance;
    }

    public void handle(){
        elevController.handle();
        elev.handle();
        dBase.handle();
    }
}
