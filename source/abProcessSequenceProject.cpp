#pragma hdrstop
#include "abProcessSequenceProject.h"
#include "mtkXMLUtils.h"
#include "mtkLogger.h"
#include "abProcessSequence.h"
#include "abCombinedMove.h"
#include "abPosition.h"
#include "abArrayBot.h"
#include "abAbsoluteMove.h"
#include "abTimedelay.h"
#include "abAPTMotor.h"
using namespace mtk;
using namespace tinyxml2;

//XML Version history
/*
    0.5 : Original version
*/

const string gProcessSequenceProjectFileVersion    = "0.6";

ProcessSequenceProject::ProcessSequenceProject(ProcessSequence& ps, const string& fName)
:
Project(fName, "abp"),
mProcessSequence(ps)
{
	resetXML();
}

ProcessSequenceProject::~ProcessSequenceProject()
{}

string ProcessSequenceProject::getPresentModelVersion()
{
    return gProcessSequenceProjectFileVersion;
}

bool ProcessSequenceProject::resetXML()
{
	mTheXML.Clear();
    mProjectRoot = mTheXML.NewElement("sequence_project");
    mRootNode = mTheXML.InsertFirstChild(mProjectRoot);

    //Insert as a minimum project file version
    XMLElement* version = mTheXML.NewElement("version");
    XMLText* 	versionValue = mTheXML.NewText(gProcessSequenceProjectFileVersion.c_str());
    version->InsertEndChild(versionValue);
    mProjectRoot->InsertEndChild(version);

    XMLElement* name 		= mTheXML.NewElement("name");
    XMLText* 	nameValue 	= mTheXML.NewText(mProcessSequence.getName().c_str());
	name->InsertEndChild(nameValue);
    mProjectRoot->InsertEndChild(name);
    return true;
}

bool ProcessSequenceProject::save(const string& fName)
{
    resetXML();

    //For now, do a brute force save of Moleculix Objects
    XMLElement* sequence = newElement("sequence");

    //First save Processes
    Process* p = mProcessSequence.getFirst();
    while(p)
    {
        Log(lDebug) << "Saving process: " << p->getProcessName();
        XMLElement* xmlProc = p->addToXMLDocument(mTheXML, sequence);
        if(dynamic_cast<CombinedMove*>(p))
	    {
        	CombinedMove* clm = dynamic_cast<CombinedMove*>(p);

        	//Write subprocesses
			clm->addToXMLDocumentAsChildProcess(mTheXML, xmlProc);
        }

        if(dynamic_cast<TimeDelay*>(p))
	    {
        	TimeDelay* td = dynamic_cast<TimeDelay*>(p);

        	//Write subprocesses
			td->addToXMLDocumentAsChildProcess(mTheXML, xmlProc);
        }
        p = mProcessSequence.getNext();
    }

    this->addNode(sequence);

    //Convoluted code
    if(fName.size() != 0)
    {
    	return saveToFile(fName);
    }
    else
    {
    	return saveToFile(joinPath(mFileFolder, getFileNameNoPath(mFileName)));
    }
}

bool ProcessSequenceProject::open()
{
    try
    {
        Log(lInfo) << "Attempting to load model: "<<this->getFileName();

        //Read the name node
        int nrOfObjs = loadProcesses();
        Log(lDebug) << "Loaded " << nrOfObjs << " process objects";
        return true;
    }
    catch(...)
    {
        throw(("Bad model file!"));
    }
}

int ProcessSequenceProject::loadProcesses()
{
    //This function creates proceses XML
    XMLElement* sequence = this->getXML("sequence");

    if(sequence == NULL)
    {
        return 0;
    }

    int nrOfObjects = 0;

     //Load process by process
    XMLElement* p = sequence->FirstChildElement();
    while(p)
    {
        //Find out what kind of element p is
        Process* aProc = createProcess(p);
        if(aProc)
        {
            mProcessSequence.add(aProc);
            Log(lDebug) <<"Imported process: "<<aProc->getProcessName()<<" of type: "<<aProc->getTypeName();
            nrOfObjects++;
        }
        else
        {
            Log(lError) << "Failed importing a "<<p->Name()<<" process";
        }

        p = p->NextSiblingElement();
    }

    return nrOfObjects;
}

Process* ProcessSequenceProject::createProcess(tinyxml2::XMLElement* element)
{
    if(!element)
    {
        return NULL;
    }

    if(!compareStrings(element->Name(), "process", csCaseInsensitive))
    {
    	return NULL;
    }

	ProcessType pt = toProcessType(element->Attribute("type"));

  	//What process?
    switch(pt)
    {
    	case ptCombinedMove: 	return createCombinedMoveProcess(element);
        case ptTimeDelay:       return createTimeDelayProcess(element);
    }

    return NULL;
}

Process* ProcessSequenceProject::createCombinedMoveProcess(XMLElement* element)
{
    CombinedMove* p = new CombinedMove(element->Attribute("name"));

    //Read data
    XMLElement* proc = element->FirstChildElement("process");
    if(proc)
    {
        //Loop over childs
        while(proc)
        {
            AbsoluteMove* absMove(NULL);

            const char* type = proc->Attribute("type");
            const char* name = proc->Attribute("name");

            if(name)
            {
                Log(lDebug) << "Loading element: "<<name;

                if(compareNoCase(type, "absoluteMove"))
                {
                    absMove = new AbsoluteMove(name);
                }

                XMLElement* data = proc->FirstChildElement("motor_name");
                if(data && data->GetText())
                {
//                    absMove->setMotorName(data->GetText());
                }

                data = proc->FirstChildElement("final_position");
                if(data && data->GetText())
                {
                    absMove->setPosition(toDouble(data->GetText()));
                }

                data = proc->FirstChildElement("max_velocity");
                if(data && data->GetText())
                {
                    absMove->setMaxVelocity(toDouble(data->GetText()));
                }

                data = proc->FirstChildElement("acc");
                if(data && data->GetText())
                {
                    absMove->setAcceleration(toDouble(data->GetText()));
                }

                data = proc->FirstChildElement("pre_dwell_time");
                if(data && data->GetText())
                {
                    absMove->setPreDwellTime(toDouble(data->GetText()));
                }

                data = proc->FirstChildElement("post_dwell_time");
                if(data && data->GetText())
                {
                    absMove->setPostDwellTime(toDouble(data->GetText()));
                }

                //Load the trigger
                data = proc->FirstChildElement("trigger");

                if(data)
                {
                	XMLElement* e = data->FirstChildElement("position");
                    if(e)
                    {
	                	absMove->getTrigger().setPosition(toDouble(e->GetText()));
                    }

                	e = data->FirstChildElement("operator");
                    if(e)
                    {
	                	absMove->getTrigger().setTestOperator(toLogicOperator(e->GetText()));
                    }

                	e = data->FirstChildElement("object_to_trigger");
                    if(e)
                    {
//	                	absMove->getTrigger().setObjectToTriggerName(stdstr(e->GetText()));
                    }
                }

                //We need to associate the motor with 'name' with a
                //real motor object provided for by ArrayBot
                absMove->assignUnit(mProcessSequence.getArrayBot());
                p->addMove(absMove);
            }

            proc = proc->NextSiblingElement();
        }
    }

    return p;
}

Process* ProcessSequenceProject::createTimeDelayProcess(XMLElement* element)
{
    TimeDelay* p = new TimeDelay("");

   	p->setProcessName(element->Attribute("name"));
    XMLElement* delay = element->FirstChildElement("delay");
    if(delay)
    {
    	p->setTimeDelay(toInt(delay->GetText()));
    }
   	else
    {
    	p->setTimeDelay(-1);
    }

    return p;
}

