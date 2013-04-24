#if !defined(_WSENCODER_H)
#define _WSENCODER_H

#include <stdio.h>

#include "Encoder.h"

class WsEncoder : public Encoder {
public:
    typedef enum
    {
        DIR_FWD,
        DIR_REV
    } DirectionT;

    WsEncoder(UINT32 aChannel, UINT32 bChannel,
              bool reverseDirection=false, EncodingType encodingType = k4X);
    virtual ~WsEncoder();

    void setDirection(DirectionT direction);

    INT32 Get();
    float GetDistance();
    void Reset();

    INT32 getAbsCount();
    INT32 getRelCount();

    float getAbsDistance();
    float getRelDistance();

    void resetAbsCount();
    void resetRelCount();

    void resetAbsDistance();
    void resetRelDistance();


protected:
    INT32 a_relStart;
    float a_relDistStart;
    DirectionT a_direction;
};

#endif  //_WSENCODER_H
