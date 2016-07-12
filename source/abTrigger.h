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

//typedef bool   (__closure *fireFunctionFPtrBoolDouble)(double);
typedef double (__closure *triggerTestFunctionFPtr)();

typedef function<void (const double& nr) > 	FireFunction;


enum TriggerCondition {tcLargerThan = 0, tcSmallerThan, tcEqualTo, tcLargerThanOrEqual, tcSmallerThanOrEqual};


class AB_CORE Trigger : public ABObject
{
    public:
                                            Trigger(const string& name, TriggerCondition c, triggerTestFunctionFPtr f);
		virtual                             ~Trigger(){}
		string					            getName(){return mName;}

        						            //!Load 'loads' the trigger.
        virtual bool			            load();
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
        bool					            mIsTriggered;
        mtk::Timer				            mTriggerTimer;

        						            //!The test function is a function called
                                            //!to check in order to trigger the trigger.
        triggerTestFunctionFPtr	            mTestFunction;

        TriggerCondition                    mTriggerCondition;
        string					            mName;

		FireFunction						mFireFunction;
};

#endif
