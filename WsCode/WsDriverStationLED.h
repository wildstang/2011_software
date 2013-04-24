/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef __WS_DRIVER_STATION_LED_H__
#define __WS_DRIVER_STATION_LED_H__

#include <stdio.h>

class DriverStation;
class Timer;

/**
 * Provide access to LED outputs on the Driver Station.
 *
 */
class WsDriverStationLED
{
public:
    WsDriverStationLED(UINT32 channel);
    ~WsDriverStationLED();
    void turnOn(void);
    void turnOff(void);
    void setState(bool state);
    bool getState();
    // Blink rate is in seconds
    void blink(double rate);
    void blinkNumber(UINT8 num);
protected:
    DriverStation* p_ds;
    UINT32 a_channel;
    Timer* ap_timer;
    bool a_blinking;
    bool a_blinkState;
    UINT8 a_blinkNumCount;
    bool a_state;
};

#endif
