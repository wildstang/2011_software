#include "WsDashboard.h"
#include "WPILib.h"
#include "Timer.h"
#include "DriverStation.h"
#include "WsDriveVector.h"

WsDashboard* WsDashboard::ap_instance = NULL;

WsDashboard::WsDashboard(DriverStation* p_ds)
{
    int i;

#if USE_DATA_TIMER
    dataTimer = new Timer();
    dataTimer->Start();
#endif

    ap_ds = p_ds;
    for(i = 0; i < MAX_NUM_DATA_IDX; i++)
    {
        a_data[i] = NULL;
    }

    a_data[IDX_IN_DRIVE_THROTTLE] = new DashboardDataFloat();
    a_data[IDX_IN_DRIVE_TURN] = new DashboardDataFloat();
    a_data[IDX_IN_DRIVE_TURBO] = new DashboardDataBool();
    a_data[IDX_IN_DRIVE_SHIFTER] = new DashboardDataBool();

    a_data[IDX_OUT_DRIVE_RIGHT] = new DashboardDataFloat();
    a_data[IDX_OUT_DRIVE_LEFT] = new DashboardDataFloat();
    a_data[IDX_OUT_DRIVE_SHIFTER] = new DashboardDataBool();
    a_data[IDX_OUT_CLAW_SPEED] = new DashboardDataFloat();
    a_data[IDX_OUT_CLAW_RELEASE] = new DashboardDataBool();
    a_data[IDX_OUT_LIFT_SPEED] = new DashboardDataFloat();
    a_data[IDX_OUT_ARM_SPEED] = new DashboardDataFloat();

    a_data[IDX_SENSOR_ENC_LEFT] = new DashboardDataINT32();
    a_data[IDX_SENSOR_ENC_RIGHT] = new DashboardDataINT32();
    a_data[IDX_SENSOR_GYRO_ANGLE] = new DashboardDataFloat();
    a_data[IDX_SENSOR_POT_ARM] = new DashboardDataINT32();
    a_data[IDX_SENSOR_ENC_LIFT] = new DashboardDataINT32();
    a_data[IDX_SENSOR_SW_LIFT_BOT] = new DashboardDataBool();
    a_data[IDX_SENSOR_SW_LIFT_TOP] = new DashboardDataBool();
    a_data[IDX_SENSOR_SW_TUBE_POSS] = new DashboardDataBool();

    a_data[IDX_DRIVESTRAIGHT_CMD_SPEED_LEFT] = new DashboardDataFloat();
    a_data[IDX_DRIVESTRAIGHT_CMD_SPEED_RIGHT] = new DashboardDataFloat();
    a_data[IDX_DRIVESTRAIGHT_ADJ_SPEED_LEFT] = new DashboardDataFloat();
    a_data[IDX_DRIVESTRAIGHT_ADJ_SPEED_RIGHT] = new DashboardDataFloat();
    a_data[IDX_DRIVESTRAIGHT_ENC_SNAPPED_DIFF] = new DashboardDataINT32();
    a_data[IDX_DRIVESTRAIGHT_ENC_CURR_DIFF] = new DashboardDataINT32();
    a_data[IDX_DRIVESTRAIGHT_ENABLED] = new DashboardDataBool();

    a_data[IDX_LARM_SETPOINT_ARM] = new DashboardDataINT32();
    a_data[IDX_LARM_SETPOINT_LIFT] = new DashboardDataINT32();
    a_data[IDX_LARM_POSITION] = new DashboardDataINT32();
    a_data[IDX_LARM_ARM_IN_POSITION] = new DashboardDataBool();
    a_data[IDX_LARM_LIFT_IN_POSITION] = new DashboardDataBool();
    a_data[IDX_LARM_ARM_ANGLE] = new DashboardDataFloat();

    a_data[IDX_AUTO_PROG_NUM] = new DashboardDataUINT32();
    a_data[IDX_AUTO_RACK_LOC] = new DashboardDataUINT32();
    a_data[IDX_AUTO_COL_LOC] = new DashboardDataUINT32();
    a_data[IDX_AUTO_PEG_HEIGHT] = new DashboardDataUINT32();
    a_data[IDX_AUTO_START_DELAY] = new DashboardDataFloat();
    a_data[IDX_AUTO_LOCK] = new DashboardDataBool();

    a_data[IDX_LED_CMD] = new DashboardDataUINT32();

    a_data[IDX_MINIBOT_MODE] = new DashboardDataUINT32();

    /*
    for(i = 0; i < MAX_NUM_DATA_IDX; i++)
    {
        if(a_data[i] != NULL)
        {
            a_data[i]->reset();
        }
    }
    */
}

WsDashboard::~WsDashboard()
{
    int i;
    for(i = 0; i < MAX_NUM_DATA_IDX; i++)
    {
        if(a_data[i] != NULL)
        {
            delete a_data[i];
            a_data[i] = NULL;
        }
    }

    if(ap_instance != NULL)
    {
        delete ap_instance;
    }

    ap_instance = NULL;

#if USE_DATA_TIMER
    dataTimer->Stop();
    delete dataTimer;
#endif

#if USE_VISION_TIMER
    visionTimer->Stop();
    delete visionTimer;
#endif
}

WsDashboard* WsDashboard::getInstance()
{
   return ap_instance;
}

WsDashboard* WsDashboard::getInstance(DriverStation* p_ds)
{
    if(ap_instance == NULL)
    {
        ap_instance = new WsDashboard(p_ds);
    }
    return ap_instance;
}

void WsDashboard::setValue(DashboardIndexT index, bool value)
{
    a_data[index]->set(value);
}

void WsDashboard::setValue(DashboardIndexT index, UINT32 value)
{
    a_data[index]->set(value);
}

void WsDashboard::setValue(DashboardIndexT index, INT32 value)
{
    a_data[index]->set(value);
}

void WsDashboard::setValue(DashboardIndexT index, float value)
{
    a_data[index]->set(value);
}

void WsDashboard::getValue(DashboardIndexT index, bool* value)
{
    a_data[index]->get(value);
}

void WsDashboard::getValue(DashboardIndexT index, UINT32* value)
{
    a_data[index]->get(value);
}

void WsDashboard::getValue(DashboardIndexT index, INT32* value)
{
    a_data[index]->get(value);
}

void WsDashboard::getValue(DashboardIndexT index, float* value)
{
    a_data[index]->get(value);
}


void WsDashboard::resetValues()
{
    int i;
    for(i = 0; i < MAX_NUM_DATA_IDX; i++)
    {
        a_data[i]->reset();
    }
}

void WsDashboard::update()
{
    updateDataSections();
}


void WsDashboard::updateDataSections(void)
{
#if USE_DATA_TIMER
    if (dataTimer->Get() < 0.1)
    {
        return;
    }
    dataTimer->Reset();
#endif

    Dashboard &dataDashboardPacker = ap_ds->GetLowPriorityDashboardPacker();

    // ORDER MATTERS!!!
    packSection(dataDashboardPacker, SECTION_INPUT_START, SECTION_INPUT_END);
    packSection(dataDashboardPacker, SECTION_OUTPUT_START, SECTION_OUTPUT_END);
    packSection(dataDashboardPacker, SECTION_SENSOR_START, SECTION_SENSOR_END);
    packSection(dataDashboardPacker, SECTION_DRIVESTRAIGHT_START, SECTION_DRIVESTRAIGHT_END);
    packSection(dataDashboardPacker, SECTION_LARM_START, SECTION_LARM_END);
    packSection(dataDashboardPacker, SECTION_AUTONOMOUS_START, SECTION_AUTONOMOUS_END);
    packSection(dataDashboardPacker, SECTION_MINIBOT_START, SECTION_MINIBOT_END);
    packSection(dataDashboardPacker, SECTION_MISC_START, SECTION_MISC_END);

    // Flush the data to the driver station
    dataDashboardPacker.Finalize();
}

void WsDashboard::packSection(Dashboard& dashboard,
                              DashboardIndexT startIndex,
                              DashboardIndexT endIndex)
{
    int i;
    dashboard.AddCluster();
    for(i = startIndex; i <= endIndex; i++)
    {
        packData(dashboard, i);
    }
    dashboard.FinalizeCluster();
}


void WsDashboard::packData(Dashboard& dashboard, const int& index)
{
    bool valueBool;
    UINT32 valueUINT32;
    INT32 valueINT32;
    float valueFloat;

    switch(a_data[index]->a_dataType)
    {
        case DATA_TYPE_BOOL:
            a_data[index]->get(&valueBool);
            dashboard.AddBoolean(valueBool);
            break;
        case DATA_TYPE_UINT32:
            a_data[index]->get(&valueUINT32);
            dashboard.AddU32(valueUINT32);
            break;
        case DATA_TYPE_INT32:
            a_data[index]->get(&valueINT32);
            dashboard.AddI32(valueINT32);
            break;
        case DATA_TYPE_FLOAT:
            a_data[index]->get(&valueFloat);
            dashboard.AddFloat(valueFloat);
            break;
        default:
            break;
    }
}
