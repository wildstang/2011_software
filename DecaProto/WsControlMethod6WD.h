#if !defined(_WSCONTROLMETHOD6WD_H)
#define _WSCONTROLMETHOD6WD_H

#include "WPILib.h"
#include "Gamepad.h"
#include "WsDriveVector.h"
#include "WsControllerPolarStick.h"

class WsControlMethod6WD
{
    public:
        WsControlMethod6WD(void);
        virtual ~WsControlMethod6WD(void);
        
        void assignInputs(Gamepad* gamepad, GenericHID::JoystickHand hand);
        void assignInputs(Gamepad* gamepad, Gamepad::AxisType driveAxis, Gamepad::AxisType turnAxis);
        
        virtual void readInputs(void);
        virtual void getDriveVector(WsDriveVector* driveVector);
        
        
    protected:
        WsControllerPolarStick* ap_polarStick;
        WsDriveVector* ap_driveVector;
        
    private:
};

#endif  //_WSCONTROLMETHOD6WD_H

