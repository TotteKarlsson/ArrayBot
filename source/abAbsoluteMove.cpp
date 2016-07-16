#pragma hdrstop
#include "abAbsoluteMove.h"
#include "abAPTMotor.h"
#include "abPosition.h"
//---------------------------------------------------------------------------

AbsoluteMove::AbsoluteMove(const string& lbl, const ab::Position& p, double maxVel, double acc)
:
ab::Move(lbl, maxVel, acc),
mPosition(p),
mPositionResolution(1.0e-3)
{}

const char* AbsoluteMove::getTypeName() const
{
	return "absoluteMove";
}

bool AbsoluteMove::isDone()
{
	APTMotor* o = dynamic_cast<APTMotor*>(mUnit);
    if(o)
    {
    	//If still moving we cannot be done(!)
    	if(o->isActive())
        {
        	return false;
        }

    	double p = o->getPosition();
    	return (isEqual(p, mPosition.x(), mPositionResolution)) ? true : false;
    }

    return false;
}

bool AbsoluteMove::start()
{
	Process::start();

	APTMotor* m = dynamic_cast<APTMotor*>(mUnit);
    if(m)
    {
		if(mMaxVelocity == 0 || mAcceleration == 0)
        {
        	Log(lError) << "Move cannot be executed with zero velocity or acceleration";
            return false;
        }

        if(mTrigger.getObjectToTriggerName() != "")
        {

        	APTMotor* motor = dynamic_cast<APTMotor*>(this->getUnit());
            if(motor)
            {
                //The trigger is now observing the motor..
                getTrigger().setTestFunction(motor->getPosition);
            }


        	mTrigger.enable();
        }
    	m->setVelocity(mMaxVelocity);
        m->setAcceleration(mAcceleration);
        return m->moveToPosition(mPosition.x());
    }
    return true;
}

XMLElement* AbsoluteMove::addToXMLDocumentAsChild(XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* pn	  			= doc.NewElement("process");
    XMLNode*    rootNode 		= doc.InsertFirstChild(pn);

    //Attributes
    pn->SetAttribute("type", getTypeName());
    pn->SetAttribute("name", mProcessName.c_str());

	XMLElement* dataval1 = doc.NewElement("motor_name");
    dataval1->SetText(mMotorName.c_str());
	pn->InsertEndChild(dataval1);

	dataval1 = doc.NewElement("final_position");
    dataval1->SetText(toString(getPosition().x()).c_str());
	pn->InsertEndChild(dataval1);

 	dataval1 = doc.NewElement("max_velocity");
    dataval1->SetText(toString(getMaxVelocity()).c_str());
	pn->InsertEndChild(dataval1);

  	dataval1 = doc.NewElement("acc");
    dataval1->SetText(toString(getAcceleration()).c_str());
	pn->InsertEndChild(dataval1);

	dataval1 = doc.NewElement("pre_dwell_time");
    dataval1->SetText(toString(getPreDwellTime()).c_str());
	pn->InsertEndChild(dataval1);

	dataval1 = doc.NewElement("post_dwell_time");
    dataval1->SetText(toString(getPostDwellTime()).c_str());
	pn->InsertEndChild(dataval1);

	//Add trigger
    mTrigger.addToXMLDocumentAsChild(doc, pn);

    pn->InsertEndChild(rootNode);
    docRoot->InsertEndChild(pn);

    return pn;
}

