#pragma hdrstop
#include "abPositionalTrigger.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"

using namespace mtk;

//---------------------------------------------------------------------------

PositionalTrigger::PositionalTrigger(const string& name, TriggerCondition c, double position, TriggerAction ta, APTMotor* mtr)
:
Trigger(name, c, ta),
mMotor(mtr),
mMotorPositionalTriggerPoint(position)
{}

bool PositionalTrigger::test(double val)
{
	switch(mTriggerCondition)
    {
    	case tcLargerThan: 			return val > mMotorPositionalTriggerPoint;
    	case tcLargerThanOrEqual: 	return val >= mMotorPositionalTriggerPoint;
        default: Log(lError) << "Trigger condition not defined"; return false;
    }
}

void PositionalTrigger::execute()
{
	Log(lInfo) << "Executing trigger: "<<mName;
    mIsTriggered = true;

    if(!mMotor)
    {
    	return;
    }

    switch(mTriggerAction)
    {
    	case taStopImmediate: 	mMotor->stop(); break;
    	case taStopProfiled: 	mMotor->stop(); break;
    	case taSetVelocity:
        	mMotor->setVelocity(mNewVelocity);
            mMotor->moveAbsolute(mMotor->getDesiredPosition());
        break;
    }
}


