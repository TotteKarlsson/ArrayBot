#ifndef atTriggerH
#define atTriggerH
#include "atABExporter.h"
#include "atATObject.h"
#include <string>
#include "dslTimer.h"
#include <vector>
#include "dslXMLUtils.h"
#include "atUtils.h"
//---------------------------------------------------------------------------

using std::string;
using std::vector;

namespace at
{

    typedef double (__closure *triggerTestFunctionFPtr)();
    class TriggerFunction;

    class AT_AB Trigger : public ATObject
    {
        public:
                                                Trigger(ATObject* s, LogicOperator lt = loLargerThan);
    		virtual                             ~Trigger(){}

            void								assignSubject(ATObject* s){mSubject = s;}
            ATObject*							getSubject(){return mSubject;}

    		string					            getSubjectName();

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
    		virtual void						assignTriggerFunction(TriggerFunction* f);

            									//!Check if the trigger been triggered
    		bool                                isTriggered(){return mIsTriggered;}

            						            //!Any subclass need to implement
                                                //an execute method
    		virtual void	 		            execute() = 0;
            virtual void	 		            reset();

            TriggerFunction* 					getTriggerFunction(){return mTriggerFunction;}

            									//!Ability to read/write trigger objects occurs using xml
    		virtual dsl::XMLElement* 			addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* docRoot) = 0;

        protected:
            									//!The subject name is the name of the device being monitored
            string					            mSubjectName;

            									//!The subject being 'observed' is typically APTDevices, motors etc
            ATObject*							mSubject;

        										//!The mIsTriggered is set to true in case the trigger been fired
            bool					            mIsTriggered;

        										//!The Trigger timer checks for a satisified trigger condition.
                                                //!Todo: Add timeout logic..
            dsl::Timer				            mTriggerTimer;

            						            //!The test function is a function called
                                                //!in the triggers timer function and used to test for the trigger condition
            triggerTestFunctionFPtr	            mTestFunction;

            virtual bool  			            test(double){return false;}
            virtual bool  			            test(int)   {return false;}

            									//!The triggerTest function is called by the timer
                                                //!and is the point at where the trigger condition is checked                                            /
            virtual void  			            triggerTest() = 0;

            									//!The triggering is tested using an Logic operator
            LogicOperator            			mTriggerConditionOperator;

            									//!The Fire function is executed when the trigger is
                                                //triggered
    		TriggerFunction*				 	mTriggerFunction;
    };


}
#endif

