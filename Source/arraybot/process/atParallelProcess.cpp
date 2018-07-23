#pragma hdrstop
#include "atParallelProcess.h"
#include "atXYZUnit.h"
#include "apt/atAPTMotor.h"
#include "dslLogger.h"
#include "atMove.h"
#include "arraybot/process/atProcessSequence.h"
using namespace dsl;
using namespace at;

namespace at
{

    //---------------------------------------------------------------------------
    ParallelProcess::ParallelProcess(const string& lbl)
    :
    Process(lbl, NULL)
    {
    	mProcessType = ptParallel;
    }

    const string ParallelProcess::getTypeName() const
    {
    	return toString(mProcessType);
    }

    void ParallelProcess::init(ArrayBot& ab)
    {
    	Process::init(ab);

        //Call init for each sub move
        for(int i = 0; i < mProcesses.size(); i++)
        {
        	if(mProcesses[i])
            {
            	mProcesses[i]->init(ab);
            }
        }
    }

    void ParallelProcess::clear()
    {
    	mProcesses.clear();
    }

    bool ParallelProcess::write()
    {
    	if(mProcessSequence)
        {
        	return mProcessSequence->write();
        }
    	return false;
    }

    void ParallelProcess::addProcess(Process* lm)
    {
    	if(!lm)
        {
        	return;
        }
    	if(lm->getProcessName() =="")
        {
        	lm->setProcessName("Action " + dsl::toString((mProcesses.size() + 1)));
        }

    	mProcesses.push_back(lm);
    }

    bool ParallelProcess::removeProcess(const string& name)
    {
    	for(int i = 0; i < mProcesses.size(); i++)
        {
        	if(mProcesses[i]->getProcessName() == name)
            {
            	Process* lm = (mProcesses[i]);
                mProcesses.erase(mProcesses.begin() + i);
            }
        }
        return true;
    }

    bool ParallelProcess::removeProcess(Process* m)
    {
    	return false;
    }

    Process* ParallelProcess::getProcess(int i)
    {
    	if(i < mProcesses.size())
        {
        	return (mProcesses[i]);
        }
        return NULL;
    }

    Process* ParallelProcess::getProcess(const string& lbl)
    {
    	// look for item
        for(int i = 0 ; i < mProcesses.size(); i++)
        {
        	Process* mv = mProcesses[i];
            if(mv->getProcessName() == lbl)
            {
            	return mv;
            }
        }
        return NULL;
    }

    Process* ParallelProcess::getProcess(const Process* p)
    {
    	// look for item
        for(int i = 0 ; i < mProcesses.size(); i++)
        {
        	Process* aProc = mProcesses[i];
            if(aProc == p)
            {
            	return aProc;
            }
        }
        return NULL;
    }

    bool ParallelProcess::isBeingProcessed()
    {
    	if(isDone())
        {
    		mIsBeingProcessed = false;
            mIsProcessed = true;
           	Timestamp now;
            mEndTime = now;
        }

        return mIsBeingProcessed;
    }

    bool ParallelProcess::isProcessed()
    {
        if(mIsProcessed == true)
        {
        	return true;
        }

        if(isDone())
        {
            //Consider this process to be "processed"
            mIsProcessed 		= true;
            mIsBeingProcessed 	= false;
            return true;
        }

    	return false;
    }

    bool ParallelProcess::isCommandPending()
    {
    	for(int i = 0; i < mProcesses.size(); i++)
        {
    	    at::Move* m = dynamic_cast<at::Move*>(mProcesses[i]);
        	if(m && m->isMotorCommandPending())
            {
            	return true;
            }
        }

        return false;
    }

    bool ParallelProcess::areMotorsActive()
    {
    	for(int i = 0; i < mProcesses.size(); i++)
        {
    	    at::Move* m = dynamic_cast<at::Move*>(mProcesses[i]);
        	if(m && m->isMotorCommandPending())
            {
            	return true;
            }
        }

        return false;
    }

    bool ParallelProcess::start()
    {
    	for(int i = 0; i < mProcesses.size(); i++)
        {
        	mProcesses[i]->start();
            Log(lInfo) << "Started Action \"" << mProcesses[i]->getProcessName()<<"\"";
        }

    	return Process::start();
    }

    bool ParallelProcess::resume()
    {
    	for(int i = 0; i < mProcesses.size(); i++)
        {
        	mProcesses[i]->resume();
            Log(lInfo) << "Started Action \"" << mProcesses[i]->getProcessName()<<"\"";
        }

    	return Process::start();
    }

    bool ParallelProcess::stop()
    {
    	for(int i = 0; i < mProcesses.size(); i++)
        {
        	mProcesses[i]->stop();
        }

    	return Process::stop();
    }

    bool ParallelProcess::isDone()
    {
    	//Check all subprocesses here
    	for(int i = 0; i < mProcesses.size(); i++)
        {
        	if(!mProcesses[i]->isDone())
            {
            	return false;
            }
        }

        return true;
    }

    bool ParallelProcess::undo()
    {
    	return false;
    }

    XMLElement* ParallelProcess::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
    {
    	for(int i = 0; i < mProcesses.size(); i++)
        {
        	Process* pp = mProcesses[i];
            dsl::XMLElement* newElement = pp->addToXMLDocument(doc, docRoot);
            pp->addToXMLDocumentAsChild(doc, newElement);
        }

        return dynamic_cast<XMLElement*>(docRoot);
    }

}

