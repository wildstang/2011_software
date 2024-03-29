//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : WsLightSensor.cpp
//  @ Date : 12/14/2010
//  @ Author : 
//
//


#include "WsLightSensor.h"
#include "AnalogChannel.h"

/**
 * Construst an instance of a WsLightSensor
 *
 * @param slot The physical slot light sensor  is connected to
 * @param channel The analog channel that the light sensor is connected to
 */
WsLightSensor::WsLightSensor(UINT32 slot, UINT32 channel)
{
    a_analogChannel = new AnalogChannel(slot, channel);
}

/**
 * Construst an instance of a WsLightSensor
 *
 * @param channel The analog channel that the light sensor is connected to
 */
WsLightSensor::WsLightSensor(UINT32 channel)
{
    a_analogChannel = new AnalogChannel(channel);
}

/**
 * Destroys an instance of a WsLightSensor
 *
 */
WsLightSensor::~WsLightSensor()
{
    delete a_analogChannel;
    a_analogChannel = NULL;
}

/**
 * Sets the threshold that determines light and dark
 *
 * @param threshold The threshold that determines if a value is light or dark
 */
void WsLightSensor::SetThresholds(INT32 threshold)
{
    SetThresholds(threshold, threshold);
}

/**
 * Sets the threshold that determines light and dark
 *
 * @param lightThreshold The threshold that determines if a value is light
 * @param darkThreshold The threshold that determines if a value is dark
 */
void WsLightSensor::SetThresholds(INT32 lightThreshold, INT32 darkThreshold)
{
    a_lightThreshold = lightThreshold;
    a_darkThreshold = darkThreshold;
}


/**
 * Determines if the sensor is seeing a light value based on the lightThreshold
 *
 * @return True If the value read is below the light threshold
 * @return False If the value read is above the light threshold
 */
bool WsLightSensor::SeesLight(void )
{
    bool ret = false;

    if(Get() <= a_lightThreshold)
    {
        ret = true;
    }

    return ret;
}

/**
 * Determines if the sensor is seeing a dark value based on the darkThreshold
 *
 * @return True If the value read is above the dark threshold
 * @return False If the value read is below the dark threshold
 */
bool WsLightSensor::SeesDark(void )
{
    bool ret = false;

    if(Get() >= a_darkThreshold)
    {
        ret = true;
    }

    return ret;
}

/**
 * Reads the analog value of the sensor
 *
 * @return The analog value of the sensor
 */
INT32 WsLightSensor::Get(void )
{
    return a_analogChannel->GetAverageValue();   
}
