#pragma hdrstop
#include "atTrigger.h"
#include "apt/atAPTMotor.h"
#include "atXYZUnit.h"
//---------------------------------------------------------------------------

using namespace dsl;
using Poco::Timespan;

namespace at
{

    Trigger::Trigger(ATObject* s, LogicOperator lt)
    :
    mSubject(s),
    mIsTriggered(false),
    mTriggerTimer(Poco::Timespan(100*Poco::Timespan::MILLISECONDS), triggerTest),
    mTestFunction(NULL),
    mTriggerConditionOperator(lt),
    mTriggerFunction(NULL)
    {}

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

    string Trigger::getSubjectName()
    {
    	if(mSubject)
        {
        	if(dynamic_cast<APTMotor*>(mSubject))
            {
    	        dynamic_cast<APTMotor*>(mSubject)->getName();
            }

        	if(dynamic_cast<XYZUnit*>(mSubject))
            {
    	        dynamic_cast<XYZUnit*>(mSubject)->getName();
            }
        }
        return "<none>";
    }

    void Trigger::setTestFunction(triggerTestFunctionFPtr func)
    {
        mTestFunction = func;
    }

    void Trigger::reset()
    {
    	mIsTriggered = false;
    }

    void Trigger::assignTriggerFunction(TriggerFunction* f)
    {
    	mTriggerFunction = f;
    }

}
