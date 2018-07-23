#pragma hdrstop
#include "atAbsoluteMove.h"
#include "atAPTMotor.h"
#include "atTriggerFunction.h"
#include "atProcessSequence.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
using namespace dsl;

namespace at
{
    AbsoluteMove::AbsoluteMove(const string& lbl, APTMotor* mtr, double pos, double maxVel, double acc)
    :
    at::Move(lbl, mtr, maxVel, acc),
    mPosition(pos),
    mPositionResolution(1.0e-3)
    {
    	mProcessType = ptAbsoluteMove;
    }

    const string AbsoluteMove::getTypeName() const
    {
    	return "absoluteMove";
    }

    bool AbsoluteMove::write()
    {
    	if(mProcessSequence)
        {
        	return mProcessSequence->write();
        }
    	return false;
    }

    bool AbsoluteMove::isDone()
    {
    	APTMotor* o = dynamic_cast<APTMotor*>(mSubject);
        if(o)
        {
        	//If still moving we cannot be done(!)
        	if(o->isActive())
            {
            	return false;
            }

            //Also, if we did setoff a trigger, check on that and add that to the lifetime of
            //the process
    		if(mTrigger)
            {
            	if(mTrigger->isTriggered())
                {
                	if(mTrigger->getTriggerFunction()->isActive())
                    {
                    	return false;
                    }

                    //This return statement allows a trigger to 'finish' a process in a different
                    //position than its 'mother' process
                    return true;
                }
            }

        	double p = o->getPosition();
        	return (isEqual(p, mPosition, mPositionResolution)) ? true : false;
        }

        return false;
    }

    bool AbsoluteMove::start()
    {
    	APTMotor* m = dynamic_cast<APTMotor*>(mSubject);
        if(m)
        {
    		if(mMaxVelocity == 0 || mAcceleration == 0)
            {
            	Log(lError) << "Move cannot be executed with zero velocity or acceleration";
                return false;
            }

    		//Reset and enable trigger(s)
            if(mTrigger)
            {
            	mTrigger->reset();
    	        mTrigger->enable();
            }

            //This will start the processs internal time checking that checks for
            //process events
            Process::start();
        	m->setVelocityParameters(mMaxVelocity, mAcceleration);
            return m->moveToPosition(mPosition);
        }

        return false;
    }

    //Resume is similar to start...
    bool AbsoluteMove::resume()
    {
    	APTMotor* m = dynamic_cast<APTMotor*>(mSubject);
        if(m)
        {
    		if(mMaxVelocity == 0 || mAcceleration == 0)
            {
            	Log(lError) << "Move cannot be executed with zero velocity or acceleration";
                return false;
            }

    		//Reset and enable trigger(s)
            if(mTrigger)
            {
            	mTrigger->reset();
    	        mTrigger->enable();
            }

            Process::resume();
        	m->setVelocityParameters(mMaxVelocity, mAcceleration);
            return m->moveToPosition(mPosition);
        }

        return false;
    }

    void AbsoluteMove::addTrigger(Trigger* t)
    {
    	mTrigger = t;
        mTrigger->assignSubject(this);
        PositionalTrigger* pt = dynamic_cast<PositionalTrigger*>(mTrigger);
        if(pt)
        {
        	if(dynamic_cast<APTMotor*>(getUnit()))
            {
    			pt->setTestFunction(dynamic_cast<APTMotor*>(getUnit())->getPosition);
            }
        }
    }

    XMLElement* AbsoluteMove::addToXMLDocumentAsChild(dsl::XMLDocument& doc, XMLNode* docRoot)
    {
    	XMLElement* dataval1 = doc.NewElement("motor_name");
        dataval1->SetText(mSubjectName.c_str());
    	docRoot->InsertEndChild(dataval1);

    	dataval1 = doc.NewElement("final_position");
        dataval1->SetText(dsl::toString(getPosition()).c_str());
    	docRoot->InsertEndChild(dataval1);

     	dataval1 = doc.NewElement("max_velocity");
        dataval1->SetText(dsl::toString(getMaxVelocity()).c_str());
    	docRoot->InsertEndChild(dataval1);

      	dataval1 = doc.NewElement("acc");
        dataval1->SetText(dsl::toString(getAcceleration()).c_str());
    	docRoot->InsertEndChild(dataval1);

    	dataval1 = doc.NewElement("pre_dwell_time");
        dataval1->SetText(dsl::toString(getPreDwellTime()).c_str());
    	docRoot->InsertEndChild(dataval1);

    	dataval1 = doc.NewElement("post_dwell_time");
        dataval1->SetText(dsl::toString(getPostDwellTime()).c_str());
    	docRoot->InsertEndChild(dataval1);

    	//Add trigger
        if(mTrigger)
        {
        	mTrigger->addToXMLDocumentAsChild(doc, docRoot);
        }

        docRoot->InsertEndChild(dataval1);
        return dataval1;
    }

}
