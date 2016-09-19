#pragma hdrstop
#include "abTimeDelay.h"
#include "abXYZUnit.h"
#include "abAPTMotor.h"
//#include "abPosition.h"
#include "mtkLogger.h"
#include "abMove.h"
#include "mtkXMLUtils.h"


using namespace mtk;
using namespace ab;
using namespace tinyxml2;

//---------------------------------------------------------------------------
TimeDelay::TimeDelay(const string& lbl, Poco::Timespan ts)
:
Process(lbl, NULL),
mTimeDelay(ts)
{
	mProcessType = ptTimeDelay;
}

void TimeDelay::clear()
{}

const string TimeDelay::getTypeName() const
{
	return "timeDelay";
}

XMLElement* TimeDelay::addToXMLDocumentAsChildProcess(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file
	XMLElement* delay = doc.NewElement("delay");
	delay->SetText(mtk::toString( (long) mTimeDelay.totalMicroseconds()).c_str() );

    docRoot->InsertEndChild(delay);
    return delay;
}

bool TimeDelay::isBeingProcessed()
{
	if(isDone())
    {
		mIsBeingProcessed = false;
        mIsProcessed = true;
       	Timestamp now;
        mEndTime = now;
    }

    return mIsBeingProcessed;
}

bool TimeDelay::isProcessed()
{
    if(mIsProcessed == true)
    {
    	return true;
    }

    if(isDone())
    {
        //Consider this process to be "processed"
        mIsProcessed 		= true;
        mIsBeingProcessed 	= false;
        return true;
    }

	return false;
}

bool TimeDelay::start()
{
	return Process::start();
}

bool TimeDelay::stop()
{
	return Process::stop();
}

bool TimeDelay::isDone()
{
	if(!mIsStarted)
    {
    	return false;
    }

	Poco::Timestamp now;
    Poco::Timespan timeElapsed(now - mStartTime);
    return timeElapsed > mTimeDelay ? true : false;
}
