//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : WsLift.cpp
//  @ Date : 1/22/2011
//  @ Author : 
//
//


#include "WsLift.h"
#include "WsEncoderPot.h"
#include "WsPid.h"
#include "WsCalibration.h"

#define DEBUG_LIFT_PID 0

WsLift::WsLift(UINT32 sc_1, UINT32 sc_2, UINT32 encoder_a, UINT32 encoder_b, UINT32 bottom_sw, UINT32 top_sw) {
    ap_sc1 = new Victor(sc_1);
    ap_sc2 = new Victor(sc_2);
    ap_encPot = new WsEncoderPot(encoder_a, encoder_b, bottom_sw, top_sw);
    ap_calib = WsCalibration::getInstance();

    if(ap_calib->isCompetitionRobot() == true)
    {
        ap_upPID = new WsPid(.0120, .004, .003, 3, 10);
        ap_upPID->setMaxIntegral(.5);
        ap_downPID = new WsPid(.05, 0, .02, 3, 10);
        ap_downPID->setIntegralErrorThresh(100);
        ap_downPID->setMaxIntegral(.5);
        //ap_downPID->setMaxOutput(.5);
        ap_downPID->setMaxOutput(.3);
        a_limitLiftSpeed = .4;
    }
    else
    {
        ap_upPID = new WsPid(.0070, .0045, 0, 5, 12);
        //ap_downPID = new WsPid(.01, .003, .007, 3, 10);
        //ap_downPID = new WsPid(.002, .00065, .0015, 3, 5);
        ap_downPID = new WsPid(.0013, .003, .001, 3, 4);
        ap_downPID->setMaxIntegral(.5);
        ap_downPID->setIntegralErrorThresh(100);
        ap_downPID->setMaxOutput(.3);
        a_limitLiftSpeed = .4;
    }

    ap_currentPID = ap_upPID;
    ap_otherPID = ap_downPID;
    a_cachedSetpoint = 0;
    a_cachedLiftInPosition = false;
    a_cachedLiftInPositionCount = 0;
    a_cachedEncoderValue = 0;
    a_latchTopOverrun = false;
    a_currentSetpoint = UNINIT_SETPOINT;
}

WsLift::~WsLift() {
    delete ap_sc1;
    ap_sc1 = NULL;

    delete ap_sc2;
    ap_sc2 = NULL;

    delete ap_encPot;
    ap_encPot = NULL;

    delete ap_upPID;
    ap_upPID = NULL;

    delete ap_downPID;
    ap_downPID = NULL;
}

void WsLift::setSpeed(float speed, bool automated, bool overrideLimits) {
    float outSpeed = 0;
    float coastSpeed = 0; // Speed to drive BB motor at
    a_cachedEncoderValue = ap_encPot->getValue();
    bool atTop = ap_encPot->isAtTop();
    bool atBot = ap_encPot->isAtBottom();

    if(overrideLimits == true)
    {
        atTop = false;
        atBot = false;
    }

    if((speed >= 0) && (atTop == false) && (a_latchTopOverrun == false))
    {
        outSpeed = speed;
    }
    else if((speed < 0) && (atBot == false))
    {
        outSpeed = speed;
        a_latchTopOverrun = false;
    }
    else
    {
        if(overrideLimits == false)
        {
            outSpeed = 0;
            if(atTop == true)
            {
                a_latchTopOverrun = true;
            }
            if( atBot == true )
            {
                a_latchTopOverrun = false;
            }
        }
    }

    if(automated == false)
    {
        a_cachedLiftInPosition = (outSpeed == 0);
        a_cachedLiftInPositionCount = 0;
        a_cachedSetpoint = 0;
        a_currentSetpoint = UNINIT_SETPOINT;
    }
    else
    {
        if(outSpeed == 0)
        {
            a_cachedLiftInPositionCount++;
        }
        else
        {
            a_cachedLiftInPositionCount = 0;
        }

        if(a_cachedLiftInPositionCount > LIFT_IN_POSITION_COUNT)
        {
            a_cachedLiftInPositionCount = LIFT_IN_POSITION_COUNT;
        }

        a_cachedLiftInPosition = (a_cachedLiftInPositionCount >= LIFT_IN_POSITION_COUNT);
    }

    coastSpeed = outSpeed;


    if(automated == false && outSpeed < 0)
    {
        if(overrideLimits == false)
        {
            // Scale this based on lift height
            outSpeed *= a_limitLiftSpeed;
        }
        else
        {
            outSpeed *= a_limitLiftSpeed;
        }
        // This overcomes brake mode
        if(outSpeed < -.1)
        {
            coastSpeed = -.1;
        }
        /*
        coastSpeed = 0;
        */
    }
    else
    {
        //outSpeed *= .75;
        //coastSpeed *= .75;
    }


    outSpeed *= -1;
    coastSpeed *= -1;

    ap_sc1->Set(outSpeed);
    ap_sc2->Set(coastSpeed);

    //printf( "OUT:%0.3f, COAST:%0.3f \n", outSpeed, coastSpeed );
}

void WsLift::setHeight(INT32 height) {

    float outSpeed = 0;

    INT32 currentHeight = getEncoderValue();

    //printf("LIFT(%d, %d) ", a_currentSetpoint, height);
    if(a_currentSetpoint != height)
    {
        if((height - currentHeight) >= 0 )
        {
            ap_currentPID = ap_upPID;
            ap_otherPID = ap_downPID;
        }
        else
        {
            ap_currentPID = ap_downPID;
            ap_otherPID = ap_upPID;
        }
        a_currentSetpoint = height;
    }

    //printf("%s ", (ap_currentPID == ap_upPID) ? "UP" : "DOWN");

    outSpeed = ap_currentPID->calcPid(currentHeight, height);
    ap_otherPID->resetErrorSum();

    setSpeed(outSpeed, true, false);

    a_cachedSetpoint = height;
    
#if DEBUG_LIFT_PID
    printf("DONE %d SET %d CURR %d  DES %d SP %f\n", a_cachedLiftInPosition, a_cachedSetpoint, currentHeight, height, outSpeed);
#endif
}


INT32 WsLift::getEncoderValue(void ) {
    return a_cachedEncoderValue;
}

bool WsLift::isEncoderInitialized(void ) {
    return ap_encPot->isInitialized();
}

bool WsLift::isInPosition(void)
{
    return a_cachedLiftInPosition;
}

void WsLift::reset(void)
{
    a_cachedSetpoint = 0;
    a_cachedLiftInPosition = false;
    a_cachedEncoderValue = 0;
    setSpeed(0, false, false);
    resetErrorSum();
}


void WsLift::resetErrorSum(void)
{
    ap_upPID->resetErrorSum();
    ap_downPID->resetErrorSum();
}

bool WsLift::dashGetLiftInPosition(void)
{
    return isInPosition();
}

INT32 WsLift::dashGetLiftSetpoint(void)
{
    return a_cachedSetpoint;
}

bool WsLift::dashGetLiftSwBot(void)
{
    return ap_encPot->isAtBottom();
}

bool WsLift::dashGetLiftSwTop(void)
{
    return ap_encPot->isAtTop();
}
