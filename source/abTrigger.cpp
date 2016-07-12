#pragma hdrstop
#include "abTrigger.h"
//---------------------------------------------------------------------------

using namespace mtk;
using Poco::Timespan;

Trigger::Trigger(const string& name, TriggerCondition c, triggerTestFunctionFPtr ttf)
:
mName(name),
mIsTriggered(false),
mTriggerCondition(c),
mTriggerTimer(Poco::Timespan(10*Poco::Timespan::MILLISECONDS)),
mTestFunction(ttf)
{
	mTriggerTimer.assignTimerFunction(triggerTest);
}

bool Trigger::load()
{
    mIsTriggered = false;
	mTriggerTimer.start();
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

void Trigger::addFireFunction(FireFunction f)
{
	mFireFunction = f;
}
