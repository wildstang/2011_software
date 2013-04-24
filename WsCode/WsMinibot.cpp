#include "WsMinibot.h"
#include "WPILib.h"

WsMinibot::WsMinibot(UINT32 deployFwdChannel,
                     UINT32 deployRevChannel)
{
    ap_dsolDeploy = new DoubleSolenoid(deployFwdChannel, deployRevChannel);
}

WsMinibot::~WsMinibot()
{
    delete ap_dsolDeploy;
    ap_dsolDeploy = NULL;
}


void WsMinibot::reset()
{
    ap_dsolDeploy->Set(DoubleSolenoid::kOff);
}

void WsMinibot::setDeployState(WsMinibot::DeployStateT state)
{
    DoubleSolenoid::Value output = OUTPUT_DEPLOY_OFF;
    switch(state)
    {
        case DEPLOY_STATE_IN:
            output = OUTPUT_DEPLOY_IN;
            break;
        case DEPLOY_STATE_OUT:
            output = OUTPUT_DEPLOY_OUT;
            break;
        default:
            output = OUTPUT_DEPLOY_OFF;
            break;
    }
    ap_dsolDeploy->Set(output);
}


