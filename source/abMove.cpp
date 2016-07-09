#pragma hdrstop
#include "abMove.h"
#include "abXYZUnit.h"
#include "mtkLogger.h"
#include "abArrayBot.h"
#include "abAPTMotor.h"
#include "abPosition.h"

namespace ab
{

using namespace mtk;
using namespace ab;

//---------------------------------------------------------------------------
Move::Move(const string& lbl, double maxVel, double acc)
:
Process(lbl, ptMove),
mMaxVelocity(maxVel),
mAcceleration(acc)
{}

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

bool Move::isMotorActive()
{
	APTMotor* o = dynamic_cast<APTMotor*>(mUnit);
    if(o)
    {
    	return o->isActive();
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
	return false;
}

}
