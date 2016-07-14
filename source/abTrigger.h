#ifndef abTriggerH
#define abTriggerH
#include "abExporter.h"
#include "abABObject.h"
#include <string>
#include "mtkTimer.h"
#include <functional>
#include <vector>

//---------------------------------------------------------------------------
using std::string;
using std::vector;
using std::tr1::function;


typedef double (__closure *triggerTestFunctionFPtr)();
typedef function<void (const double& nr) > 	FireFunction;

enum TriggerConditionOperator {tcLargerThan = 0, tcSmallerThan, tcEqualTo, tcLargerThanOrEqual, tcSmallerThanOrEqual};


class AB_CORE Trigger : public ABObject
{
    public:
                                            Trigger(const string& name, TriggerConditionOperator c, triggerTestFunctionFPtr f);
		virtual                             ~Trigger(){}
		string					            getName(){return mName;}

        						            //!Enable 'loads' the trigger.
        virtual bool			            enable();

        						            //!Disable disables the trigger.
        virtual bool			            disable();

        virtual bool  			            test(double){return false;}
        virtual bool  			            test(int)   {return false;}
        virtual void  			            triggerTest() {;}
        virtual void			            setTestFunction(triggerTestFunctionFPtr f);

		virtual void						addFireFunction(FireFunction f);
		bool                                isTriggered(){return mIsTriggered;}

        						            //!Any subclass need to implement
                                            //an execute method
		virtual void	 		            execute() = 0;
        virtual void	 		            reset();

    protected:
    										//!The mIsTriggered is set to true in case the trigger been fired
        bool					            mIsTriggered;

    										//!The Trigger timer checks for a satisified trigger condition.
                                            //!Todo: Add timeout logic..
        mtk::Timer				            mTriggerTimer;

        						            //!The test function is a function called
                                            //!to test for the trigger condition
        triggerTestFunctionFPtr	            mTestFunction;

        TriggerConditionOperator            mTriggerConditionOperator;
        string					            mName;

		FireFunction						mFireFunction;
};

#endif
