#pragma hdrstop
#include "abPositionalTrigger.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"

using namespace mtk;

//---------------------------------------------------------------------------
PositionalTrigger::PositionalTrigger(const string& s, const string& o)
:
Trigger(s, o),
mPosition(-1)
{
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
        Log(lInfo) << "Positional trigger: \""<<getSubjectName()<<" was executed at trigger value: "<<testVal;
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
    if(mFireFunction)
    {
        mFireFunction.execute();
    }
}

XMLElement* PositionalTrigger::addToXMLDocumentAsChild(XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* pn	  			= doc.NewElement("trigger");
    XMLNode*    rootNode 		= doc.InsertFirstChild(pn);

    //Attributes
    pn->SetAttribute("type", getTypeName());
    pn->SetAttribute("subject", mSubjectName.c_str());

	XMLElement* val = doc.NewElement("position");
    string test = toString(mPosition);
    val->SetText(test.c_str());
	pn->InsertEndChild(val);

	val = doc.NewElement("operator");
    test = toString(mTriggerConditionOperator);
    val->SetText(test.c_str());
	pn->InsertEndChild(val);

	val = doc.NewElement("object_to_trigger");
    test = mObjectToTriggerName;
    val->SetText(test.c_str());
	pn->InsertEndChild(val);

	val = doc.NewElement("fire_function");
    test = toString(mFireFunctionType);
    val->SetText(test.c_str());
	pn->InsertEndChild(val);

    pn->InsertEndChild(rootNode);
    docRoot->InsertEndChild(pn);

    return pn;
}


