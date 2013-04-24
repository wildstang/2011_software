#include "WsEncoder.h"

WsEncoder::WsEncoder(UINT32 aChannel, UINT32 bChannel, bool reverseDirection, EncodingType encodingType)
: Encoder(aChannel, bChannel, reverseDirection, encodingType)
{
    resetAbsCount();
    resetAbsDistance();
    a_direction = DIR_FWD;
}

WsEncoder::~WsEncoder()
{

}

void WsEncoder::setDirection(DirectionT direction)
{
    a_direction = direction;
}

INT32 WsEncoder::Get(void)
{
    return getAbsCount();
}

float WsEncoder::GetDistance(void)
{
    return getAbsDistance();
}

void WsEncoder::Reset(void)
{
    resetAbsCount();
    resetAbsDistance();
}

INT32 WsEncoder::getAbsCount(void)
{
    INT32 count;

    count = Encoder::Get();

    if(a_direction == DIR_REV)
    {
        count *= -1;
    }

    return count;
}

float WsEncoder::getAbsDistance(void)
{
    float dist;

    dist = (float)Encoder::GetDistance();

    if(a_direction == DIR_REV)
    {
        dist *= -1;
    }

    return dist;
}

INT32 WsEncoder::getRelCount(void)
{
    INT32 count;

    count = getAbsCount() - a_relStart;

    return count;
}

float WsEncoder::getRelDistance(void)
{
    float dist;

    dist = getAbsDistance() - a_relDistStart;

    return dist;
}


void WsEncoder::resetAbsCount(void)
{
    Encoder::Reset();
    resetRelCount();
}

void WsEncoder::resetAbsDistance(void)
{
    resetRelDistance();
}

void WsEncoder::resetRelCount(void)
{
    a_relStart = getAbsCount();
}

void WsEncoder::resetRelDistance(void)
{
    a_relDistStart = getAbsDistance();
}


