/*
 * AutoModeSelectionController
 *
 * This class reads from a control board UI
 * and configures the autonomous mode selector
 */

package edu.neu.nutrons.bots.logomotion;

import edu.neu.nutrons.lib.AutoModeController;
import edu.neu.nutrons.lib.PulseTriggerBoolean;
import edu.wpi.first.wpilibj.Timer;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class AutoModeSelectionController {
    PulseTriggerBoolean toggleLR = new PulseTriggerBoolean();
    PulseTriggerBoolean togglePeg = new PulseTriggerBoolean();
    PulseTriggerBoolean toggleMain = new PulseTriggerBoolean();
    PulseTriggerBoolean toggleSecond = new PulseTriggerBoolean();
    ControlMap cb = ControlBoard.getInstance();
    AutoModeSelector ams = new AutoModeSelector();
    Timer t = new Timer();

    public AutoModeSelectionController(){
        t.start();
    }

    public void handle(){
        // Mapping
        toggleLR.set(cb.getHighBtn());
        togglePeg.set(cb.getMidBtn());
        toggleMain.set(cb.getLowBtn());
        toggleSecond.set(cb.getFloorBtn());

        // Do things
        if(toggleLR.get()){
            ams.toggleLR();
        }

        if(togglePeg.get()){
            ams.togglePeg();
        }

        if(toggleMain.get()){
            ams.incrementMain();
        }

        if(toggleSecond.get()){
            ams.incrementSecondary();
        }

        if(t.get() > 1.0 ){
            t.reset();
            ams.updateScreen();
        }


    }

    public AutoModeController getAC(){
        return ams.getAC();
    }

}
