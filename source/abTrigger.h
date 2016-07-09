#ifndef abTriggerH
#define abTriggerH
#include "abExporter.h"
#include "abABObject.h"
#include <string>
//---------------------------------------------------------------------------

using std::string;


enum TriggerCondition {tcLargerThan = 0, tcSmallerThan, tcEqualTo, tcLargerThanOrEqual, tcSmallerThanOrEqual};
enum TriggerAction	  {taStopImmediate = 0, taStopProfiled, taStart, taSetVelocity, taSetAcceleration};

class AB_CORE Trigger : public ABObject
{
    public:
                                Trigger(const string& name, TriggerCondition c, TriggerAction ta);
		virtual                 ~Trigger(){}

        virtual bool  			test(double){return false;}
        virtual bool  			test(int)   {return false;}

		bool                    isTriggered(){return mIsTriggered;}

        						//!Any subclass need to implement
                                //an execute method
		virtual void	 		execute() = 0;
        virtual void	 		reset() {mIsTriggered = false;}


    protected:
        bool					mIsTriggered;

        TriggerCondition        mTriggerCondition;
    	TriggerAction			mTriggerAction;
        string					mName;
};

#endif
