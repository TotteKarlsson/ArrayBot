#pragma hdrstop
#include "atTimeDelay.h"
#include "dslLogger.h"
#include "atXYZUnit.h"
#include "apt/atAPTMotor.h"
#include "apt/atMove.h"
#include "dslXMLUtils.h"
#include "atProcessSequence.h"
using namespace dsl;
using namespace at;
using namespace tinyxml2;

namespace at
{

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

    bool TimeDelay::write()
    {
    	if(mProcessSequence)
        {
        	return mProcessSequence->write();
        }
    	return false;
    }

    XMLElement* TimeDelay::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
    {
        //Create XML for saving to file
    	XMLElement* delay = doc.NewElement("delay");
    	delay->SetText(dsl::toString( (long) mTimeDelay.totalMicroseconds()).c_str() );

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

    bool TimeDelay::start()
    {
    	return Process::start();
    }

    bool TimeDelay::stop()
    {
    	return Process::stop();
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

}
