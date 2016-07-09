#pragma hdrstop
#include "abContinousMove.h"
#include "abAPTMotor.h"
//---------------------------------------------------------------------------

using namespace mtk;


ContinousMove::ContinousMove(const string& lbl, double v, double acc)
:
ab::Move(lbl, v, acc)
{}

bool ContinousMove::isDone()
{
    return true;
}

bool ContinousMove::start()
{
	Process::start();

	APTMotor* m = dynamic_cast<APTMotor*>(mUnit);
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

XMLElement* ContinousMove::addToXMLDocumentAsChild(mtk::XMLDocument& doc, mtk::XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* processNode  	= doc.NewElement("process");
    XMLNode*    rootNode 		= doc.InsertFirstChild(processNode);

    //Attributes
    processNode->SetAttribute("name", mProcessName.c_str());
    processNode->SetAttribute("type", getTypeName());
	processNode->SetAttribute("motor_name", mMotorName.c_str());
	processNode->SetAttribute("max_velocity", mtk::toString(getMaxVelocity()).c_str());
	processNode->SetAttribute("acc", mtk::toString(getAcceleration()).c_str());
	processNode->SetAttribute("pre_dwell_time", mtk::toString(getPreDwellTime()).c_str());
	processNode->SetAttribute("post_dwell_time", mtk::toString(getPostDwellTime()).c_str());

    processNode->InsertEndChild(rootNode);
    docRoot->InsertEndChild(processNode);

    return processNode;
}