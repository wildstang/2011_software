#if !defined(_WSROBOTDECAPROTO_H)
#define _WSROBOTDECAPROTO_H

#include "WPILib.h"
#include "Gamepad.h"
#include "WsButton.h"
#include "WsControlMethodDeca.h"
#include "WsDriveBase6WD.h"
#include "WsDriveBaseDeca.h"

class WsRobotDecaProto : public IterativeRobot
{
    public:
        WsRobotDecaProto(void);

        /********************************** Init Routines *************************************/

        void RobotInit(void);
        void DisabledInit(void);
        void AutonomousInit(void);
        void TeleopInit(void);

        /********************************** Periodic Routines *************************************/

        void DisabledPeriodic(void);
        void AutonomousPeriodic(void);
        void TeleopPeriodic(void);

        /********************************** Continuous Routines *************************************/

        void DisabledContinuous(void);
        void AutonomousContinuous(void);
        void TeleopContinuous(void);

    protected:
        /********************************** Inputs *************************************/

        Gamepad    *ap_driveGamepad;
        
        /********************************** Input Control Methods  *********************/
        
        WsControlMethodDeca *ap_driveBaseInput;
        
        /************************** Robot Side Sensor Inputs ***************************/

        /********************************** Outputs *************************************/

        SpeedController *ap_scDriveL1;
        SpeedController *ap_scDriveL2;
        SpeedController *ap_scDriveR1;
        SpeedController *ap_scDriveR2;
        
        SpeedController *ap_scDeca1;
        SpeedController *ap_scDeca2;
        
        Solenoid *ap_solDeca;
        
        /********************************** Output Objects  *********************/
        
        WsDriveBaseDeca *ap_driveBaseOutput;

        /********************************** Internal Variables *************************************/
        // Local variables to count the number of periodic loops performed
        UINT32 a_autoPeriodicLoops;
        UINT32 a_disabledPeriodicLoops;
        UINT32 a_telePeriodicLoops;
        
    private:
        ~WsRobotDecaProto(void);
};

START_ROBOT_CLASS(WsRobotDecaProto);

#endif  //_WSROBOTDECAPROTO_H

