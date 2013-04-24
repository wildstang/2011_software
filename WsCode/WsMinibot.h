#if !defined(_WSMINIBOT_H)
#define _WSMINIBOT_H

#include <stdio.h>

class DoubleSolenoid;

#define OUTPUT_DEPLOY_OFF  DoubleSolenoid::kOff
#define OUTPUT_DEPLOY_IN   DoubleSolenoid::kForward
#define OUTPUT_DEPLOY_OUT  DoubleSolenoid::kReverse

class WsMinibot
{
public:

    typedef enum
    {
        DEPLOY_STATE_NONE,
        DEPLOY_STATE_IN,
        DEPLOY_STATE_OUT,
    } DeployStateT;

    WsMinibot(UINT32 deployFwdChannel,
              UINT32 deployRevChannel);
    ~WsMinibot();

    void reset();
    void setDeployState(WsMinibot::DeployStateT state);

private:
    DoubleSolenoid* ap_dsolDeploy;
};

#endif  //_WSMINIBOT_H
