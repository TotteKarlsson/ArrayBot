#pragma hdrstop
#include "abMove.h"
#include "abXYZUnit.h"
#include "mtkLogger.h"
#include "abArrayBot.h"
#include "abAPTMotor.h"
#include "abPosition.h"
#include <functional>

namespace ab
{

using namespace std::tr1;
using namespace mtk;
using namespace ab;

//---------------------------------------------------------------------------
Move::Move(const string& lbl, APTMotor* mtr, double maxVel, double acc)
:
Process(lbl, mtr),
mMaxVelocity(maxVel),
mAcceleration(acc),
mTrigger(mtr)
{}

void Move::init(ArrayBot& ab)
{
	Process::init(ab);
//    mTrigger.getSubjectName();

//   	APTMotor* mtr = ab.getMotorWithName(mTrigger.getObjectToTriggerName());
//    if(mtr)
//    {
////        if(mTrigger.getFireFunctionType() == fftMoveAbsolute)
//        {
////            FireFunction f = bind(&APTMotor::moveAbsolute, mtr,  25, 5, 5);
////            mTrigger.addFireFunction(f);
//        }
//    }
}

string Move::getMotorName()
{
	if(dynamic_cast<APTMotor*>(mSubject))
    {
    	return dynamic_cast<APTMotor*>(mSubject)->getName();
    }

	return "<none>";
}

void Move::assignUnit(ABObject* o)
{
	mSubject = NULL;

	//Check out what ABObject is
    if(dynamic_cast<ArrayBot*>(o))
    {
		ArrayBot* ab = dynamic_cast<ArrayBot*>(o);
        if(ab->getMotorWithName(mSubjectName))
        {
        	mSubject = ab->getMotorWithName(mSubjectName);
        }
    }
    else if(dynamic_cast<XYZUnit*>(o))
    {
    	//Look for motor
        XYZUnit* xyz = dynamic_cast<XYZUnit*>(o);
        if(xyz->getMotorWithName(mSubjectName))
        {
        	mSubject = xyz->getMotorWithName(mSubjectName);
        }
    }
    else if(dynamic_cast<APTMotor*>(o))
    {
    	APTMotor* m = dynamic_cast<APTMotor*>(o);
        mSubjectName = m->getName();
    	mSubject = m;
    }

    if(mSubject == NULL)
    {
   		Log(lError) << "Motor Unit is NULL for Move: "<<mProcessName;
    }
    else
    {
     	APTMotor* m = dynamic_cast<APTMotor*>(mSubject);
		mTrigger.setTestFunction(m->getPosition);
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
	APTMotor* o = dynamic_cast<APTMotor*>(mSubject);
    if(o)
    {
    	return o->isMotorCommandPending();
    }
	return false;
}

bool Move::isMotorActive()
{
	APTMotor* o = dynamic_cast<APTMotor*>(mSubject);
    if(o)
    {
    	return o->isActive();
    }

    return false;
}

bool Move::stop()
{
	Process::stop();
	XYZUnit* o = dynamic_cast<XYZUnit*>(mSubject);
    if(o)
    {
		return o->stopAll();
    }

	APTMotor* m = dynamic_cast<APTMotor*>(mSubject);
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
