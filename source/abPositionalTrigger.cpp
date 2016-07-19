#pragma hdrstop
#include "abPositionalTrigger.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"
#include "abTriggerFunction.h"
using namespace mtk;

//---------------------------------------------------------------------------
PositionalTrigger::PositionalTrigger(APTMotor* m, double position, LogicOperator lt)
:
Trigger(m),
mPosition(position),
mMotor(m)
{
	if(m)
    {
    	assignSubject(m);
        setTestFunction(m->getPosition);
    }

	mTriggerTimer.assignTimerFunction(triggerTest);
}

void PositionalTrigger::triggerTest()
{
	if(!mTestFunction)
	{
    	return;
    }

    double testVal = mTestFunction();
    if(test(testVal))
    {
	    mTriggerTimer.stop();
        execute();
       	string name("");
        if(mMotor)
	    {
        	name = mMotor->getName();
        }
        Log(lInfo) << "Positional trigger: \""<<name<<" was executed at trigger value: "<<testVal;
    }
}

bool PositionalTrigger::test(double val)
{
	switch(mTriggerConditionOperator)
    {
    	case loLargerThan: 			return val > mPosition;
    	case loLargerThanOrEqual: 	return val >= mPosition;
    	case loSmallerThan: 		return val < mPosition;
    	case loSmallerThanOrEqual:	return val < mPosition;

        default: Log(lError) << "Trigger condition not defined"; return false;
    }
}

void PositionalTrigger::execute()
{
    mIsTriggered = true;
    //Execute any functions in the fireFunction container
    if(mTriggerFunction)
    {
        mTriggerFunction->execute();
    }
}

XMLElement* PositionalTrigger::addToXMLDocumentAsChild(XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* pn	  			= doc.NewElement("trigger");
    XMLNode*    rootNode 		= doc.InsertFirstChild(pn);
    string 		test;

    //Attributes
    pn->SetAttribute("type", getTypeName().c_str());
    pn->SetAttribute("subject", mSubjectName.c_str());

	XMLElement* val = doc.NewElement("position");
    test = toString(mPosition);
    val->SetText(test.c_str());
	pn->InsertEndChild(val);

	val = doc.NewElement("operator");
    test = toString(mTriggerConditionOperator);
    val->SetText(test.c_str());
	pn->InsertEndChild(val);


    //Add trigger function(s)
    if(mTriggerFunction)
    {
		mTriggerFunction->addToXMLDocumentAsChild(doc, pn);
    }

    pn->InsertEndChild(rootNode);
    docRoot->InsertEndChild(pn);

    return pn;
}


