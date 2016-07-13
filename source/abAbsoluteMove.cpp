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
    	m->setVelocity(mMaxVelocity);
        m->setAcceleration(mAcceleration);
        return m->moveAbsolute(mPosition.x());
    }
    return true;
}

XMLElement* AbsoluteMove::addToXMLDocumentAsChild(mtk::XMLDocument& doc, mtk::XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* processNode  	= doc.NewElement("process");
    XMLNode*    rootNode 		= doc.InsertFirstChild(processNode);

    //Attributes
    processNode->SetAttribute("name", mProcessName.c_str());
    processNode->SetAttribute("type", getTypeName());
	processNode->SetAttribute("motor_name", mMotorName.c_str());
	processNode->SetAttribute("final_position", toString(getPosition().x()).c_str());
	processNode->SetAttribute("max_velocity", toString(getMaxVelocity()).c_str());
	processNode->SetAttribute("acc", toString(getAcceleration()).c_str());
	processNode->SetAttribute("pre_dwell_time", toString(getPreDwellTime()).c_str());
	processNode->SetAttribute("post_dwell_time", toString(getPostDwellTime()).c_str());

    processNode->InsertEndChild(rootNode);
    docRoot->InsertEndChild(processNode);

    return processNode;
}

