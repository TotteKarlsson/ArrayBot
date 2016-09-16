#pragma hdrstop
#include "abArduinoServerCommand.h"
#include "abXYZUnit.h"
#include "mtkLogger.h"
#include "abArrayBot.h"
#include "abAPTMotor.h"
#include "abPosition.h"
#include "abTriggerFunction.h"
#include "abArduinoClient.h"


using namespace mtk;
using namespace ab;

//---------------------------------------------------------------------------
ArduinoServerCommand::ArduinoServerCommand(const string& lbl)
:
Process(lbl, NULL),
mTrigger(NULL)
{}

const string ArduinoServerCommand::getTypeName() const
{
	return "arduinoServerCommand";
}

void ArduinoServerCommand::init(ArrayBot& ab)
{
	Process::init(ab);
	mArduinoClient = ab.getArduinoClient();

//    //Setup any triggers
//    if(mTrigger && mTrigger->getTriggerFunction())
//    {
//        TriggerFunction* tf = mTrigger->getTriggerFunction();
//        if(dynamic_cast<ArduinoServerCommandAbsolute*>(tf))
//        {
//        	ArduinoServerCommandAbsolute* ma = dynamic_cast<ArduinoServerCommandAbsolute*>(tf);
//            ma->setMotor(ab.getMotorWithName(ma->getMotorName()));
//        }
//    }
}

//void ArduinoServerCommand::addTrigger(Trigger* t)
//{
//	mTrigger = t;
//    mTrigger->assignSubject(this);
//}
//
//void ArduinoServerCommand::deleteTrigger(Trigger* t)
//{
//	delete mTrigger;
//    mTrigger = NULL;
//}

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
		bool res = mArduinoClient->send(mCommand);
		if(res)
        {
        	Log(lDebug3) << "ArduinoServerCommand was executed successfully ("<<mCommand;
        }
        else
        {
        	Log(lError) << "ArduinoServerCommand was executed unsuccessfully ("<<mCommand;
        }

        mIsProcessed = true;
        //This will start the processs internal timer that checks for
        //process events
        Process::start();
        return res;
    }

    return false;
}

XMLElement* ArduinoServerCommand::addToXMLDocumentAsChild(XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* pn	  			= doc.NewElement("process");
    XMLNode*    rootNode 		= doc.InsertFirstChild(pn);

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
    dataval1->SetText(toString(getPostDwellTime()).c_str());
	pn->InsertEndChild(dataval1);

//	//Add trigger
//    if(mTrigger)
//    {
//    	mTrigger->addToXMLDocumentAsChild(doc, pn);
//    }

    pn->InsertEndChild(rootNode);
    docRoot->InsertEndChild(pn);

    return pn;
}

bool ArduinoServerCommand::isDone()
{
    return mIsProcessed;
}




