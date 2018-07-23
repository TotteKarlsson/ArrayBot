#pragma hdrstop
#include "atContinousMove.h"
#include "atAPTMotor.h"
#include "dslUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
using namespace dsl;
using namespace at;
ContinousMove::ContinousMove(const string& lbl, double v, double acc)
:
at::Move(lbl, NULL, v, acc)
{}

bool ContinousMove::isDone()
{
    return true;
}

bool ContinousMove::start()
{
	Process::start();

	APTMotor* m = dynamic_cast<APTMotor*>(mSubject);
    if(m)
    {
		if(mMaxVelocity == 0 || mAcceleration == 0)
        {
        	Log(lError) << "Move cannot be executed with zero velocity or acceleration";
            return false;
        }
    	m->setJogVelocity(mMaxVelocity);
        m->setJogAcceleration(mAcceleration);
        m->jogForward();
        return true;
    }
    return false;
}

XMLElement* ContinousMove::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* processNode  	= doc.NewElement("process");
    XMLNode*    rootNode 		= doc.InsertFirstChild(processNode);

    //Attributes
    processNode->SetAttribute("name", mProcessName.c_str());
    processNode->SetAttribute("type", getTypeName().c_str());
	processNode->SetAttribute("motor_name", mSubjectName.c_str());
	processNode->SetAttribute("max_velocity", dsl::toString(getMaxVelocity()).c_str());
	processNode->SetAttribute("acc", dsl::toString(getAcceleration()).c_str());
	processNode->SetAttribute("pre_dwell_time", dsl::toString(getPreDwellTime()).c_str());
	processNode->SetAttribute("post_dwell_time", dsl::toString(getPostDwellTime()).c_str());

    processNode->InsertEndChild(rootNode);
    docRoot->InsertEndChild(processNode);

    return processNode;
}
