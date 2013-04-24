/*
 * AutoModeSelector
 *
 * This class handles the selection of a pre-defined
 * autonomous operation mode for the match
 */

package edu.neu.nutrons.bots.logomotion;

import edu.neu.nutrons.bots.logomotion.elevator.Elevator;
import edu.neu.nutrons.lib.AutoModeController;
import edu.wpi.first.wpilibj.DriverStationLCD;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public class AutoModeSelector {
    final double DEFAULT_HEIGHT = Elevator.HEIGHT_HIGH;
    boolean leftSide = false;
    int main = AutoModeWriter.MainFunctions.SCORE_UBERTUBE;
    boolean middlePeg = false;
    int second = AutoModeWriter.SecondFunctions.SCORE_SECOND_UBERTUBE;
    
    public AutoModeController getAC(){
        return AutoModeWriter.getAC(main, second, leftSide, middlePeg, DEFAULT_HEIGHT);
    }

    public void toggleLR(){
        leftSide = !leftSide;
        updateScreen();
    }

    public void togglePeg(){
        middlePeg = !middlePeg;
        updateScreen();
    }

    public void incrementMain(){
        main++;
        if(main > AutoModeWriter.MainFunctions.amtMainFunctions){
            main = 0;
        }
        updateScreen();
    }

    public void incrementSecondary(){
        second++;
        if(second > AutoModeWriter.SecondFunctions.amtSecondFuntions){
            second = 0;
        }
        updateScreen();
    }

    public void updateScreen(){
        DriverStationLCD lcd = DriverStationLCD.getInstance();
        String firstLine = "Side: ";
        String secondLine = "1st Peg: ";
        String thirdLine = "Main: ";
        String fourthLine = "2nd: ";
        
        // Sides
        if(leftSide){
            firstLine = firstLine + "L";
        }
        else{
            firstLine = firstLine + "R";
        }

        //Pegs {
        if(middlePeg){
            secondLine = secondLine + "Regular";
        }
        else{
            secondLine = secondLine + "Shifted";
        }

        //  Main Functions
        switch(main){
            case AutoModeWriter.MainFunctions.SCORE_UBERTUBE:
                thirdLine = thirdLine + "Score Tube";
                break;
            case AutoModeWriter.MainFunctions.DO_NOTHING:
                main = AutoModeWriter.MainFunctions.DO_NOTHING;
                thirdLine = thirdLine + "Nothing";
                break;
            default:
                main = AutoModeWriter.MainFunctions.DO_NOTHING;
                thirdLine = thirdLine + "Nothing";
        }


        switch(second){
            case AutoModeWriter.SecondFunctions.SCORE_SECOND_UBERTUBE:
                fourthLine = fourthLine + "Score 2 (111)";
                break;
             case AutoModeWriter.SecondFunctions.SCORE_SECOND_UBERTUBE_ALT:
                 fourthLine = fourthLine + "Score 2 (33)";
                 break;
            case AutoModeWriter.SecondFunctions.GO_TO_MIDFIELD:
                fourthLine = fourthLine + "Go to middle";
                break;
            case AutoModeWriter.SecondFunctions.DO_NOTHING:
                // intentional fall through!
            default:
                second = AutoModeWriter.SecondFunctions.DO_NOTHING;
                fourthLine = fourthLine + "Nothing";
        }

        firstLine = firstLine + "           ";
        secondLine = secondLine + "           ";
        thirdLine = thirdLine + "           ";
        fourthLine = fourthLine + "           ";

        lcd.println(DriverStationLCD.Line.kUser2, 1, firstLine);
        lcd.println(DriverStationLCD.Line.kUser3, 1, secondLine);
        lcd.println(DriverStationLCD.Line.kUser4, 1, thirdLine);
        lcd.println(DriverStationLCD.Line.kUser5, 1, fourthLine);

        lcd.updateLCD();
    }
}
