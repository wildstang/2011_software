#if !defined(_WSDRIVEBASEDECA_H)
#define _WSDRIVEBASEDECA_H

#include "WPILib.h"
#include "WsDriveVector.h"
#include "WsControlMethodDeca.h"
#include "WsDriveBase6WD.h"

class WsDriveBaseDeca : public WsDriveBase6WD
{
    public:
        WsDriveBaseDeca(void);
        virtual ~WsDriveBaseDeca(void);
        
        virtual void assignControllers(SpeedController* scLeft1,
                                       SpeedController* scLeft2,
                                       SpeedController* scRight1,
                                       SpeedController* scRight2,
                                       SpeedController* scDeca1,
                                       SpeedController* scDeca2,
                                       Solenoid* solDeca);
            
        virtual void setOutputs(WsDriveVector* p_driveVector,
                                WsDriveVector* p_decaVector,
                                WsControlMethodDeca::WsDecaStateT decaState);
                                    
        
    protected:
        SpeedController* ap_scDeca1;
        SpeedController* ap_scDeca2;
        Solenoid* ap_solDeca;
        
    private:
};

#endif  //_WSDRIVEBASEDECA_H

