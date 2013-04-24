/*
 * ElevatorCappingCommand
 *
 * Cap a tube
 */
package edu.neu.nutrons.bots.logomotion.elevator.cmd;

import edu.neu.nutrons.bots.logomotion.elevator.Elevator;
import edu.wpi.first.wpilibj.Timer;

/**
 *
 * @author Tom
 */
public class ElevatorCappingCommand extends ElevatorCommand {

    // Note: I think we need to redo the logic, as it's changing a lot for the roller claw
    Timer t = new Timer();
    boolean firstRun = true;
    boolean needToGoDown = true;
    public static final double CAP_ELEV_TIME_DELAY = .0;
    public static final double TIME_TO_CAP = .193;

    public ElevatorCappingCommand(double pos, boolean wrist, boolean miniwrist) {
        super(pos, wrist, miniwrist);
    }

    public double calcSpeed(double realPos) {
        if(firstRun) {
            firstRun = false;
            t.start();
        }
        /* if(t.get() > CAP_ELEV_TIME_DELAY && needToGoDown) {
            this.pos = realPos - Elevator.SCORING_DROP;
            needToGoDown = false;
        }
        return super.calcSpeed(realPos); */
        double speed = 0;
        if(t.get() < TIME_TO_CAP){
            speed = -.31;
        }
        else {
            if(needToGoDown) {
                needToGoDown = false;
                this.pos = realPos;
            }
            speed = super.calcSpeed(this.pos);
        }
        return speed;
    }

    public boolean getWrist() {
        return false;
    }

    public boolean getMiniwrist() {
        return false;
    }
}
