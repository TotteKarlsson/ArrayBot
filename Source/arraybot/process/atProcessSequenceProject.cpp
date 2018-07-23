#pragma hdrstop
#include "atProcessSequenceProject.h"
#include "dslXMLUtils.h"
#include "dslLogger.h"
#include "atProcessSequence.h"
#include "atParallelProcess.h"
#include "atArrayBot.h"
#include "apt/atAbsoluteMove.h"
#include "apt/atMove.h"
#include "atTimedelay.h"
#include "atAbsoluteMove.h"
#include "atStopAndResumeProcess.h"
#include "atArrayCamRequestProcess.h"
#include "atMoveCoverSlipAtAngleProcess.h"
#include "apt/atAPTMotor.h"
#include "atTriggerFunction.h"
#include "arduino/atArduinoServerCommand.h"
#include "atHomeMotor.h"

using namespace dsl;
using namespace tinyxml2;

//XML Version history
/*
    0.5 : Original version
*/

const string gProcessSequenceProjectFileVersion    = "0.6";

namespace at
{
ProcessSequenceProject::ProcessSequenceProject(ProcessSequence& ps, ArrayCamClient& ac, const string& projectFileName)
:
Project(projectFileName, "abp"),
mProcessSequence(ps),
mArrayCamClient(ac)
{
	resetXML();
}

ProcessSequenceProject::~ProcessSequenceProject()
{}

string ProcessSequenceProject::getPresentXMLModelVersion()
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
	sequence->SetAttribute("category", 					mProcessSequence.getCategory().c_str());
	sequence->SetAttribute("order", 					dsl::toString(mProcessSequence.getOrder()).c_str());
	sequence->SetAttribute("use_process_controller", 	dsl::toString(mProcessSequence.getUseProcessController()).c_str());

    //First save Processes
    Process* p = mProcessSequence.getFirst();
    while(p)
    {
        Log(lDebug) << "Saving process: " << p->getProcessName();
        XMLElement* xmlProc = p->addToXMLDocument(mTheXML, sequence);

        switch(p->getProcessType())
        {
            case ptParallel:
            {
                ParallelProcess* p1 = dynamic_cast<ParallelProcess*>(p);

				if(p1)
                {
                	p1->addToXMLDocumentAsChild(mTheXML, xmlProc);
                }
            }
            break;

            case ptTimeDelay:
            {
                TimeDelay* p1 = dynamic_cast<TimeDelay*>(p);

				if(p1)
                {
                	p1->addToXMLDocumentAsChild(mTheXML, xmlProc);
                }
            }
            break;

            case ptStopAndResume:
            {
                StopAndResumeProcess* p1 = dynamic_cast<StopAndResumeProcess*>(p);

				if(p1)
                {
                	p1->addToXMLDocumentAsChild(mTheXML, xmlProc);
                }
            }
            break;
            case ptArrayCamRequest:
            {
                ArrayCamRequestProcess* p1 = dynamic_cast<ArrayCamRequestProcess*>(p);

				if(p1)
                {
                	p1->addToXMLDocumentAsChild(mTheXML, xmlProc);
                }
            }
            break;
            case ptAbsoluteMove:
            {
                AbsoluteMove* p1 = dynamic_cast<AbsoluteMove*>(p);

				if(p1)
                {
                	p1->addToXMLDocumentAsChild(mTheXML, xmlProc);
                }
            }
            break;
            case ptMoveCoverSlipAtAngle:
            {
                MoveCoverSlipAtAngleProcess* p1 = dynamic_cast<MoveCoverSlipAtAngleProcess*>(p);

				if(p1)
                {
                	p1->addToXMLDocumentAsChild(mTheXML, xmlProc);
                }
            }
            break;
            case ptHomeMotor:
            {
                HomeMotor* p1 = dynamic_cast<HomeMotor*>(p);

				if(p1)
                {
                	p1->addToXMLDocumentAsChild(mTheXML, xmlProc);
                }
            }
            break;

            default:
            {
                Log(lError) << "The process: " <<p->getProcessName()<< " of type: "<<p->getProcessTypeAsString()<<" was NOT added to the XML document";
            }
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

bool ProcessSequenceProject::open(const string& fName)
{
    try
    {
        if(fName.size())
        {
            this->setFileName(fName);
        }

        Log(lInfo) << "Attempting to load model: "<<this->getFileName();

        //Read the name node
        int nrOfObjs = loadProcesses();
        Log(lDebug) << "Loaded " << nrOfObjs << " process objects";
        return true;
    }
    catch(...)
    {
        throw("Bad model file!");
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

    /// Category attribute
    string category("General");
    if(sequence->Attribute("category"))
    {
		category = sequence->Attribute("category");
    }
    else
    {
    	Log(lWarning) << "The sequence: "<<this->getProjectName()<<" don't have a category. Category \"General\" is applied";
    }

    mProcessSequence.setCategory(category);
	//==========================================================================================================================

    int order(0);
    /// order attribute
    if(sequence->Attribute("order"))
    {
		order = toInt(sequence->Attribute("order"));
    }
    else
    {
    	Log(lWarning) << "The sequence: "<<this->getProjectName()<<" don't have an order attribute. Order \"0\" is applied";
    }

    mProcessSequence.setOrder(order);
	//==========================================================================================================================

    bool useProcessController(true);

    /// useProcessController attribute
    if(sequence->Attribute("use_process_controller"))
    {
		useProcessController = toBool(sequence->Attribute("use_process_controller"));
    }
    else
    {
    	Log(lWarning) << "The sequence: "<<this->getProjectName()<<" don't have an \"use_process_controller\" attribute. use_process_controller \"true\" is applied";
    }

    mProcessSequence.setUseProcessController(useProcessController);
	//==========================================================================================================================

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
    if(!element && !compareStrings(element->Name(), "process", csCaseInsensitive))
    {
    	Log(lError) <<"Bad 'createProcess' xml!";
    	return NULL;
    }

  	//What processtype?
	ProcessType pt = toProcessType(element->Attribute("type"));
    switch(pt)
    {
    	case ptParallel: 				        return createParallelProcess(element);
        case ptTimeDelay:       		        return createTimeDelayProcess(element);
        case ptStopAndResume:			        return createStopAndResumeProcess(element);
        case ptArrayCamRequest:					return createArrayCamRequestProcess(element);
        case ptAbsoluteMove:					return createAbsoluteMove(element);
        case ptMoveCoverSlipAtAngle:			return createMoveCoverSlipAtAngleProcess(element);
        case ptHomeMotor:						return createHomeMotorProcess(element);
    }

    return NULL;
}

ParallelProcess* ProcessSequenceProject::createParallelProcess(XMLElement* element)
{
    ParallelProcess* p = new ParallelProcess(element->Attribute("name"));
    p->assignProcessSequence(&mProcessSequence);

    //Read data
    XMLElement* proc = element->FirstChildElement("process");
    if(proc)
    {
        //Loop over childs
        while(proc)
        {
            const char* type = proc->Attribute("type");
            const char* name = proc->Attribute("name");

            if(name)
            {
                Log(lDebug) << "Loading process with name: "<<name<<" and type: "<<type;

                if(toProcessType(type) == ptAbsoluteMove)
                {
                	AbsoluteMove* absMove = createAbsoluteMove(proc);
    				absMove->assignProcessSequence(&mProcessSequence);

                    //We need to associate the motor with 'name' with a
                    //real motor object provided for by ArrayBot
                    absMove->assignUnit(mProcessSequence.getArrayBot());
                    p->addProcess(absMove);
                }

                else if(toProcessType(type) == ptArrayCamRequest)
                {
                	ArrayCamRequestProcess* c = createArrayCamRequestProcess(proc);
    				c->assignProcessSequence(&mProcessSequence);
                    p->addProcess(c);
                }

                else if(toProcessType(type) == ptArduinoServerCommand)
                {
                	ArduinoServerCommand* c = createArduinoServerCommand(proc);
    				c->assignProcessSequence(&mProcessSequence);
                    p->addProcess(c);
                }
                else if(toProcessType(type) == ptMoveCoverSlipAtAngle)
                {
                	MoveCoverSlipAtAngleProcess* c = createMoveCoverSlipAtAngleProcess(proc);
    				c->assignProcessSequence(&mProcessSequence);
                    p->addProcess(c);
                }
            }
            proc = proc->NextSiblingElement();
        }
    }
    return p;
}

AbsoluteMove* ProcessSequenceProject::createAbsoluteMove(XMLElement* element)
{
   	string name = element->Attribute("name");
	AbsoluteMove* absMove = new AbsoluteMove(name);
    XMLElement* data = element->FirstChildElement("info");
    if(data && data->GetText())
    {
        absMove->setInfoText(data->GetText());
    }

    data = element->FirstChildElement("motor_name");
    if(data && data->GetText())
    {
        absMove->setSubjectName(data->GetText());
    }

    data = element->FirstChildElement("final_position");
    if(data && data->GetText())
    {
        absMove->setPosition(toDouble(data->GetText()));
    }

    data = element->FirstChildElement("max_velocity");
    if(data && data->GetText())
    {
        absMove->setMaxVelocity(toDouble(data->GetText()));
    }

    data = element->FirstChildElement("acc");
    if(data && data->GetText())
    {
        absMove->setAcceleration(toDouble(data->GetText()));
    }

    data = element->FirstChildElement("pre_dwell_time");
    if(data && data->GetText())
    {
        absMove->setPreDwellTime(toDouble(data->GetText()));
    }

    data = element->FirstChildElement("post_dwell_time");
    if(data && data->GetText())
    {
        absMove->setPostDwellTime(toDouble(data->GetText()));
    }

    //Load the trigger
    data = element->FirstChildElement("trigger");

    if(data)
    {
        const char* ttype = data->Attribute("type");
        if(ttype && compareNoCase(ttype, "positionalTrigger"))
        {
            PositionalTrigger* pt = new PositionalTrigger(NULL);
            absMove->addTrigger(pt);

            XMLElement* e = data->FirstChildElement("position");
            if(e)
            {
                pt->setPosition(toDouble(e->GetText()));
            }

            e = data->FirstChildElement("operator");
            if(e)
            {
                pt->setTestOperator(toLogicOperator(e->GetText()));
            }

            //Load trigger function(s)
            //Load the trigger
            XMLElement* tfData = data->FirstChildElement("trigger_function");
            if(tfData)
            {
                const char* type = tfData->Attribute("type");
                if(type && compareNoCase(type, "absoluteMove"))
                {
                    MoveAbsolute* tf = new MoveAbsolute(NULL, 0,0,0);

                    const char* mtrName = tfData->Attribute("motor_name");
                    tf->setMotorName(mtrName);
                    pt->assignTriggerFunction(tf);

                    XMLElement* e = tfData->FirstChildElement("final_position");
                    if(e && e->GetText())
                    {
                        tf->setPosition(toDouble(e->GetText()));
                    }

                    e = tfData->FirstChildElement("max_velocity");
                    if(e && e->GetText())
                    {
                        tf->setVelocity(toDouble(e->GetText()));
                    }

                    e = tfData->FirstChildElement("acceleration");
                    if(e && e->GetText())
                    {
                        tf->setAcceleration(toDouble(e->GetText()));
                    }
                }
            }
        }
    }


    //We need to associate the motor with 'name' with a
    //real motor object provided for by ArrayBot
    absMove->assignUnit(mProcessSequence.getArrayBot());
    return absMove;
}

TimeDelay* ProcessSequenceProject::createTimeDelayProcess(XMLElement* element)
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

StopAndResumeProcess* ProcessSequenceProject::createStopAndResumeProcess(XMLElement* element)
{
    StopAndResumeProcess* p = new StopAndResumeProcess("");
   	p->setProcessName(element->Attribute("name"));

    //Read info
    XMLElement* data1 = element->FirstChildElement("info");
    if(data1 && data1->GetText())
    {
        p->setInfoText(data1->GetText());
    }

    return p;
}

ArrayCamRequestProcess* ProcessSequenceProject::createArrayCamRequestProcess(XMLElement* element)
{
   	string name = element->Attribute("name");
    XMLElement* request = element->FirstChildElement("request");
    ArrayCamRequestProcess* p = new ArrayCamRequestProcess(mArrayCamClient, name, request->GetText());
    if(p->getRequest() == acrSetZoomAndFocus)
    {
    	//Look for parameters
	    XMLElement* data1 = element->FirstChildElement("focus");
        if(data1 && data1->GetText())
        {
        	p->mParameter1.setValue(toDouble(data1->GetText()));
			p->mParameter1.setLabel("focus");
        }
    	//Look for parameters
	    XMLElement* data2 = element->FirstChildElement("zoom");
        if(data2 && data2->GetText())
        {
        	p->mParameter2.setValue(toDouble(data2->GetText()));
			p->mParameter2.setLabel("zoom");
        }
    }
	else if(p->getRequest() == acrSetLEDIntensity)
    {
    	//Look for parameters
	    XMLElement* data1 = element->FirstChildElement("intensity");
        if(data1 && data1->GetText())
        {
        	p->mParameter1.setValue(toInt(data1->GetText()));
			p->mParameter1.setLabel("intensity");
        }
    }

    return p;
}

ArduinoServerCommand* ProcessSequenceProject::createArduinoServerCommand(XMLElement* element)
{
   	string name = element->Attribute("name");
	ArduinoServerCommand* c = new ArduinoServerCommand(name);

    XMLElement* data = element->FirstChildElement("command");
    if(data && data->GetText())
    {
        c->setCommand(data->GetText());
    }
	return c;
}

MoveCoverSlipAtAngleProcess* ProcessSequenceProject::createMoveCoverSlipAtAngleProcess(XMLElement* element)
{
   	string name = element->Attribute("name");
	MoveCoverSlipAtAngleProcess* p = new MoveCoverSlipAtAngleProcess(name);

    p->populateFromXML(element);

    return p;
}

HomeMotor* ProcessSequenceProject::createHomeMotorProcess(XMLElement* element)
{
   	string name = element->Attribute("name");
	HomeMotor* p = new HomeMotor(name);

    //This code belongs in the process class!
    XMLElement* data = element->FirstChildElement("info");
    if(data && data->GetText())
    {
        p->setInfoText(data->GetText());
    }

    data = element->FirstChildElement("motor_name");
    if(data && data->GetText())
    {
        p->setSubjectName(data->GetText());
    }

    data = element->FirstChildElement("pre_dwell_time");
    if(data && data->GetText())
    {
        p->setPreDwellTime(toDouble(data->GetText()));
    }

    data = element->FirstChildElement("post_dwell_time");
    if(data && data->GetText())
    {
        p->setPostDwellTime(toDouble(data->GetText()));
    }

    //We need to associate the motor with 'name' with a
    //real motor object provided for by ArrayBot
    p->assignUnit(mProcessSequence.getArrayBot());

    return p;
}
}

