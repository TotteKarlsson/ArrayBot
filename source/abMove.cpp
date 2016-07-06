#pragma hdrstop
#include "abMove.h"
#include "abXYZUnit.h"
#include "abAPTMotor.h"
#include "abPosition.h"
#include "mtkLogger.h"
#include "abArrayBot.h"

namespace ab
{

using namespace mtk;
using namespace ab;

//---------------------------------------------------------------------------
Move::Move(const string& lbl, MoveType type, const ab::Position& p, double maxVel, double acc, double dwellTime)
:
Process(lbl),
mPosition(p),
mPositionResolution(1.0e-3),
mMoveType(type),
mMaxVelocity(0),
mAcceleration(0)
{
	mProcessType = ptMove;
}

void Move::assignUnit(ABObject* o)
{
	mUnit = NULL;

	//Check out what ABObject is
    if(dynamic_cast<ArrayBot*>(o))
    {
		ArrayBot* ab = dynamic_cast<ArrayBot*>(o);
        if(ab->getMotorWithName(mMotorName))
        {
        	mUnit = ab->getMotorWithName(mMotorName);
        }
    }
    else if(dynamic_cast<XYZUnit*>(o))
    {
    	//Look for motor
        XYZUnit* xyz = dynamic_cast<XYZUnit*>(o);
        if(xyz->getMotorWithName(mMotorName))
        {
        	mUnit = xyz->getMotorWithName(mMotorName);
        }
    }
    else if(dynamic_cast<APTMotor*>(o))
    {
    	APTMotor* m = dynamic_cast<APTMotor*>(o);
        mMotorName = m->getName();
    	mUnit = m;
    }

    if(mUnit == NULL)
    {
   		Log(lError) << "Motor Unit is NULL for Move: "<<mProcessName;
    }
}

bool Move::isBeingProcessed()
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

bool Move::isProcessed()
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
    else
    {
        return false;
    }

	return false;
}

bool Move::isMotorCommandPending()
{
	APTMotor* o = dynamic_cast<APTMotor*>(mUnit);
    if(o)
    {
    	return o->isMotorCommandPending();
    }
	return false;
}

bool Move::isDone()
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

bool Move::isMotorActive()
{
	APTMotor* o = dynamic_cast<APTMotor*>(mUnit);
    if(o)
    {
    	return o->isActive();
    }

    return false;
}

XMLElement* Move::addToXMLDocumentAsChild(mtk::XMLDocument& doc, mtk::XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* processNode  	= doc.NewElement("process");
    XMLNode*    rootNode 		= doc.InsertFirstChild(processNode);

    //Attributes
    processNode->SetAttribute("name", mProcessName.c_str());
    processNode->SetAttribute("type", toString(mMoveType).c_str());
	processNode->SetAttribute("motor_name", mMotorName.c_str());
	processNode->SetAttribute("final_position", toString(getPosition().x()).c_str());
	processNode->SetAttribute("max_velocity", toString(getMaxVelocity()).c_str());
	processNode->SetAttribute("acc", toString(getAcceleration()).c_str());
	processNode->SetAttribute("pre_dwell_time", toString(getPreDwellTime()).c_str());
	processNode->SetAttribute("post_dwell_time", toString(getPostDwellTime()).c_str());

    //Elements
//    XMLElement* elem = doc.NewElement("process_name");
//    processNode->InsertFirstChild(elem);
//        elem->SetText(mProcessName.c_str());
//    processNode->InsertEndChild(elem);
//
//    //Elements
//    elem = doc.NewElement("process_type");
//    processNode->InsertFirstChild(elem);
//        elem->SetText(getProcessType().c_str());
//    processNode->InsertEndChild(elem);

    processNode->InsertEndChild(rootNode);
    docRoot->InsertEndChild(processNode);

    return processNode;
}

bool Move::start()
{
	Process::start();
	XYZUnit* o = dynamic_cast<XYZUnit*>(mUnit);
    if(o)
    {
		return o->moveAbsolute(mPosition);
    }

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

    return false;
}

bool Move::stop()
{
	Process::stop();
	XYZUnit* o = dynamic_cast<XYZUnit*>(mUnit);
    if(o)
    {
		return o->stopAll();
    }

	APTMotor* m = dynamic_cast<APTMotor*>(mUnit);
    if(m)
    {
    	m->stop(false);
        return true;
    }

    return false;
}

bool Move::undo()
{
	Position p("undo pos", mPosition.x() * -1, mPosition.y() * -1, mPosition.z() * -1);

	XYZUnit* unit = dynamic_cast<XYZUnit*>(mUnit);
    if(unit)
    {
		return unit->moveAbsolute(p);
    }

	return false;
}

MoveType toMoveType(const string& mt)
{
	if(mt == "ABSOLUTE_MOVE")
    {
    	return mtAbsolute;
    }

	if(mt == "RELATIVE_MOVE")
    {
    	return mtRelative;
    }

    return mtUnknown;
}

string toString(MoveType mt)
{
	switch(mt)
    {
    	case mtAbsolute: 	return "ABSOLUTE_MOVE";
    	case mtRelative: 	return "RELATIVE_MOVE";
        default:    		return "UNKNOWN_MOVE";
    }
}

}
