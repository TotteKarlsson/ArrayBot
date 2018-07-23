#pragma hdrstop
#include "atArduinoServerCommand.h"
#include "arraybot/atXYZUnit.h"
#include "dslLogger.h"
//#include "atArrayBot.h"
//#include "atAPTMotor.h"
//#include "atTriggerFunction.h"
#include "atArduinoClient.h"

namespace at
{

using namespace dsl;

//---------------------------------------------------------------------------
ArduinoServerCommand::ArduinoServerCommand(const string& lbl)
:
Process(lbl, NULL),
mTrigger(NULL),
mCommand("ENABLE_PUFFER"),
mArduinoClient(NULL)
{}

ArduinoServerCommand::~ArduinoServerCommand()
{}

const string ArduinoServerCommand::getTypeName() const
{
	return "arduinoServerCommand";
}

void ArduinoServerCommand::init(ArrayBot& ab)
{
	Process::init(ab);
//	mArduinoClient = ab.getArduinoClient();
}

bool ArduinoServerCommand::isBeingProcessed()
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

bool ArduinoServerCommand::isProcessed()
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

bool ArduinoServerCommand::undo()
{
	return false;
}

bool ArduinoServerCommand::start()
{
    if(mArduinoClient)
    {
    	stringstream cmd;
        cmd << "[" << mCommand << "]";
		int res = mArduinoClient->send(cmd.str());
		if(res != -1)
        {
        	Log(lDebug3) << "ArduinoServerCommand was executed successfully ("<<mCommand;
        }
        else
        {
        	Log(lError) << "ArduinoServerCommand was executed unsuccessfully ("<<mCommand;
        }

        Process::start();
        mIsProcessed = true;

        //This will start the processs internal timer that checks for
        //process events
        return res;
    }

    return false;
}

XMLElement* ArduinoServerCommand::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* pn	  	 = doc.NewElement("process");
    XMLNode*    rootNode = doc.InsertFirstChild(pn);

    //Attributes
    pn->SetAttribute("type", getTypeName().c_str());
    pn->SetAttribute("name", mProcessName.c_str());

	XMLElement* dataval1 = doc.NewElement("info");
    dataval1->SetText(mInfoText.c_str());
	pn->InsertEndChild(dataval1);

	dataval1 = doc.NewElement("command");
    dataval1->SetText(mCommand.c_str());
	pn->InsertEndChild(dataval1);

	dataval1 = doc.NewElement("pre_dwell_time");
    dataval1->SetText(toString(getPreDwellTime()).c_str());
	pn->InsertEndChild(dataval1);

	dataval1 = doc.NewElement("post_dwell_time");
    dataval1->SetText(dsl::toString(getPostDwellTime()).c_str());
	pn->InsertEndChild(dataval1);

    pn->InsertEndChild(rootNode);
    docRoot->InsertEndChild(pn);
    return pn;
}

bool ArduinoServerCommand::isDone()
{
    return mIsProcessed;
}

}

