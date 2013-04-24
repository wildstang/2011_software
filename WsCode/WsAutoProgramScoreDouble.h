#if !defined(_WSAUTOPROGRAMSCOREDOUBLE_H)
#define _WSAUTOPROGRAMSCOREDOUBLE_H

#include <stdio.h>
#include "WsAutoNStepBase.h"

class WsAutoProgramScoreDouble : public WsAutoNStepBase
{
    public:
        WsAutoProgramScoreDouble();
        virtual ~WsAutoProgramScoreDouble();
        virtual void initParams(void);
    protected:
        WsPid* ap_driveLowPID;
        WsPid* ap_driveHighPID;
        WsPid* ap_rotatePID;
};

#endif
