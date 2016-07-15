#pragma hdrstop
#include "abPositionalTrigger.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"

using namespace mtk;

//---------------------------------------------------------------------------
PositionalTrigger::PositionalTrigger(const string& name, triggerTestFunctionFPtr f, TriggerConditionOperator c, double tVal)
:
Trigger(name, f,  c),
mMotorPositionalTriggerPoint(tVal)
{
	mTriggerTimer.assignTimerFunction(triggerTest);
}

bool PositionalTrigger::test(double val)
{
	switch(mTriggerConditionOperator)
    {
    	case tcLargerThan: 			return val > mMotorPositionalTriggerPoint;
    	case tcLargerThanOrEqual: 	return val >= mMotorPositionalTriggerPoint;
        default: Log(lError) << "Trigger condition not defined"; return false;
    }
}

void PositionalTrigger::triggerTest()
{
	if(mTestFunction)
	{
    	double testVal = mTestFunction();
    	if(test(testVal))
    	{
	        mTriggerTimer.stop();
			execute();
		   	Log(lInfo) << "Positional trigger: \""<<getName()<<" executed at trigger value: "<<testVal;
        }
    }
}

void PositionalTrigger::execute()
{
    mIsTriggered = true;

    //Execute any functions in the fireFunction container
    if(mFireFunction)
    {
        mFireFunction(0,0,0);
    }

}

