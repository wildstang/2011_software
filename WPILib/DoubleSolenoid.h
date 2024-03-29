/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef DOUBLE_SOLENOID_H_
#define DOUBLE_SOLENOID_H_

#include "SolenoidBase.h"

/**
 * DoubleSolenoid class for running 2 channels of high voltage Digital Output
 * (9472 module).
 * 
 * The DoubleSolenoid class is typically used for pneumatics solenoids that
 * have two positions controlled by two separate channels.
 */
class DoubleSolenoid : public SolenoidBase {
public:
	typedef enum {kOff, kForward, kReverse} Value;

	explicit DoubleSolenoid(UINT32 forwardChannel, UINT32 reverseChannel);
	DoubleSolenoid(UINT32 slot, UINT32 forwardChannel, UINT32 reverseChannel);
	virtual ~DoubleSolenoid();
	virtual void Set(Value value);
	virtual Value Get();

private:
	virtual void InitSolenoid();

	UINT32 m_forwardChannel; ///< The forward channel on the module to control.
	UINT32 m_reverseChannel; ///< The reverse channel on the module to control.
	UINT8 m_forwardMask; ///< The mask for the forward channel.
	UINT8 m_reverseMask; ///< The mask for the reverse channel.
};

#endif
