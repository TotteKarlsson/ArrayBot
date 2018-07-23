#pragma hdrstop
#include "atTriggerFunction.h"
#include "apt/atAPTMotor.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
using namespace dsl;


namespace at
{
    MoveAbsolute::MoveAbsolute(APTMotor* mtr, double pos, double v, double a)
    :
    mMotor(mtr),
    mPosition(pos),
    mVelocity(v),
    mAcceleration(a)
    {}

    bool MoveAbsolute::execute()
    {
    	if(mMotor)
        {
        	mMotor->moveAbsolute(mPosition, mVelocity, mAcceleration);
            Log(lInfo) << "Move absolute trigger executed";
        }
        else
        {
            Log(lError) << "Move absolute trigger executed with NULL motor";
        }

    	return true;
    }

    bool MoveAbsolute::isActive()
    {
    	return mMotor ? mMotor->isActive() : false;
    }

    dsl::XMLElement* MoveAbsolute::addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* docRoot)
    {
        //Create XML for saving to file
        XMLElement* e	  			= doc.NewElement("trigger_function");
        XMLNode*    rootNode 		= doc.InsertFirstChild(e);
        string 		test;

        //Attributes
        e->SetAttribute("type", getTypeName().c_str());

        mMotorName = mMotor ? mMotor->getName() : mMotorName;
        e->SetAttribute("motor_name", mMotorName.c_str());

    	XMLElement* val = doc.NewElement("final_position");
        test = dsl::toString(mPosition);
        val->SetText(test.c_str());
    	e->InsertEndChild(val);

    	val = doc.NewElement("max_velocity");
        test = dsl::toString(mVelocity);
        val->SetText(test.c_str());
    	e->InsertEndChild(val);

    	val = doc.NewElement("acceleration");
        test = dsl::toString(mAcceleration);
        val->SetText(test.c_str());
    	e->InsertEndChild(val);

        e->InsertEndChild(rootNode);
        docRoot->InsertEndChild(e);
        return e;
    }

}
