//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : WsArm.cpp
//  @ Date : 1/22/2011
//  @ Author : 
//
//


#include "WsArm.h"
#include "WPILib.h"
#include "WsPid.h"
#include "WsUtils.h"

#define DEBUG_ARM_PID 0

WsArm::WsArm(UINT32 arm1_sc, UINT32 arm2_sc, UINT32 pot) {
    ap_arm1 = new Victor(arm1_sc);
    ap_arm2 = new Victor(arm2_sc);
    ap_pot = new AnalogChannel(pot);
    ap_calib = WsCalibration::getInstance();

    if(ap_calib->isCompetitionRobot() == true)
    {
        ap_pid = new WsPid(.025, .001, 0, 3, 3);
    }
    else
    {
        //ap_pid = new WsPid(.015, .001, .001, 3, 3);
        ap_pid = new WsPid(.011, .001, .001, 3, 3);
    }


    a_cachedSetpoint = 0;
    a_cachedArmInPosition = false;
    a_cachedArmAngle = 0;
    a_cachedArmInPositionCount = 0;
}

WsArm::~WsArm() {
    delete ap_arm1;
    ap_arm1 = NULL;

    delete ap_arm2;
    ap_arm2 = NULL;

    delete ap_pot;
    ap_pot = NULL;

    delete ap_pid;
    ap_pid = NULL;

}

void WsArm::setSpeed(float speed, bool automated, bool overrideLimits) {

    INT32 botValue = (INT32)ap_calib->getValue(WsCalibration::ARM_BOTTOM);
    INT32 topValue = (INT32)ap_calib->getValue(WsCalibration::ARM_90_DEG);
    float outSpeed = 0;
    INT32 potValue = (INT32)ap_pot->GetAverageValue();

    if( (overrideLimits == false) &&
        ((speed >= 0 && potValue >= topValue) ||
        (speed <= 0 && potValue <= botValue)))
    {
        speed = 0;
    }

    //printf( "o: %d s: %f p: %d t: %d ", overrideLimits, speed, potValue, topValue);

    outSpeed = speed;

    if(automated == false)
    {
        a_cachedArmInPosition = (outSpeed == 0);
        a_cachedArmInPositionCount = 0;
        a_cachedSetpoint = 0;
    }
    else
    {
        if(outSpeed == 0)
        {
            a_cachedArmInPositionCount++;
        }
        else
        {
            a_cachedArmInPositionCount = 0;
        }

        if(a_cachedArmInPositionCount > ARM_IN_POSITION_COUNT)
        {
            a_cachedArmInPositionCount = ARM_IN_POSITION_COUNT;
        }

        a_cachedArmInPosition = (a_cachedArmInPositionCount >= ARM_IN_POSITION_COUNT);
    }



    a_cachedArmAngle = getAngleFromPot(potValue);
    //printf("ANGLE %f\n", a_cachedArmAngle);

    ap_arm1->Set(outSpeed);
    ap_arm2->Set(outSpeed);

}

void WsArm::setAngle(float angle) {
    INT32 setPoint;
    float speed;
    INT32 currentPosition = getPotValue();

    setPoint = (int)(ap_calib->getValue(WsCalibration::ARM_0_DEG) +
                    ((angle * (ap_calib->getValue(WsCalibration::ARM_90_DEG) -
                    ap_calib->getValue(WsCalibration::ARM_0_DEG))) / 90.0));

#if 0
    if(currentPosition < setPoint)
    {
        ap_pid->setMaxOutput(1);
    }
    else
    {
        ap_pid->setMaxOutput(.75);
    }
#else
        ap_pid->setMaxOutput(1);
#endif

    speed = ap_pid->calcPid(currentPosition, setPoint);
#if DEBUG_ARM_PID
    printf("DONE %d DES %3d  CURR %3d  SPEED %3f\n", a_cachedArmInPosition, setPoint, currentPosition, speed);
#endif


    if(speed < .001 && speed > -.001)
    {
        speed = 0;
    }

    setSpeed(speed, true, false);

    a_cachedSetpoint = setPoint;

}

INT32 WsArm::getPotValue(void ) {
    return ap_pot->GetAverageValue();
}


float WsArm::getAngleFromPot(INT32 potValue)
{
    float angle = 0;

    angle = 90 * (potValue - (INT32)ap_calib->getValue(WsCalibration::ARM_0_DEG)) /
            (float)(ap_calib->getValue(WsCalibration::ARM_90_DEG) - ap_calib->getValue(WsCalibration::ARM_0_DEG));
    
    /*
    printf("%d %d %d %f\n", potValue, 
            ap_calib->getValue(WsCalibration::ARM_0_DEG),
            ap_calib->getValue(WsCalibration::ARM_90_DEG),
            angle);
            */
            

    return angle;
}

bool WsArm::isInPosition(void)
{
    return a_cachedArmInPosition;
}

void WsArm::reset(void)
{
    a_cachedSetpoint = 0;
    a_cachedArmInPosition = false;
    a_cachedArmAngle = 0;
    setSpeed(0, false, false);
    resetErrorSum();
}

void WsArm::resetErrorSum(void)
{
    ap_pid->resetErrorSum();
}


INT32 WsArm::dashGetArmSetpoint(void)
{
    return a_cachedSetpoint;
}

bool WsArm::dashGetArmInPosition(void)
{
    return isInPosition();
}

float WsArm::dashGetArmAngle(void)
{
    return a_cachedArmAngle;
}

INT32 WsArm::dashGetArmPot(void)
{
    return getPotValue();
}


