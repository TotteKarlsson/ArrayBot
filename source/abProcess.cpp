#pragma hdrstop
#include "abProcess.h"
#include "mtkXMLUtils.h"
//---------------------------------------------------------------------------

using Poco::Timespan;
using namespace mtk;

Process::Process(const string& lbl, ProcessType pt)
:
mUnit(NULL),
mProcessName(lbl),
mPreDwellTime(0),
mPostDwellTime(0),
mTimeOut(60*Poco::Timespan::SECONDS),
mIsBeingProcessed(false),
mIsProcessed(false),
mIsStarted(false),
mProcessType(pt)
{}

string Process::getProcessType()
{
	return toString(mProcessType);
}

bool Process::start()
{
	Poco::Timestamp now;
	mStartTime = now;
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

XMLElement* Process::addToXMLDocument(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* processNode  	= doc.NewElement("process");
    XMLNode*    rootNode 		= doc.InsertFirstChild(processNode);

    //Attributes
    processNode->SetAttribute("type", getProcessType().c_str());
    processNode->SetAttribute("name", mProcessName.c_str());

    processNode->InsertEndChild(rootNode);
    docRoot->InsertEndChild(processNode);

    return processNode;
}

//Re implemented in derived processes
XMLElement* Process::addToXMLDocumentAsChild(mtk::XMLDocument& doc, mtk::XMLNode* docRoot)
{
	return NULL;
}

bool Process::isTimedOut()
{
//    if(isBeingProcessed())
//    {
//     	Poco::Timestamp now;
//        Poco::Timespan timeElapsed(now - mStartTime);
//        return ( timeElapsed > mTimeOut) ? true : false;
//    }
//    else
//    {
//		return (Timespan(mEndTime - mStartTime) > mTimeOut) ? true : false;
//    }
	return false;
}
