#if !defined(_WSAUTOPROGRAMSCORESTRAIGHT_H)
#define _WSAUTOPROGRAMSCORESTRAIGHT_H

#include <stdio.h>
#include "WsAutoNStepBase.h"

class WsPid;

class WsAutoProgramScoreStraight : public WsAutoNStepBase
{
    public:
        WsAutoProgramScoreStraight();
        virtual ~WsAutoProgramScoreStraight();
        virtual void initParams(void);
    protected:
        WsPid* ap_driveLowPID;
        WsPid* ap_driveHighPID;
        WsPid* ap_rotatePID;
};

#endif
