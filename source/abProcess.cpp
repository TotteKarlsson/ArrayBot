#pragma hdrstop
#include "abProcess.h"
//---------------------------------------------------------------------------

using Poco::Timespan;
Process::Process(const string& lbl, ABObject* o)
:
mUnit(o),
mProcessName(lbl),
mPreDwellTime(0),
mPostDwellTime(0),
mTimeOut(60*Poco::Timespan::SECONDS),
mIsBeingProcessed(false),
mIsProcessed(false),
mIsStarted(false)
{}


bool Process::start()
{
	mIsStarted = true;
	mIsBeingProcessed = true;
    mIsProcessed = false;
    return true;
}

void Process::init()
{
	mIsBeingProcessed =  false;
    mIsProcessed = false;
    mIsStarted = false;
    mEndTime = mStartTime;
}

bool Process::stop()
{
	mIsBeingProcessed 	= false;
    mIsProcessed 		= false;
    return true;

}

bool Process::isTimedOut()
{
	bool res;
    if(isBeingProcessed())
    {
     	Poco::Timestamp now;
        Poco::Timespan timeElapsed(now - mStartTime);
        return ( timeElapsed > mTimeOut) ? true : false;
    }
    else
    {
		return (Timespan(mEndTime - mStartTime) > mTimeOut) ? true : false;
    }

	return false;
}
