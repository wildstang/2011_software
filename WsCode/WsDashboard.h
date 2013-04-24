#if !defined(_WSDASHBOARD_H)
#define _WSDASHBOARD_H

#include <stdio.h>
#include <vector>
#include "WsDriveVector.h"

class Dashboard;
class Timer;


#define USE_DATA_TIMER 0


typedef enum
{
    ////////////////////////////////////
    SECTION_INPUT_START,
    IDX_IN_DRIVE_THROTTLE = SECTION_INPUT_START,
    IDX_IN_DRIVE_TURN,
    IDX_IN_DRIVE_TURBO,
    IDX_IN_DRIVE_SHIFTER,
    SECTION_INPUT_END = IDX_IN_DRIVE_SHIFTER,
    ////////////////////////////////////

    ////////////////////////////////////
    SECTION_OUTPUT_START,
    IDX_OUT_DRIVE_RIGHT = SECTION_OUTPUT_START,
    IDX_OUT_DRIVE_LEFT,
    IDX_OUT_DRIVE_SHIFTER,
    IDX_OUT_CLAW_SPEED,
    IDX_OUT_CLAW_RELEASE,
    IDX_OUT_LIFT_SPEED,
    IDX_OUT_ARM_SPEED,
    SECTION_OUTPUT_END = IDX_OUT_ARM_SPEED,
    ////////////////////////////////////

    ////////////////////////////////////
    SECTION_SENSOR_START,
    IDX_SENSOR_ENC_LEFT = SECTION_SENSOR_START,
    IDX_SENSOR_ENC_RIGHT,
    IDX_SENSOR_GYRO_ANGLE,
    IDX_SENSOR_POT_ARM,
    IDX_SENSOR_ENC_LIFT,
    IDX_SENSOR_SW_LIFT_BOT,
    IDX_SENSOR_SW_LIFT_TOP,
    IDX_SENSOR_SW_TUBE_POSS,
    SECTION_SENSOR_END = IDX_SENSOR_SW_TUBE_POSS,
    ////////////////////////////////////

    ////////////////////////////////////
    SECTION_DRIVESTRAIGHT_START,
    IDX_DRIVESTRAIGHT_CMD_SPEED_LEFT = SECTION_DRIVESTRAIGHT_START,
    IDX_DRIVESTRAIGHT_CMD_SPEED_RIGHT,
    IDX_DRIVESTRAIGHT_ADJ_SPEED_LEFT,
    IDX_DRIVESTRAIGHT_ADJ_SPEED_RIGHT,
    IDX_DRIVESTRAIGHT_ENC_SNAPPED_DIFF,
    IDX_DRIVESTRAIGHT_ENC_CURR_DIFF,
    IDX_DRIVESTRAIGHT_ENABLED,
    SECTION_DRIVESTRAIGHT_END = IDX_DRIVESTRAIGHT_ENABLED,
    ////////////////////////////////////

    ////////////////////////////////////
    SECTION_LARM_START,
    IDX_LARM_SETPOINT_ARM = SECTION_LARM_START,
    IDX_LARM_SETPOINT_LIFT,
    IDX_LARM_POSITION,
    IDX_LARM_ARM_IN_POSITION,
    IDX_LARM_LIFT_IN_POSITION,
    IDX_LARM_ARM_ANGLE,
    SECTION_LARM_END = IDX_LARM_ARM_ANGLE,
    ////////////////////////////////////

    ////////////////////////////////////
    SECTION_AUTONOMOUS_START,
    IDX_AUTO_PROG_NUM = SECTION_AUTONOMOUS_START,
    IDX_AUTO_RACK_LOC,
    IDX_AUTO_COL_LOC,
    IDX_AUTO_PEG_HEIGHT,
    IDX_AUTO_START_DELAY,
    IDX_AUTO_LOCK,
    SECTION_AUTONOMOUS_END = IDX_AUTO_LOCK,
    ////////////////////////////////////

    ////////////////////////////////////
    SECTION_MINIBOT_START,
    IDX_MINIBOT_MODE = SECTION_MINIBOT_START,
    SECTION_MINIBOT_END = IDX_MINIBOT_MODE,
    ////////////////////////////////////

    SECTION_MISC_START,
    IDX_LED_CMD = SECTION_MISC_START,
    SECTION_MISC_END = IDX_LED_CMD,

    // All indicies go above here
    MAX_NUM_DATA_IDX
} DashboardIndexT;

typedef enum
{
    DATA_TYPE_BOOL,
    DATA_TYPE_UINT32,
    DATA_TYPE_INT32,
    DATA_TYPE_FLOAT,
    DATA_TYPE_VISION,
} DashboardDataTypeT;

class DriverStation;

class DashboardDataBase
{
    public:
        virtual void reset(void) = 0;
        virtual void get(bool* value)
        {
            *value = false;
        }
        virtual void get(UINT32* value)
        {
            *value = 0;
        }
        virtual void get(INT32* value)
        {
            *value = 0;
        }
        virtual void get(float* value)
        {
            *value = 0;
        }
        virtual void set(bool value)
        {
        }
        virtual void set(UINT32 value)
        {
        }
        virtual void set(INT32 value)
        {
        }
        virtual void set(float value)
        {
        }

        DashboardDataTypeT a_dataType;

};
class DashboardDataBool : public DashboardDataBase
{
    public:
        DashboardDataBool()
        {
            a_dataType = DATA_TYPE_BOOL;
            reset();
        }
        virtual void reset(void)
        {
            a_value = false;
        }
        virtual void set(bool value)
        {
            a_value = value;
        }
        virtual void get(bool* value)
        {
            *value = a_value;
        }
    protected:
        bool a_value;

};
class DashboardDataUINT32 : public DashboardDataBase
{
    public:
        DashboardDataUINT32()
        {
            a_dataType = DATA_TYPE_UINT32;
            reset();
        }
        virtual void reset(void)
        {
            a_value = 0;
        }
        virtual void set(UINT32 value)
        {
            a_value = value;
        }
        virtual void get(UINT32* value)
        {
            *value = a_value;
        }
    protected:
        UINT32 a_value;
};
class DashboardDataINT32 : public DashboardDataBase
{
    public:
        DashboardDataINT32()
        {
            a_dataType = DATA_TYPE_INT32;
            reset();
        }
        virtual void reset(void)
        {
            a_value = 0;
        }
        virtual void set(INT32 value)
        {
            a_value = value;
        }
        virtual void get(INT32* value)
        {
            *value = a_value;
        }
    protected:
        INT32 a_value;
};
class DashboardDataFloat : public DashboardDataBase
{
    public:
        DashboardDataFloat()
        {
            a_dataType = DATA_TYPE_FLOAT;
            reset();
        }
        virtual void reset(void)
        {
            a_value = 0;
        }
        virtual void set(float value)
        {
            a_value = value;
        }
        virtual void get(float *value)
        {
            *value = a_value;
        }
    protected:
        float a_value;
};



class WsDashboard
{
public:
    virtual ~WsDashboard();
    // This should be called by the robot to assign the DS
    static WsDashboard* getInstance(DriverStation* p_ds);
    // This should be called by classes that will update data
    static WsDashboard* getInstance();
    void resetValues(void);
    void update(void);

    void setValue(DashboardIndexT index, bool value);
    void setValue(DashboardIndexT index, UINT32 value);
    void setValue(DashboardIndexT index, INT32 value);
    void setValue(DashboardIndexT index, float value);

    void getValue(DashboardIndexT index, bool* value);
    void getValue(DashboardIndexT index, UINT32* value);
    void getValue(DashboardIndexT index, INT32* value);
    void getValue(DashboardIndexT index, float* value);

protected:
    WsDashboard(DriverStation* p_ds);
    static WsDashboard* ap_instance;

    // There are two top level data streams: data and vision
    void updateDataSections(void);
    void updateVisionSection(void);

    void packSection(Dashboard& dashboard, DashboardIndexT startIndex, DashboardIndexT endIndex);

    // This is a generic function that knows how to pack
    // all data types.  It will determine the type based on index
    void packData(Dashboard& dashboard, const int& index);

    DriverStation* ap_ds;
    DashboardDataBase* a_data[MAX_NUM_DATA_IDX];

#if USE_DATA_TIMER
    Timer *dataTimer;
#endif
#if USE_VISION_TIMER
    Timer *visionTimer;
#endif
};

#endif  //_WSDASHBOARD_H

