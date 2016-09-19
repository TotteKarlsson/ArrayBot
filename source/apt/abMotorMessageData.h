#ifndef abMotorMessageDataH
#define abMotorMessageDataH
#include "abExporter.h"
#include <string>
#include "mtkProperty.h"
#include "mtkRange.h"
//--------------------------------------------------------------------
using std::string;
using mtk::Property;
using mtk::Range;

//!Motor message data may be send as a windows message to communicate that something
//!is happening regarding the motor. It is up to the listening UI to communicate this
//!to the user, and/or deal with it.
class AB_CORE MotorMessageData
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
