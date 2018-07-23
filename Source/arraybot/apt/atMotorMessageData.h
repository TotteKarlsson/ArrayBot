#ifndef atMotorMessageDataH
#define atMotorMessageDataH
#include "arraybot/atABExporter.h"
#include <string>
#include "dslProperty.h"
#include "dslRange.h"
//--------------------------------------------------------------------
using std::string;
using dsl::Property;
using dsl::Range;

//!Motor message data may be send as a windows message to communicate that something
//!is happening regarding the motor. It is up to the listening UI to communicate this
//!to the user, and/or deal with it.
class AT_AB MotorMessageData
{
	public:
    								MotorMessageData();
        string 						mSerial;
        string 						mName;
        double      				mCurrentPosition;
        Property< Range<double> > 	mPositionLimits;
        Property< bool > 	 		mPositionLimitsEnabled;
};

#endif
