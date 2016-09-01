#pragma hdrstop
#include "abProcess.h"
#include "mtkXMLUtils.h"
#include "abProcessSequence.h"
//---------------------------------------------------------------------------

using Poco::Timespan;
using namespace mtk;

Process::Process(const string& lbl, ABObject* ao)
:
mSubject(ao),
mProcessName(lbl),
mPreDwellTime(0),
mPostDwellTime(0),
mTimeOut(60*Poco::Timespan::SECONDS),
mIsBeingProcessed(false),
mIsProcessed(false),
mIsStarted(false),
mProcessSequence(NULL),
mInfoText("Process Information..(click me!)")
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

void Process::init(ArrayBot& ab)
{
	mIsBeingProcessed 	=  false;
    mIsProcessed 		= false;
    mIsStarted 			= false;
    mEndTime 			= mStartTime;
}

bool Process::stop()
{
	mIsBeingProcessed 	= false;
    mIsProcessed 		= false;
    return true;
}

bool Process::write()
{
	if(mProcessSequence)
    {
    	return mProcessSequence->write();
    }
	return false;
}

XMLElement* Process::addToXMLDocument(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* processNode  	= doc.NewElement("process");
    XMLNode*    rootNode 		= doc.InsertFirstChild(processNode);

    //Attributes
    processNode->SetAttribute("type", getProcessType().c_str());
    processNode->SetAttribute("name", mProcessName.c_str());

	XMLElement* dataval1 = doc.NewElement("info");
    dataval1->SetText(mInfoText.c_str());
	processNode->InsertEndChild(dataval1);

    processNode->InsertEndChild(rootNode);
    docRoot->InsertEndChild(processNode);

    return processNode;
}

//Re implemented in derived processes
XMLElement* Process::addToXMLDocumentAsChild(XMLDocument& doc, XMLNode* docRoot)
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
