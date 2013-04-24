// Automated Roller claw controller

//
package edu.neu.nutrons.bots.logomotion.elevator;

import edu.neu.nutrons.lib.DebouncedDigitalInput;
import edu.neu.nutrons.lib.MotorMechanism;
import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.SmartDashboard;
import edu.wpi.first.wpilibj.Timer;

public class RollerClaw {

    final boolean TUBE_IN = false;
    final double RELEASE_TIME = 1.0;
    final double SCORE_TIME = 1.5;
    final double REAQUIRE_TIMEOUT = .75; // how long to try to hold on to it


    final int STATE_IDLE = 0;
    final int STATE_HAS_TUBE = 2;
    final int STATE_AQUIRE_TUBE = 1;
    final int STATE_RELEASE_TUBE = 3;
    final int STATE_SCORE_TUBE = 4;
    final int STATE_MANUAL = 5;


    public static final double SPEED_CLAW_IN = 1.0;
    public static final double SPEED_CLAW_SCORE = -0.60; // Tom is good at guessing
    public static final double SPEED_CLAW_RELEASE = -.65;

    int state = STATE_IDLE;
    MotorMechanism m;
    DigitalInput tubeSwitch;
    Timer t = new Timer();
    Timer tL = new Timer();
    boolean startRelease = false;
    private boolean startScore = false;
    private boolean losingTube = false;

    private double manualSpeed = 0;

    public RollerClaw(int motorChannel, int switchChannel) {
        m = new RollerClawMotorMechanism(motorChannel);
        tubeSwitch = new DebouncedDigitalInput(switchChannel, .125, false);
    }

    public void handle() {
        double speed = 0;
        SmartDashboard.log(state, "roller claw state");

        switch (state) {
            case STATE_IDLE:
                startRelease = false;
                startScore = false;
                losingTube = false;
                break;
            case STATE_AQUIRE_TUBE:
                // run rollers in until thing is hit
                speed = SPEED_CLAW_IN;
                if (tubeSwitch.get() == TUBE_IN) {
                    state = STATE_HAS_TUBE;
                    speed = 0;
                }
                break;
            case STATE_HAS_TUBE:
                if (tubeSwitch.get() != TUBE_IN) {
                    if (!losingTube) {
                        tL.reset();
                        tL.start();
                        losingTube = true;
                    }

                    if (losingTube && tL.get() > REAQUIRE_TIMEOUT) {
                        state = STATE_IDLE;
                    }
                    speed = SPEED_CLAW_IN;
                } else {
                    tL.stop();
                    losingTube = false;
                }
                break;

            case STATE_SCORE_TUBE:
                speed = SPEED_CLAW_SCORE;
                if (startScore) {
                    t.reset();
                    t.start();
                    startScore = false;
                }
                if (t.get() > SCORE_TIME) {
                    state = STATE_IDLE;
                    speed = 0;
                }
                break;

            case STATE_RELEASE_TUBE:
                speed = SPEED_CLAW_RELEASE;
                if (startRelease) {
                    t.reset();
                    t.start();
                    startRelease = false;
                }
                if (t.get() > RELEASE_TIME) {
                    state = STATE_IDLE;
                    speed = 0;

                }
                break;

            case STATE_MANUAL:
                speed = manualSpeed;
                break;
            default :
                state = STATE_IDLE;
        }

        m.set(speed);

        SmartDashboard.log(tubeSwitch.get(), "Tube Switch");

    }

    public boolean hasTube() {
        return tubeSwitch.get() == TUBE_IN;
    }

    public void goIdle() {
        state = STATE_IDLE;
    }

    public void aquireTube() {
        state = STATE_AQUIRE_TUBE;
    }

    public void releaseTube() {
        
            state = STATE_RELEASE_TUBE;
            startRelease = true;
        
    }

    public void scoreTube() {
       
            state = STATE_SCORE_TUBE;
            startScore = true;
        
    }

    public void manualDrive(double speed){
        manualSpeed = speed;
        state = STATE_MANUAL;
    }

    public void stopAquiringTube(){
        if(state == STATE_AQUIRE_TUBE){
            state = STATE_IDLE;
        }
    }
}
