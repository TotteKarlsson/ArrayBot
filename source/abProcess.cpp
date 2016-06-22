#pragma hdrstop
#include "abProcess.h"
//---------------------------------------------------------------------------

Process::Process(const string& lbl, ABObject* o)
:
mUnit(o),
mProcessName(lbl),
mDwellTime(0),
mTimeOut(60*Poco::Timespan::SECONDS)
{}

bool Process::isTimedOut()
{
//	bool res;
//    if(isActive())
//    {
//    	Timestamp now;
//		if((now - mStartTime) > mTimeOut)
//        {
//        	return true;
//        }
//        else
//        {
//        	return false;
//        }
//    }
//    else
//    {
//		return (mEndTime - mStartTime > mTimeOut) ? true : false;
//    }

	return false;
}
