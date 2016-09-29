#pragma hdrstop
#include "abMotorMessageData.h"

//---------------------------------------------------------------------------
MotorMessageData::MotorMessageData()
:
mSerial(""),
mName(""),
mCurrentPosition(-1),
mPositionLimits(Range<double>(0,0)),
mPositionLimitsEnabled(false)
{}

