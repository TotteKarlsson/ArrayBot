#ifndef atTriggerFunctionH
#define atTriggerFunctionH
#include "arraybot/atABExporter.h"
#include "atATObject.h"
#include <functional>
#include "dslXMLUtils.h"
//---------------------------------------------------------------------------

//!A trigger function can be called and saved together with a Trigger.
//Any derived trigger functions implement their own data and functions.
//A triggerFunction is 'kind of' a a functor, but instead of an implemented operator()
//a triggerfunction executes by executing its 'execute()' function.

//typedef function<void (double, double, double) > 	FireFunctionP;

//enum FireFunctionType {fftStop, fftMoveAbsolute};
//string toString(FireFunctionType t);
//TODO: These triggerfunctions may be replaced later
//on by using pure process objects instead, like the MoveAbsoluteProcess

namespace at
{
    class APTMotor;
    class AT_AB TriggerFunction : public ATObject
    {
        public:
                                                TriggerFunction(){}
                                                ~TriggerFunction(){}
            const string   	                    getTypeName() const {return "triggerFunction";}
            virtual bool				        execute() = 0;
            virtual bool		   				isActive() = 0;

            									//!Ability to read/write trigger objects occurs using xml
    		virtual dsl::XMLElement* 			addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* docRoot) = 0;
    };

    //!Move absolute is a subclass of TriggerFunction.
    class AT_AB MoveAbsolute : public  TriggerFunction
    {
    	public:
    								            MoveAbsolute(APTMotor* mtr, double pos = 0, double v = 1.0, double a = 1.0);

            virtual bool	                    execute();
            const string   	                    getTypeName() const {return "absoluteMove";}

            bool								isActive();
            void								setMotor(APTMotor* mtr){mMotor = mtr;}
            APTMotor*							getMotor(){return mMotor;}

            void								setMotorName(const string& name){mMotorName = name;}
            string 								getMotorName(){return mMotorName;}

            double								getVelocity(){return mVelocity;}
            void								setVelocity(double v){mVelocity = v;}

            double								getAcceleration(){return mAcceleration;}
            void								setAcceleration(double a){mAcceleration = a;}

            double								getPosition(){return mPosition;}
            void								setPosition(double a){mPosition = a;}

    		virtual dsl::XMLElement* 			addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* docRoot);

    	protected:
            APTMotor*		                    mMotor;
            string			                    mMotorName;
        	double			                    mVelocity;
            double			                    mAcceleration;
            double 			                    mPosition;
    };
}


#endif
