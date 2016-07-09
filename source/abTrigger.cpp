#pragma hdrstop
#include "abTrigger.h"
//---------------------------------------------------------------------------

Trigger::Trigger(const string& name, TriggerCondition c, TriggerAction ta)
:
mTriggerAction(ta),
mName(name),
mIsTriggered(false),
mTriggerCondition(c)
{}
