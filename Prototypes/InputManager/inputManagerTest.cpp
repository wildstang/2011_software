#include <stdio.h>
#include "stubs.h"
#include "InputManager.h"

using namespace std;

/********* BEGIN STUBS **************/
int BadJoystickAxis = 0;
void wpi_assert(bool b)
{
    printf("-- WPI ASSERT %d --\n", b);
}

void wpi_fatal(int i)
{
    printf("-- WPI FATAL %d --\n", i);
}

DriverStation* DriverStation::ap_singletonInstance = NULL;
/********* END STUBS **************/

/***************************
  Using constants to make the code readable
****************************/
#define PORT_DRIVER 1
#define PORT_MANIPULATOR 2

int main(void)
{
    InputManager* inMgr;

    inMgr = InputManager::Instance();

    inMgr->RegisterAxis(InputManager::AXIS_INDEX_DRIVE_THROTTLE,
                        PORT_DRIVER,
                        Gamepad::GetAxisNumber(Gamepad::kRightYAxis));

    inMgr->RegisterButton(InputManager::BUTTON_INDEX_DRIVE_ANTITURBO,
                          PORT_DRIVER,
                          Gamepad::GetButtonNumber(Gamepad::kLeftTrigger),
                          InputManager::BUTTON_TYPE_STANDARD);

    inMgr->RegisterButton(InputManager::BUTTON_INDEX_STICKY_TEST,
                          PORT_DRIVER,
                          Gamepad::GetButtonNumber(Gamepad::kXButton),
                          InputManager::BUTTON_TYPE_STICKY);

    inMgr->RegisterButton(InputManager::BUTTON_INDEX_KICK,
                          PORT_DRIVER,
                          Gamepad::GetButtonNumber(Gamepad::kCircleButton),
                          InputManager::BUTTON_TYPE_TAP);

    // Can't assign buttons in the variable declaration because it allocates
    // extra size...we only want 2
    vector<UINT32> multiStickyTestButtons;
    multiStickyTestButtons.push_back(Gamepad::GetButtonNumber(Gamepad::kLeftBumper)); // off button
    multiStickyTestButtons.push_back(Gamepad::GetButtonNumber(Gamepad::kRightBumper)); // on button

    inMgr->RegisterButton(InputManager::BUTTON_INDEX_MULTISTICKY_TEST,
                          PORT_DRIVER,
                          multiStickyTestButtons,
                          InputManager::BUTTON_TYPE_MULTISTICKY);

    inMgr->RegisterDPad(InputManager::DPAD_INDEX_DRIVER,
                        PORT_DRIVER);
    int i;
    for(i = 0; i < 10; i++)
    {
        inMgr->ReadInputs();
        printf("%f\n",
                inMgr->GetAxisValue(InputManager::AXIS_INDEX_DRIVE_THROTTLE));
        printf("%f %d %d %d %d %d\n",
                inMgr->GetAxisValue(InputManager::AXIS_INDEX_DRIVE_THROTTLE),
                inMgr->GetButtonValue(InputManager::BUTTON_INDEX_DRIVE_ANTITURBO),
                inMgr->GetButtonValue(InputManager::BUTTON_INDEX_KICK),
                inMgr->GetButtonValue(InputManager::BUTTON_INDEX_STICKY_TEST),
                inMgr->GetButtonValue(InputManager::BUTTON_INDEX_MULTISTICKY_TEST),
                inMgr->GetDPadValue(InputManager::DPAD_INDEX_DRIVER));
    }

    inMgr->ResetInputs();
    printf("%f %d %d %d %d %d\n",
            inMgr->GetAxisValue(InputManager::AXIS_INDEX_DRIVE_THROTTLE),
            inMgr->GetButtonValue(InputManager::BUTTON_INDEX_DRIVE_ANTITURBO),
            inMgr->GetButtonValue(InputManager::BUTTON_INDEX_KICK),
            inMgr->GetButtonValue(InputManager::BUTTON_INDEX_STICKY_TEST),
            inMgr->GetButtonValue(InputManager::BUTTON_INDEX_MULTISTICKY_TEST),
            inMgr->GetDPadValue(InputManager::DPAD_INDEX_DRIVER));

    delete inMgr;




    return 0;
}
