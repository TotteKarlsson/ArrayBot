#ifndef abTriggerH
#define abTriggerH
#include "abExporter.h"
#include "abABObject.h"
#include <string>
#include "mtkTimer.h"
#include <functional>
#include <vector>
#include "mtkXMLUtils.h"
#include "abUtilities.h"
//---------------------------------------------------------------------------

using std::string;
using std::vector;
using std::tr1::function;

typedef double (__closure *triggerTestFunctionFPtr)();
typedef function<void (double, double, double) > 	FireFunctionP;

enum FireFunctionType {fftStop, fftMoveAbsolute};
string toString(FireFunctionType t);

class FireFunction : public ABObject
{
	public:
    	FireFunctionP 				f;
        virtual const char* 		getType();
};

class AbsoluteMoveFunctor : public  FireFunction
{
	public:
    	double			mVelocity;
        double			mAcceleration;
        double 			mPosition;
        APTMotor*		mMotor;
        const char*    	getType(){return "absoluteMove";}
};


class AB_CORE Trigger : public ABObject
{
    public:
                                            Trigger(const string& subject, const string& observer);
		virtual                             ~Trigger(){}

        void								setSubjectName(const string& n){mSubjectName = n;}
		string					            getSubjectName(){return mSubjectName;}

        void								setObjectToTriggerName(const string& n){mObjectToTriggerName = n;}
		string					            getObjectToTriggerName(){return mObjectToTriggerName;}

        bool								setTestOperator(LogicOperator lo){mTriggerConditionOperator = lo; return true;}
        LogicOperator						getTestOperator(){return mTriggerConditionOperator;}

        						            //!Enable 'loads' the trigger.
        virtual bool			            enable();

        						            //!Disable disables the trigger.
        virtual bool			            disable();

        									//!The test function is using the TriggerCondition
                                            //operator in order to check if the trigger should trigger
        virtual void			            setTestFunction(triggerTestFunctionFPtr f);

        									//!Assign function that will be executed when
                                            //!the trigger triggers
		virtual void						addFireFunction(FireFunction f);
//		const char* 						getFireFunctionType(){ifreturn mFireFunction.getType();}
        									//!Check if the trigger been triggered
		bool                                isTriggered(){return mIsTriggered;}

        						            //!Any subclass need to implement
                                            //an execute method
		virtual void	 		            execute() = 0;
        virtual void	 		            reset();
		virtual mtk::XMLElement* 			addToXMLDocumentAsChild(mtk::XMLDocument& doc, mtk::XMLNode* docRoot) = 0;

    protected:
        									//!The subject name is the name of the device being monitored
        string					            mSubjectName;

        									//!The DeviceToTrigger name is the name of the device being acted on
        string					            mObjectToTriggerName;

    										//!The mIsTriggered is set to true in case the trigger been fired
        bool					            mIsTriggered;

    										//!The Trigger timer checks for a satisified trigger condition.
                                            //!Todo: Add timeout logic..
        mtk::Timer				            mTriggerTimer;

        						            //!The test function is a function called
                                            //!in the triggers timer function and used to test for the trigger condition
        triggerTestFunctionFPtr	            mTestFunction;

        virtual bool  			            test(double){return false;}
        virtual bool  			            test(int)   {return false;}
        virtual void  			            triggerTest() {;}

        									//!The triggering is tested using an Logic operator
        LogicOperator            			mTriggerConditionOperator;

        									//!The Fire function is executed when the trigger is
                                            //triggered
		FireFunction*						mFireFunction;
};

string toString(FireFunctionType t)
{
	switch(t)
    {
    	case fftMoveAbsolute: 	return "moveAbsolute";
    	case fftStop: 			return "stop";
        default: 				return "undefined";
    }
}
#endif
