#pragma hdrstop
#include "abProcessSequenceProject.h"
#include "mtkXMLUtils.h"
#include "mtkLogger.h"
#include "abProcessSequence.h"
#include "abCombinedMove.h"
#include "abPosition.h"
#include "abArrayBot.h"
#include "abAbsoluteMove.h"
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
    mProjectRoot = mTheXML.NewElement("ProcessSequenceProject");
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
    XMLElement* processes = newElement("ProcessSequence");

    //First save Processes
    Process* p = mProcessSequence.getFirst();
    while(p)
    {
        Log(lDebug) << "Saving process: " << p->getProcessName();
        XMLElement* elem = p->addToXMLDocument(mTheXML, processes);
        if(dynamic_cast<CombinedMove*>(p))
	    {
        	CombinedMove* clm = dynamic_cast<CombinedMove*>(p);
        	//Write subprocesses
			clm->addToXMLDocumentAsChildProcess(mTheXML, elem);
        }

        p = mProcessSequence.getNext();
    }

    this->addNode(processes);
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
    XMLElement* processes = this->getXML("ProcessSequence");

    if(processes == NULL)
    {
        return 0;
    }

    int nrOfObjects = 0;

     //Load process by process
    XMLElement* p = processes->FirstChildElement();
    while(p)
    {
        //Find out what kind of element p is
        Process* aProc = createProcess(p);
        if(aProc)
        {
            mProcessSequence.add(aProc);
            Log(lDebug) <<"Imported a "<<p->Name()<<" process.";
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

    XMLElement* elem = element->FirstChildElement("process_type");
	ProcessType pt = toProcessType(elem->GetText());

  	//What process?
    switch(pt)
    {
    	case ptCombinedMove:
        	CombinedMove* p = new CombinedMove("");
            string name = element->FirstChildElement("process_name")->GetText();
            p->setProcessName(name);

            //Read and create sub moves
            XMLElement* processes = element->FirstChildElement("processes");
            if(processes)
            {
            	XMLElement* processE = processes->FirstChildElement();

                //Loop over childs
                while(processE)
                {
	                AbsoluteMove* lm(NULL);

                    const char* name = processE->Attribute("name");
                    if(name)
                    {
			            Log(lDebug) << "Loading element: "<<name;

                        const char* type = processE->Attribute("type");
                        if(compareNoCase(type, "ABSOLUTE_MOVE"))
                        {
    	  	                lm = new AbsoluteMove(name);
                        }

                        const char* val = processE->Attribute("motor_name");
                        if(val)
                        {
                        	lm->setMotorName(val);
                        }

                        val = processE->Attribute("final_position");
                        if(val)
                        {
                        	lm->setPosition( ab::Position("", toDouble(val), 0.0 , 0.0));
                        }

                        val = processE->Attribute("max_velocity");
                        if(val)
                        {
                        	lm->setMaxVelocity(toDouble(val));
                        }

                        val = processE->Attribute("acc");
                        if(val)
                        {
                        	lm->setAcceleration(toDouble(val));
                        }

                        val = processE->Attribute("pre_dwell_time");
                        if(val)
                        {
                        	lm->setPreDwellTime(toDouble(val));
                        }

                        val = processE->Attribute("post_dwell_time");
                        if(val)
                        {
                        	lm->setPostDwellTime(toDouble(val));
                        }

                        //We need to associate the motor with 'name' with a
                        //real motor object provided for by ArrayBot
                        lm->assignUnit(mProcessSequence.getArrayBot());
	                    p->addMove(lm);
	                }

                    processE = processE->NextSiblingElement();
                }
            }

        return p;
    }

    return NULL;
}

