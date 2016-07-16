#pragma hdrstop
#include "abTrigger.h"
//---------------------------------------------------------------------------

using namespace mtk;
using Poco::Timespan;

Trigger::Trigger(const string& s, const string& objDevice)
:
mSubjectName(s),
mObjectToTriggerName(objDevice),
mIsTriggered(false),
mTriggerConditionOperator(loLargerThan),
mTriggerTimer(Poco::Timespan(100*Poco::Timespan::MILLISECONDS)),
mTestFunction(NULL)
{
	mTriggerTimer.assignTimerFunction(triggerTest);
}

bool Trigger::enable()
{
    mIsTriggered = false;
	mTriggerTimer.start();
    return true;
}

bool Trigger::disable()
{
    mIsTriggered = false;
	mTriggerTimer.stop();
    return true;
}

void Trigger::setTestFunction(triggerTestFunctionFPtr func)
{
    mTestFunction = func;
}

void Trigger::reset()
{
	mIsTriggered = false;
}

void Trigger::setupFireFunction(FireFunction f)
{
	mFireFunction = f;
}
