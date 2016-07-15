#ifndef abPositionalTriggerH
#define abPositionalTriggerH
//---------------------------------------------------------------------------
#include "abExporter.h"
#include "abABObject.h"
#include "abTrigger.h"
//---------------------------------------------------------------------------

class APTMotor;
//!A positional trigger triggers when a motors position passes over a set threshold value.
//!To properly fire a trigger, a triggerFunction need to be given, e.g. mtr->getPosition()
//!Functions to be executed when the trigger fires are stored in the fireFunctions array from
//!the base class

class AB_CORE PositionalTrigger : public Trigger
{
    public:
                                PositionalTrigger(const string& name, triggerTestFunctionFPtr f = NULL, TriggerConditionOperator c = tcLargerThan, double position = -1);
                                ~PositionalTrigger(){}

        virtual bool  			test(double);
        virtual bool  			test(int){return false;}
		virtual void	 		execute();
        virtual void  			triggerTest();

    protected:
        double					mMotorPositionalTriggerPoint;

};
#endif
