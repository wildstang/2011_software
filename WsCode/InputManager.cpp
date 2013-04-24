#include "WPILib.h"
#include "InputManager.h"
#include "Gamepad.h"

using namespace std;

// Initialize singleton instance
InputManager* InputManager::ap_singletonInstance = NULL;

// Return the singleton instance
InputManager* InputManager::Instance()
{
    if(ap_singletonInstance == NULL)
    {
        ap_singletonInstance = new InputManager();
    }

    return ap_singletonInstance;
}

/*****************************
  Constructor
  - Nothing needs to be done here
*****************************/
InputManager::InputManager()
{
}


/*****************************
  Destructor
  - Unregister all registrations
*****************************/

InputManager::~InputManager()
{
    UnregisterAll();
}

/*****************************
  RegisterAxis
  This is used to register a port/axis combination to an axis index 

  If the index is not in the map, create a new axis object and add
  it to the map
  If the index is already in the map, print and call wpi_assert

  @param index       The axis functionality index
  @param devicePort  The port the axis is on
  @param axis        The axis number to assign
  @param invert      Whether to invert the axis or not
*****************************/
void InputManager::RegisterAxis(InputManager::AxisIndexT index,
                                GamepadIndexT gamepadIndex,
                                Gamepad::AxisType axis,
                                bool invert)
{
    AxisIteratorT it;
    it = a_axisMap.find(index);

    Gamepad* pad = GetGamepad(gamepadIndex);

    if( it == a_axisMap.end() )
    {
        a_axisMap[index] = new AxisDataT();
        a_axisMap[index]->axis = new WsControllerAxis(pad, Gamepad::GetAxisNumber(axis), invert );
        a_axisMap[index]->cachedValue = 0;
    }
    else
    {
        // Throw an error if it is already registered
        printf("Axis %d already exists\n", index);
        wpi_assert(false);
    }
 }

/*****************************
  RegisterDPad
  This is used to register a Dpad device to a functionality

  If the index is not in the map, create a new DPad object and add
  it to the map
  If the index is already in the map, print and call wpi_assert

  @param index       The DPad functionality index
  @param devicePort  The port the DPad is connected to
*****************************/
void InputManager::RegisterDPad(InputManager::DPadIndexT index,
                                GamepadIndexT gamepadIndex)
{
    DPadIteratorT it;
    UINT32 port = GetPortFromIndex(gamepadIndex);
    
    it = a_dPadMap.find(index);

    if( it == a_dPadMap.end() )
    {
        a_dPadMap[index] = new DPadDataT();
        a_dPadMap[index]->pad = new GamepadDPad( port );
        a_dPadMap[index]->cachedValue = GamepadDPad::kCenter;
    }
    else
    {
        // Throw an error if it is already registered
        printf("DPad %d already exists\n", index);
        wpi_assert(false);
    }
}

/*****************************
  RegisterButton
  This form is used for button types that use a single button
  This is used to register a port/button number combination to a button index.  This also
  assigns the virtual button type to be used.

  If the index is not in the map, create a new button object based on the type and add
  it to the map
  If the index is already in the map, print and call wpi_assert

  @param index        The button functionality index
  @param devicePort   The port the controller that the button is on is on
  @param buttonNumber The button number to assign
  @param buttonStyle   The virtual button type that the button should act as
  @param invert       Whether to invert the button or not
*****************************/
void InputManager::RegisterButton(InputManager::ButtonIndexT index,
                                  GamepadIndexT gamepadIndex,
                                  Gamepad::ButtonType buttonType,
                                  InputManager::ButtonStyleT buttonStyle,
                                  bool invert)
{
    ButtonIteratorT it;
    //UINT32 buttonNumber = Gamepad::GetButtonNumber(buttonType);
    Gamepad* pad = GetGamepad(gamepadIndex);
    it = a_buttonMap.find(index);

    if( it == a_buttonMap.end() )
    {
        a_buttonMap[index] = new ButtonDataT();

        switch(buttonStyle)
        {
            case BUTTON_STYLE_STANDARD:
                a_buttonMap[index]->button = new WsControllerButton( pad, buttonType);
                break;
            case BUTTON_STYLE_STICKY:
                a_buttonMap[index]->button = new WsControllerStickyButton( pad, buttonType);
                break;
            case BUTTON_STYLE_TAP:
                a_buttonMap[index]->button = new WsControllerTapButton( pad, buttonType);
                break;
            case BUTTON_STYLE_MULTISTICKY:
                // Multisticky should use the vector constructor
                printf("Multisticky %d requires a list of buttons\n", index);
                wpi_assert(false);
                break;
            case BUTTON_STYLE_MULTIFUNCTION_NO_SHIFT:
            case BUTTON_STYLE_MULTIFUNCTION_SHIFT:
                // Multifunction should use the vector constructor
                printf("Multifunction %d requires a list of buttons\n", index);
                wpi_assert(false);
                break;
            default:
                printf("Unhandles button type for index %d\n", index);
                wpi_assert(false);
                break;
        }

        a_buttonMap[index]->cachedValue = false;
    }
    else
    {
        // Throw an error if it is already registered
        printf("Button %d already exists\n", index);
        wpi_assert(false);
    }
}

/*****************************
  RegisterButton
  This form is used for button types that use multiple buttons
  This is used to register a port/button number combination to a button index.  This also
  assigns the virtual button type to be used.

  If the index is not in the map, create a new button object based on the type and add
  it to the map
  If the index is already in the map, print and call wpi_assert

  @param index        The button functionality index
  @param devicePort   The port the controller that the button is on is on
  @param buttonList   A vector of buttons to assign
  @param buttonStyle   The virtual button type that the button should act as
  @param invert       Whether to invert the button or not
*****************************/
void InputManager::RegisterButton(InputManager::ButtonIndexT index,
                                  GamepadIndexT gamepadIndex,
                                  vector<Gamepad::ButtonType> buttonList,
                                  InputManager::ButtonStyleT buttonStyle,
                                  bool invert)
{
    ButtonIteratorT it;
    Gamepad* pad = GetGamepad(gamepadIndex);
    it = a_buttonMap.find(index);

    if( it == a_buttonMap.end() )
    {
        a_buttonMap[index] = new ButtonDataT();

        switch(buttonStyle)
        {
            case BUTTON_STYLE_STANDARD:
            case BUTTON_STYLE_STICKY:
            case BUTTON_STYLE_TAP:
                printf("Button type %d Use scalar registration.\n", buttonStyle);
                wpi_assert(false);
                break;
            case BUTTON_STYLE_MULTISTICKY:
                if(buttonList.size() >= 2)
                {
                    // Multisticky should use the vector constructor
                    a_buttonMap[index]->button = new WsControllerMultiStickyButton(pad,
                                                                                   buttonList[0],
                                                                                   buttonList[1]);
                }
                else
                {
                    printf("Multisticky button needs 2 buttons\n");
                    wpi_assert(false);
                }
                break;
            case BUTTON_STYLE_MULTIFUNCTION_NO_SHIFT:
                if(buttonList.size() >= 2)
                {
                    // Multisticky should use the vector constructor
                    a_buttonMap[index]->button = new WsControllerMultiFunctionButton(pad,
                                                                                   buttonList[0],
                                                                                   buttonList[1],
                                                                                   false);
                }
                else
                {
                    printf("Multifunction button needs 2 buttons\n");
                    wpi_assert(false);
                }
                break;
            case BUTTON_STYLE_MULTIFUNCTION_SHIFT:
                if(buttonList.size() >= 2)
                {
                    // Multisticky should use the vector constructor
                    a_buttonMap[index]->button = new WsControllerMultiFunctionButton(pad,
                                                                                   buttonList[0],
                                                                                   buttonList[1],
                                                                                   true);
                }
                else
                {
                    printf("Multifunction button needs 2 buttons\n");
                    wpi_assert(false);
                }
                break;
            default:
                printf("Unhandled button type for index %d\n", index);
                wpi_assert(false);
                break;
        }

        a_buttonMap[index]->cachedValue = false;
    }
    else
    {
        // Throw an error if it is already registered
        printf("Button %d already exists\n", index);
        wpi_assert(false);
    }
}


//void RegisterDsAnalog();

/*****************************
  ReadInputs
  Called to read all registered devices and store off a cached value for later processing.
  Loops over axes, buttons, and dpads
*****************************/
void InputManager::ReadInputs(void)
{
    AxisIteratorT axisIt;
    for( axisIt = a_axisMap.begin(); axisIt != a_axisMap.end(); ++axisIt )
    {
        try
        {
            axisIt->second->cachedValue = axisIt->second->axis->GetValue();
        }
        catch(...)
        {
            axisIt->second->cachedValue = 0.0f;
        }
    }

    DPadIteratorT dPadIt;
    for( dPadIt = a_dPadMap.begin(); dPadIt != a_dPadMap.end(); ++dPadIt )
    {
        try
        {
            dPadIt->second->cachedValue = dPadIt->second->pad->GetDPad();
        }
        catch(...)
        {
            dPadIt->second->cachedValue = GamepadDPad::kCenter;
        }
    }

    ButtonIteratorT buttonIt;
    for( buttonIt = a_buttonMap.begin(); buttonIt != a_buttonMap.end(); ++buttonIt )
    {
        try
        {
            buttonIt->second->cachedValue = buttonIt->second->button->GetState();
        }
        catch(...)
        {
            buttonIt->second->cachedValue = false;
        }
    }
}

/*****************************
  ResetInputs
  Called to clear the cached values of registered devices.
  - Axes are set to 0.0
  - Buttons are set to false and their Reset method is called to clear any state
  - DPads are set to center
*****************************/
void InputManager::ResetInputs(void)
{
    AxisIteratorT axisIt;
    for( axisIt = a_axisMap.begin(); axisIt != a_axisMap.end(); ++axisIt )
    {
        axisIt->second->cachedValue = 0;
    }

    DPadIteratorT dPadIt;
    for( dPadIt = a_dPadMap.begin(); dPadIt != a_dPadMap.end(); ++dPadIt )
    {
        dPadIt->second->cachedValue = GamepadDPad::kCenter;
    }

    ButtonIteratorT buttonIt;
    for( buttonIt = a_buttonMap.begin(); buttonIt != a_buttonMap.end(); ++buttonIt )
    {
        buttonIt->second->button->ResetState();
        buttonIt->second->cachedValue = false;
    }
}

void InputManager::ResetButton(ButtonIndexT index,
                               GamepadIndexT gamepadIndexT)
{
    ButtonIteratorT it = a_buttonMap.find(index);
    if( it != a_buttonMap.end() )
    {
        it->second->button->ResetState();
        it->second->cachedValue = false;
    }
}


/*************************
  GetAxisValue
  The desired axis is looked up in the axis map.  The cached value is retrieved
  and returned.  If the index is not found, a default value of 0.0 will be returned.
  @param index   The axis index to get the cached value for
  @returns       The cached value of the desired axis (default is 0)
*****************************/
float InputManager::GetAxisValue(InputManager::AxisIndexT index)
{
    float value = 0.0;

    AxisIteratorT it = a_axisMap.find(index);
    if( it != a_axisMap.end() )
    {
        value = it->second->cachedValue;
    }

    return value;
}

/*************************
  GetButtonValue
  The desired button is looked up in the button map.  The cached value is retrieved
  and returned.  If the index is not found, a default value of false will be returned.
  @param index   The button index to get the cached value for
  @returns       The cached value of the desired button (default is false)
*****************************/
bool InputManager::GetButtonValue(InputManager::ButtonIndexT index)
{
    bool value = false;

    ButtonIteratorT it = a_buttonMap.find(index);
    if( it != a_buttonMap.end() )
    {
        value = it->second->cachedValue;
    }

    return value;
}

/*************************
  GetDPadDirection
  The desired DPad is looked up in the DPad map.  The cached value is retrieved
  and returned.  If the index is not found, a default value of center will be returned.
  @param index   The DPad index to get the cached value for
  @returns       The cached value of the desired DPad (default is center)
*****************************/
GamepadDPad::DPadDirection InputManager::GetDPadValue(InputManager::DPadIndexT index)
{
    GamepadDPad::DPadDirection value = GamepadDPad::kCenter;

    DPadIteratorT it = a_dPadMap.find(index);
    if( it != a_dPadMap.end() )
    {
        value = it->second->cachedValue;
    }

    return value;
}
//UINT32 GetAnalogValue();

/*************************
  UnregisterAxis
  The desired axis is looked up in the axis map.  If it is found, the contained
  axis is deleted, the element in the map is deleted, then the element is erased
  from the map

  @param index   The axis index to unregister
*****************************/

void InputManager::UnregisterAxis(InputManager::AxisIndexT index)
{
    AxisIteratorT it;
    it = a_axisMap.find(index);

    if( it != a_axisMap.end() )
    {
        delete it->second->axis;
        delete it->second;
        a_axisMap.erase( it );
        
    }
}

/*************************
  UnregisterButton
  The desired button is looked up in the button map.  If it is found, the contained
  button is deleted, the element in the map is deleted, then the element is erased
  from the map

  @param index   The button index to unregister
*****************************/
void InputManager::UnregisterButton(InputManager::ButtonIndexT index)
{
    ButtonIteratorT it;
    it = a_buttonMap.find(index);

    if( it != a_buttonMap.end() )
    {
        delete it->second->button;
        delete it->second;
        a_buttonMap.erase( it );
    }
}

/*************************
  UnregisterGamepad
  The desired gamepad is looked up in the gamepad map.  If it is found, the contained
  gamepad is deleted, the element in the map is deleted, then the element is erased
  from the map

  @param index   The gamepad index to unregister
*****************************/
void InputManager::UnregisterGamepad(InputManager::GamepadIndexT index)
{
    GamepadIteratorT it;
    it = a_gamepadMap.find(index);

    if( it != a_gamepadMap.end() )
    {
        delete it->second->pad;
        delete it->second;
        a_gamepadMap.erase( it );
    }
}

/*************************
  UnregisterDPad
  The desired DPad is looked up in the DPad map.  If it is found, the contained
  DPad is deleted, the element in the map is deleted, then the element is erased
  from the map

  @param index   The DPad index to unregister
*****************************/
void InputManager::UnregisterDPad(InputManager::DPadIndexT index)
{
    DPadIteratorT it;
    it = a_dPadMap.find(index);

    if( it != a_dPadMap.end() )
    {
        delete it->second->pad;
        delete it->second;
        a_dPadMap.erase( it );
    }
}

//void UnregisterDsAnalog();


/*************************
  UnregisterDPad
  Loops over all input enums and unregisters the corresponding index.
*****************************/
void InputManager::UnregisterAll()
{
    AxisIndexT iAxis;
    DPadIndexT iDPad;
    ButtonIndexT iButton;
    GamepadIndexT iGamepad;

    for(iAxis = MIN_AXIS; iAxis < NUM_AXES; iAxis = AxisIndexT(iAxis + 1))
    {
        UnregisterAxis(iAxis);
    }

    for(iDPad = MIN_DPAD; iDPad < NUM_DPAD; iDPad = DPadIndexT(iDPad + 1))
    {
        UnregisterDPad(iDPad);
    }

    for(iButton = MIN_BUTTON; iButton < NUM_BUTTONS; iButton = ButtonIndexT(iButton + 1))
    {
        UnregisterButton(iButton);
    }

    for(iGamepad = MIN_GAMEPAD; iGamepad < NUM_GAMEPADS; iGamepad = GamepadIndexT(iGamepad + 1))
    {
        UnregisterGamepad(iGamepad);
    }
}


Gamepad* InputManager::GetGamepad(GamepadIndexT gamepadIndex)
{
    Gamepad* pad = NULL;
    GamepadIteratorT it;

    UINT32 port = 0;

    it = a_gamepadMap.find(gamepadIndex);

    if(it == a_gamepadMap.end())
    {
        port = GetPortFromIndex(gamepadIndex);
        pad =  new Gamepad(port);
        a_gamepadMap[gamepadIndex] = new GamepadDataT();
        a_gamepadMap[gamepadIndex]->pad = pad;
    }
    else
    {
        pad = it->second->pad;
    }

    return pad;
}

UINT32 InputManager::GetPortFromIndex(GamepadIndexT gamepadIndex)
{
    UINT32 port = 0;
    switch(gamepadIndex)
    {
    case GAMEPAD_INDEX_DRIVER:
        port = GAMEPAD_PORT_DRIVER;
        break;
    case GAMEPAD_INDEX_MANIPULATOR:
        port = GAMEPAD_PORT_MANIPULATOR;
        break;
    case GAMEPAD_INDEX_PORT3:
        port = GAMEPAD_PORT_UNUSED_A;
        break;
    case GAMEPAD_INDEX_OI:
        port = GAMEPAD_PORT_OI;
        break;
    default:
        printf("Unknown gamepad  %d\n", gamepadIndex);
        wpi_assert(false);
    }
    return port;
}



