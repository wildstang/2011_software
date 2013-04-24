#if !defined(_WSAUTOPROGRAMSCOREANGLE_H)
#define _WSAUTOPROGRAMSCOREANGLE_H

#include <stdio.h>
#include "WsAutoNStepBase.h"

class WsAutoProgramScoreAngle : public WsAutoNStepBase
{
    public:
        WsAutoProgramScoreAngle();
        virtual ~WsAutoProgramScoreAngle();
        virtual void initParams(void);
    protected:
        WsPid* ap_driveLowPID;
        WsPid* ap_driveHighPID;
        WsPid* ap_rotatePID;
};

#endif
