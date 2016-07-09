#ifndef abPositionalTriggerH
#define abPositionalTriggerH
//---------------------------------------------------------------------------
#include "abExporter.h"
#include "abABObject.h"
#include "abTrigger.h"
//---------------------------------------------------------------------------

class APTMotor;
class AB_CORE PositionalTrigger : public Trigger
{
    public:
                                PositionalTrigger(const string& name, TriggerCondition c,
                                					double position,  TriggerAction ta, APTMotor* motor);
                                ~PositionalTrigger(){}

        void					setNewVelocity(double nv) 		{mNewVelocity = nv;}
        void					setNewAcceleration(double na)	{mNewAcceleration = na;}

        virtual bool  			test(double);
        virtual bool  			test(int){return false;}
		virtual void	 		execute();

    protected:
    							//!The motor is the motor that will be manipulated
                                //!when the trigger fires.
		APTMotor*				mMotor;
        double					mMotorPositionalTriggerPoint;
        double					mNewVelocity;
        double					mNewAcceleration;

};
#endif
