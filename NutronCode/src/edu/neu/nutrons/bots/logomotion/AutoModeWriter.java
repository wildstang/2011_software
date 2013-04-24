/*
 * AutoModeWriter
 *
 * This class is the one that does the heavy lifting for the autonomous routines
 * they are hard coded in this and pushed into the controller based on which options
 * the drivers select
 */
package edu.neu.nutrons.bots.logomotion;

import edu.neu.nutrons.bots.logomotion.autocmd.*;
import edu.neu.nutrons.bots.logomotion.elevator.Elevator;
import edu.neu.nutrons.lib.AutoModeController;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class AutoModeWriter {

    public class MainFunctions {

        public final static int amtMainFunctions = 1;
        public final static int DO_NOTHING = 0;
        public final static int SCORE_UBERTUBE = 1;
    }

    public class SecondFunctions {

        public final static int amtSecondFuntions = 3;
        public final static int DO_NOTHING = 0;
        public final static int GO_TO_MIDFIELD = 1;
        public final static int SCORE_SECOND_UBERTUBE = 2;
        public final static int SCORE_SECOND_UBERTUBE_ALT = 3;
        public final static int SCORE_SECOND_UBERTUBE_HIGH_ROLLING = 4;
    }

    public static AutoModeController getAC(int mainAction, int secondAction, boolean leftSide, boolean middlePeg, double height) {
        AutoModeController ac = new AutoModeController();
        ac.flush();
        int sign = leftSide ? 1 : -1;
        double firstAngle = middlePeg ? 163 : 163; // Will be sharper angle for middle, needs measurement
        double secondAngle = middlePeg ? 150 : 150; // Ditto

        //double doubleAngle = 38.76; // This needs to be tuned
        double angleLeft1 = 39.76;
        double angleLeft2 = 35.76;
        double angleRight1 = 39.76;
        double angleRight2 = 35.76;
        boolean twoLanesOverAlt = false; //one lane over for alt

        switch(mainAction) {
            case MainFunctions.SCORE_UBERTUBE:
              
                // This will drive and raise elevator at 1.5s in
                ac.addCommand(
                        new DoubleCommand(
                        new DriveDistanceCommand(16.8, .83, 8.0), // amount to drive
                        .3, //seconds until elevator
                        new SignalElevatorPosCommand(height + (middlePeg ? Elevator.OFFSET_AMT : 0))));

                ac.addCommand(new WaitCommand(.7));
                ac.addCommand(new CapTubeCommand());
                ac.addCommand(new WaitCommand(.15));
                break;
            case MainFunctions.DO_NOTHING:
            // Intentional fall through
            default:
                break;
        }

        switch(secondAction) {
            case SecondFunctions.GO_TO_MIDFIELD:
                ac.addCommand(new DriveDistanceCommand(-5, 1));
                ac.addCommand(new SignalElevatorPosCommand(Elevator.HEIGHT_HOME));
                ac.addCommand(new WaitCommand(.75));
                ac.addCommand(new TurnDegreesCommand(sign * 160, 1, 3));
                break;

            // Tom changed this one on 4/4. Should work like 1114. Props to them.
            case SecondFunctions.SCORE_SECOND_UBERTUBE:
                ac.setTimeoutCommand(new ReleaseTubeCommand(), 14.6); // at 14.6, spit out tube no matter what

                // Back up
                ac.addCommand(new ShiftHighCommand());
                ac.addCommand(
                        new DoubleCommand(
                        new DriveDistanceCommand(-9.25, .9),
                        0.5,
                        new SignalFloorPickupCommand()));
                ac.addCommand(new SignalFloorPickupCommand());
                ac.addCommand(new ShiftLowCommand());
                // Drop claw, turn
                ac.addCommand(new SignalFloorPickupCommand()); // start pickup
                ac.addCommand(new TurnUntilThresholdCommand(-sign * 127.0, 1, 2.5));

                // Drive Forward
                ac.addCommand(new DriveDistanceCommand(1.0, 2.0, 10));
                ac.addCommand(new DriveDistanceCommand(-1.0, 2.0, 10));
                ac.addCommand(new EndFloorPickupCommand()); // end pickup

                // Turn Back to absolute heading pointing at wall
                ac.addCommand(new TurnToHeadingCommand(-sign * 24.0, 1.0, 10));

                // If no tube, die
                ac.addCommand(new DieOnNoTubeCommand()); // dont try if we miss...
                // ac.addCommand(new WaitCommand(10000)); //TODO: move this around to make things work!
                // Drive at wall
                ac.addCommand(new ShiftHighCommand());
                ac.addCommand(
                        new DoubleCommand(
                        new DriveDistanceAndCoastCommand(9.0, .9, 3.0),
                        0.1,
                        new SignalElevatorPosCommand(height)));

                // Turn to face peg
                ac.addCommand(new ShiftLowCommand());
                ac.addCommand(new TurnToHeadingCommand(-sign * 5.0, 1.0, 10));

                // Drive at peg
                ac.addCommand(new DriveDistanceAndCoastCommand(4.0, 1.0, .4)); // Change this to ultrasonic?

                // Cap
                ac.addCommand(new CapTubeCommand());

                // Back away
                ac.addCommand(
                        new DoubleCommand(
                        new DriveDistanceCommand(-4, .9),
                        0.75,
                        new ElevatorGoHomeCommand()));
                ac.addCommand(new TurnUntilThresholdCommand(-sign * 60, 1, 2.5));
                ac.addCommand(new DriveDistanceCommand(-7, 1, 2.5));

                break;

            case SecondFunctions.SCORE_SECOND_UBERTUBE_ALT: // 148 method of scoring
                ac.setTimeoutCommand(new ReleaseTubeCommand(), 14.6); // at 14.6, spit out tube no matter what
                ac.addCommand(
                        new DoubleCommand(
                        new DriveDistanceCommand(-16.5, .9), // 3/18: -16.5, .9
                        1.5,
                        new ElevatorGoHomeCommand()));
                ac.addCommand(new SignalFloorPickupCommand()); // start pickup
                ac.addCommand(new TurnDegreesCommand(sign * (leftSide ? angleLeft1 : angleRight1), 1.0, 2.0));
                ac.addCommand(new DriveDistanceCommand(4.1, 0.75, 3.0)); // 3/18: 3.9
                ac.addCommand(new EndFloorPickupCommand()); // end pickup
                ac.addCommand(new TurnDegreesCommand(-1 * sign * (leftSide ? angleLeft1 : angleRight2), 1.0, 2.0));
                // If no tube, die
                ac.addCommand(new DieOnNoTubeCommand()); // dont try if we miss...
                ac.addCommand(
                        new DoubleCommand(
                        new DriveDistanceFastAndCoastCommand(15, .95, 5.0), // 3/18: 17.5, .9
                        .5,
                        //new SignalElevatorPosCommand(height + +((!middlePeg && !twoLanesOverAlt) ? Elevator.OFFSET_AMT : 0)))
                        // if we didnt originally score on the middle peg, this is the middle peg
                        new SignalElevatorPosCommand(height)));
                ac.addCommand(new CapTubeCommand());
                ac.addCommand(new ShiftLowCommand());
                ac.addCommand(new DriveDistanceAndCoastCommand(-3.0, 1, 5));
                ac.addCommand(new ElevatorGoHomeCommand());
                ac.addCommand(new DriveDistanceAndCoastCommand(-4.0, 1, 5));
                break;

            case SecondFunctions.SCORE_SECOND_UBERTUBE_HIGH_ROLLING: // Actually only very slightly like 987
                ac.setTimeoutCommand(new ReleaseTubeCommand(), 14.6); // at 14.6, spit out tube no matter what
                ac.addCommand(
                        new DoubleCommand(
                        new DriveDistanceCommand(-10.5, .9, 5.0),
                        .5,
                        new SignalElevatorStartFloorCommand()));
                ac.addCommand(new TurnDegreesCommand(sign * 40, 1, 3.0));
                ac.addCommand(new DriveDistanceCommand(-4.5, .9, 5.0));
                ac.addCommand(new TurnDegreesCommand(sign * 300, 1, 5.0)); // spins around and snatches tube, wherever it happens to be
                ac.addCommand(new WaitCommand(.3));
                ac.addCommand(new SignalElevatorEndFloorCommand());
                ac.addCommand(new DieOnNoTubeCommand()); // dont try if we miss...
                ac.addCommand(new ArcTurnUntilThresholdCommand(sign * 35, 1, .5, 7.0));
                ac.addCommand(
                        new DoubleCommand(
                        new DriveDistanceAndCoastCommand(8, 1, 5),
                        .3,
                        new ShiftHighCommand()));
                // timeout scores tube
                break;

            case SecondFunctions.DO_NOTHING:
            // Intentional fall through
            default:
                break;
        }
        return ac;
    }
}
