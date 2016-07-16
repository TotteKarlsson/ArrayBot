#ifndef abPositionalTriggerH
#define abPositionalTriggerH
//---------------------------------------------------------------------------
#include "abExporter.h"
#include "abABObject.h"
#include "abTrigger.h"
//---------------------------------------------------------------------------

class APTMotor;

//!A positional trigger triggers when a motors position passes over a set threshold value.
//!To properly fire a trigger, a triggerFunction need to be given, e.g. mtr->getPosition() that
//!is used to check for the triggercondition.
//!Functions to be executed when the trigger fires are assigned and stored to the fireFunctions array from
//!the base class (no array yet)
//!Triggers are members of Process classes and are activated, deactivated in a process start/stop functions

class AB_CORE PositionalTrigger : public Trigger
{
    public:
                                			PositionalTrigger(const string& s, const string& o);
                                			~PositionalTrigger(){}

		virtual void	 					execute();
        virtual const char*	 				getTypeName() const{return "positionalTrigger";}

        double								getPosition(){return mPosition;}
        void								setPosition(double p){mPosition = p;}

		virtual mtk::XMLElement*            addToXMLDocumentAsChild(mtk::XMLDocument& doc, mtk::XMLNode* docRoot);

    protected:
        double					            mPosition;
        virtual void  			            triggerTest();
        virtual bool  			            test(double);
        virtual bool  			            test(int){return false;}
};
#endif
