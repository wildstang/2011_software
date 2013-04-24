/*
 * ControlMap Interface
 *
 * This interface defines how a driver can operate this robot 
 */
package edu.neu.nutrons.bots.logomotion;

/**
 *
 * @author Nutrons Programming Team (Student: Ziv Scully and Mentor: Tom Bottiglieri)
 */
public interface ControlMap {

    public boolean getHomeBtn();
    public boolean getLowBtn();
    public boolean getMidBtn();
    public boolean getHighBtn();
    public boolean getShiftBtn();
    public boolean getFloorBtn();
    public boolean getCapBtn();
    public boolean getHumanBtn();
    public double getThrottle();
    public double getSpin();
    public boolean getHighGear();
    public boolean getLowGear();
    public boolean getQuickTurn();
    public boolean wantManualOveride();
    public double getElevatorAdjustment();
    public double getElevatorThrottle();
    public double getClawSpeed();
    public boolean getClawIn();
    public boolean getClawOut();
    public boolean getWrist();
    public boolean getMiniwrist();
    public boolean getMinibotDeploy();
    public boolean getMinibotLaunch();

}
