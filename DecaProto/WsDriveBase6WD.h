#if !defined(_WSDRIVEBASE6WD_H)
#define _WSDRIVEBASE6WD_H

#include "WPILib.h"
#include "WsDriveVector.h"

class WsDriveBase6WD
{
    public:
        WsDriveBase6WD(void);
        virtual ~WsDriveBase6WD(void);
        
        virtual void assignControllers(SpeedController* scLeft1,
                                            SpeedController* scLeft2,
                                            SpeedController* scRight1,
                                            SpeedController* scRight2);
        
        virtual void setOutputs(WsDriveVector* p_driveVector);
                                
        
    protected:
        SpeedController* ap_scLeft1;
        SpeedController* ap_scLeft2;
        SpeedController* ap_scRight1;
        SpeedController* ap_scRight2;
        
    private:
};

#endif  //_WSDRIVEBASE6WD_H

