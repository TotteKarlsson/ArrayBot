#pragma hdrstop
#include "atHomeMotor.h"
#include "atAPTMotor.h"
#include "atProcessSequence.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
using namespace dsl;


namespace at
{
    HomeMotor::HomeMotor(const string& lbl, APTMotor* mtr)
    :
    at::Move(lbl, mtr, 1, 1)
    {
    	mProcessType = ptHomeMotor;
    }

    const string HomeMotor::getTypeName() const
    {
    	return "homeMotor";
    }

    bool HomeMotor::write()
    {
    	if(mProcessSequence)
        {
        	return mProcessSequence->write();
        }
    	return false;
    }

    bool HomeMotor::isDone()
    {
    	APTMotor* o = dynamic_cast<APTMotor*>(mSubject);
    //    Log(lDebug) << "Elapsed process time: "<<getElapsedTimeSinceStart().totalMilliseconds();

        //The motor takes really long time to set its home flag to false on start. So, don't check for the first 400ms or so
        bool timeHasElapsed = getElapsedTimeSinceStart() > Poco::Timespan::MILLISECONDS * 400;
        if(o && o->getNumberOfQueuedCommands() == 0 && timeHasElapsed)
        {
        	return o->isHomed();
        }

        return false;
    }

    bool HomeMotor::start()
    {
    	APTMotor* m = dynamic_cast<APTMotor*>(mSubject);
        if(m)
        {
            //This will start the processs internal time checking that checks for
            //process events
            Process::start();
        	m->home(true);
            return true;
        }

        return false;
    }

    //Resume is similar to start...
    bool HomeMotor::resume()
    {
    	APTMotor* m = dynamic_cast<APTMotor*>(mSubject);
        if(m)
        {
            Process::resume();
    		m->home();
            return true;
        }

        return false;
    }

    XMLElement* HomeMotor::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
    {
    	XMLElement* dataval1 = doc.NewElement("motor_name");
        dataval1->SetText(mSubjectName.c_str());
    	docRoot->InsertEndChild(dataval1);

    	dataval1 = doc.NewElement("pre_dwell_time");
        dataval1->SetText(dsl::toString(getPreDwellTime()).c_str());
    	docRoot->InsertEndChild(dataval1);

    	dataval1 = doc.NewElement("post_dwell_time");
        dataval1->SetText(dsl::toString(getPostDwellTime()).c_str());
    	docRoot->InsertEndChild(dataval1);

        docRoot->InsertEndChild(dataval1);
        return dataval1;
    }
}

