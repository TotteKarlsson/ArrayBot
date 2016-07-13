#pragma hdrstop
#include "abTimeDelay.h"
#include "abXYZUnit.h"
#include "abAPTMotor.h"
#include "abPosition.h"
#include "mtkLogger.h"
#include "abMove.h"
using namespace mtk;
using namespace ab;

//---------------------------------------------------------------------------
TimeDelay::TimeDelay(const string& lbl, Poco::Timespan ts)
:
Process(lbl, ptTimeDelay),
mTimeDelay(ts)
{
	mProcessType = ptTimeDelay;
}

void TimeDelay::clear()
{}

const char* TimeDelay::getTypeName() const
{
	return "timeDelay";
}

XMLElement* TimeDelay::addToXMLDocumentAsChildProcess(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* processNode  = doc.NewElement("processes");
//    XMLNode*    rootNode = doc.InsertFirstChild(processNode);
//
//    //Attributes
//    //processNode->SetAttribute("id", getID().toString().c_str());
//
//	for(int i = 0; i < mMoves.size(); i++)
//    {
//    	Move* lm = mMoves[i];
//        lm->addToXMLDocumentAsChild(doc, rootNode);
//    }
//
//    processNode->InsertEndChild(rootNode);
//    docRoot->InsertEndChild(processNode);

    return processNode;
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
    return true;
}
