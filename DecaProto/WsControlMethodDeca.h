#if !defined(_WSCONTROLMETHODDECA_H)
#define _WSCONTROLMETHODDECA_H

#include "WPILib.h"
#include "WsControlMethod6WD.h"
#include "Gamepad.h"
#include "WsDriveVector.h"
#include "WsControllerPolarStick.h"
#include "WsButton.h"



class WsControlMethodDeca : public WsControlMethod6WD
{
    public:
        typedef enum
        {
            DECA_STATE_UP,
            DECA_STATE_DOWN
        } WsDecaStateT;
        
        WsControlMethodDeca(void);
        virtual ~WsControlMethodDeca(void);
        
        void assignInputs(Gamepad* gamepad,
                          Gamepad::AxisType driveAxis,
                          Gamepad::AxisType turnAxis,
                          Gamepad::ButtonType decaButton,
                          Gamepad::AxisType decaAxis);
        
        virtual void readInputs(void);
        void getDecaState(WsDecaStateT* decaState, WsDriveVector* decaVector);
        
    protected:
        Gamepad* ap_gamepad;
        WsButton* ap_decaButton;
        Gamepad::AxisType a_decaAxis;
        WsDriveVector* ap_decaVector;
        WsDecaStateT a_decaState;
        
    private:
};

#endif  //_WSCONTROLMETHODDECA_H

