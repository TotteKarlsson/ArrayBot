#pragma hdrstop
#include "abLinearMove.h"
#include "abXYZUnit.h"
#include "abAPTMotor.h"
#include "abPosition.h"
#include "mtkLogger.h"


using namespace mtk;
using namespace ab;
//---------------------------------------------------------------------------
LinearMove::LinearMove(const string& lbl, MoveType type, const ab::Position& p, double maxVel, double acc, double dwellTime)
:
Process(lbl),
mMoveType(type),
mPosition(p),
mMaxVelocity(0),
mAcceleration(0),
mPositionResolution(1.0e-1)
{
	mProcessType = ptLinearMove;
}

void LinearMove::assignUnit(ABObject* o)
{
	mUnit = NULL;

	//Check out what ABObject is
    if(dynamic_cast<XYZUnit*>(o))
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
   		Log(lError) << "Motor Unit is NULL for LinearMove: "<<mProcessName;
    }
}

bool LinearMove::isBeingProcessed()
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

bool LinearMove::isProcessed()
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

bool LinearMove::commandPending()
{
	APTMotor* o = dynamic_cast<APTMotor*>(mUnit);
    if(o)
    {
    	return o->commandsPending();
    }
	return false;
}

bool LinearMove::isDone()
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

bool LinearMove::isMotorActive()
{
	APTMotor* o = dynamic_cast<APTMotor*>(mUnit);
    if(o)
    {
    	return o->isActive();
    }

    return false;
}

XMLElement* LinearMove::addToXMLDocumentAsChild(mtk::XMLDocument& doc, mtk::XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* processNode  	= doc.NewElement("process");
    XMLNode*    rootNode 		= doc.InsertFirstChild(processNode);

    //Attributes
    processNode->SetAttribute("name", mProcessName.c_str());
    processNode->SetAttribute("type", getProcessType().c_str());
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

//bool LinearMove::write(IniSection* sec)
//{
//    double x = getPosition().x();
//    IniKey* key = sec->createKey("PROCESS_TYPE", 	toString(getMoveType()));
//    key = sec->createKey("MOTOR_NAME",   			toString(mMotorName));
//    key = sec->createKey("POSITION", 				toString(x));
//    key = sec->createKey("POSITION_NAME",  			getPosition().getLabel());
//    key = sec->createKey("MAX_VELOCITY", 			toString(getMaxVelocity()));
//    key = sec->createKey("ACCELERATION", 			toString(getAcceleration()));
//    key = sec->createKey("PRE_DWELL_TIME",   		toString(getPreDwellTime()));
//    key = sec->createKey("POST_DWELL_TIME",   		toString(getPostDwellTime()));
//    return true;
//}
//
//bool LinearMove::read(IniSection* sec)
//{
//	if(!sec)
//	{
//    	return false;
//    }
//
//	IniKey* key = sec->getKey("MOVE_TYPE");
//
//    if(key)
//    {
//        mMoveType = toMoveType(key->mValue);;
//    }
//
//    key = sec->getKey("MOTOR_NAME");
//    if(key)
//    {
//        mMotorName = key->mValue;
//    }
//
//    key = sec->getKey("POSITION");
//    if(key)
//    {
//	    mPosition = Position(mPosition.getLabel(), key->asFloat(), 0.0 , 0.0);
//    }
//
//    key = sec->getKey("POSITION_NAME");
//    if(key)
//    {
//        mPosition.setLabel(key->mValue);
//    }
//
//    key = sec->getKey("MAX_VELOCITY", true);
//    if(key)
//    {
//	    mMaxVelocity = key->asFloat();
//    }
//
//    key = sec->getKey("ACCELERATION", true);
//    if(key)
//    {
//        mAcceleration = key->asFloat();
//    }
//
//    key = sec->getKey("PRE_DWELL_TIME", true);
//    if (key)
//    {
//		mPreDwellTime = key->asFloat();
//    }
//
//    key = sec->getKey("POST_DWELL_TIME", true);
//    if (key)
//    {
//		mPostDwellTime = key->asFloat();
//    }
//
//    return true;
//}

bool LinearMove::start()
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

bool LinearMove::stop()
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

bool LinearMove::undo()
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

string	toString(MoveType mt)
{
	if(mt == mtAbsolute)
    {
    	return "ABSOLUTE_MOVE";
    }

	if(mt == mtRelative)
    {
    	return "RELATIVE_MOVE";
    }

    return "UNKNOWN_MOVE";
}
