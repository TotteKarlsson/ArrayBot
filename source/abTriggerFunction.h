#ifndef abTriggerFunctionH
#define abTriggerFunctionH
//---------------------------------------------------------------------------
#include "abExporter.h"
#include "abABObject.h"
#include <functional>
//---------------------------------------------------------------------------

//!A trigger function can be called and saved together with a Trigger.
//Any derived trigger functions implement their own data and functions.
//A triggerFunction is 'kind of' a a functor. Instead of an implemented operator()
//a triggerfunction executes by executing 'execute()'


//typedef function<void (double, double, double) > 	FireFunctionP;

//enum FireFunctionType {fftStop, fftMoveAbsolute};
//string toString(FireFunctionType t);
using std::tr1::function;

class APTMotor;
class AB_CORE TriggerFunction : public ABObject
{
    public:
                                    TriggerFunction(){}
                                    ~TriggerFunction(){}
        virtual const char* 		getType() = 0;
        virtual bool				execute() = 0;

    protected:

};

class AB_CORE MoveAbsolute : public  TriggerFunction
{
	public:
								    MoveAbsolute(APTMotor* mtr, double pos, double v, double a);
        APTMotor*		            mMotor;

    	double			            mVelocity;
        double			            mAcceleration;
        double 			            mPosition;

        virtual bool	            execute();
        const char*    	            getType(){return "absoluteMove";}
};

//string toString(FireFunctionType t)
//{
//	switch(t)
//    {
//    	case fftMoveAbsolute: 	return "moveAbsolute";
//    	case fftStop: 			return "stop";
//        default: 				return "undefined";
//    }
//}

#endif
