#include "WsDriverStationLED.h"
#include "DriverStation.h"
#include "Timer.h"

WsDriverStationLED::WsDriverStationLED(UINT32 channel)
{
    p_ds = DriverStation::GetInstance();
    ap_timer = new Timer();
    a_channel = channel;
    a_blinking = false;
    a_blinkState = false;

    if(ap_timer != NULL)
    {
        ap_timer->Stop();
    }
}

WsDriverStationLED::~WsDriverStationLED()
{
    if(ap_timer != NULL)
    {
        delete ap_timer;
        ap_timer = NULL;
    }
}

void WsDriverStationLED::turnOn(void)
{
    if(ap_timer != NULL)
    {
        ap_timer->Stop();
        ap_timer->Reset();
    }
    a_blinking = false;
    setState(true);
}

void WsDriverStationLED::turnOff(void)
{
    if(ap_timer != NULL)
    {
        ap_timer->Stop();
        ap_timer->Reset();
    }
    a_blinking = false;
    setState(false);
}

void WsDriverStationLED::setState(bool state)
{
    if(p_ds != NULL)
    {
        p_ds->SetDigitalOut(a_channel, state);
    }
    a_state = state;
}

bool WsDriverStationLED::getState()
{
    return a_state;
}

void WsDriverStationLED::blink(double rate)
{
    // Toggle the LED state every 'rate' seconds
    double time;
    if (ap_timer != NULL)
    {
        if(a_blinking == false)
        {
            ap_timer->Reset();
            ap_timer->Start();
            a_blinkState = false;
            a_blinking = true;
        }

        time = ap_timer->Get();
        if(time >= rate)
        {
            a_blinkState = !a_blinkState;
            ap_timer->Reset();
        }
    }
    else
    {
        a_blinkState = false;
    }
    setState(a_blinkState);
}

void WsDriverStationLED::blinkNumber(UINT8 num)
{
    double time;
    static bool counting = false;

    if(ap_timer != NULL)
    {
        if(a_blinking == false)
        {
            ap_timer->Reset();
            ap_timer->Start();
            a_blinkState = false;
            a_blinking = true;
            a_blinkNumCount = 0;
            counting = false;
        }

        time = ap_timer->Get();

        if(counting == true)
        {
            if(time >= .25)
            {
                if(a_blinkNumCount >= num)
                {
                    counting = false;
                    a_blinkState = false;
                }
                else
                {
                    a_blinkState = !a_blinkState;
                    if(a_blinkState == true)
                    {
                        a_blinkNumCount++;
                    }
                }
                ap_timer->Reset();
            }
        }
        else
        {
            if(time >= 1)
            {
                counting = true;
                a_blinkNumCount = 0;
                ap_timer->Reset();
            }
            a_blinkState = false;
        }

    }
    else
    {
    }

    setState(a_blinkState);

}

