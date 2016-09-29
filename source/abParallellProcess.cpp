#pragma hdrstop
#include "abParallellProcess.h"
#include "abXYZUnit.h"
#include "abAPTMotor.h"
//#include "abPosition.h"
#include "mtkLogger.h"
#include "abMove.h"
using namespace mtk;
using namespace ab;

//---------------------------------------------------------------------------
ParallellProcess::ParallellProcess(const string& lbl)
:
Process(lbl, NULL)
{
	mProcessType = ptParallell;
}

const string ParallellProcess::getTypeName() const
{
	return "combinedMove";
}

void ParallellProcess::init(ArrayBot& ab)
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

void ParallellProcess::clear()
{
	mProcesses.clear();
}

void ParallellProcess::addProcess(Process* lm)
{
	if(!lm)
    {
    	return;
    }
	if(lm->getProcessName() =="")
    {
    	lm->setProcessName("Action " + mtk::toString((mProcesses.size() + 1)));
    }

	mProcesses.push_back(lm);
}

bool ParallellProcess::removeProcess(const string& name)
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

bool ParallellProcess::removeProcess(Process* m)
{
	return false;
}

Process* ParallellProcess::getProcess(int i)
{
	if(i < mProcesses.size())
    {
    	return (mProcesses[i]);
    }
    return NULL;
}

Process*	ParallellProcess::getProcess(const string& lbl)
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

XMLElement* ParallellProcess::addToXMLDocumentAsChildProcess(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
	for(int i = 0; i < mProcesses.size(); i++)
    {
    	Process* lm = mProcesses[i];
        lm->addToXMLDocumentAsChild(doc, docRoot);
    }

    return dynamic_cast<XMLElement*>(docRoot);
}

bool ParallellProcess::isBeingProcessed()
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

bool ParallellProcess::isProcessed()
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

bool ParallellProcess::isCommandPending()
{
	for(int i = 0; i < mProcesses.size(); i++)
    {
	    Move* m = dynamic_cast<Move*>(mProcesses[i]);
    	if(m && m->isMotorCommandPending())
        {
        	return true;
        }
    }

    return false;
}

bool ParallellProcess::areMotorsActive()
{
	for(int i = 0; i < mProcesses.size(); i++)
    {
	    Move* m = dynamic_cast<Move*>(mProcesses[i]);
    	if(m && m->isMotorCommandPending())
        {
        	return true;
        }
    }

    return false;
}

bool ParallellProcess::start()
{
	for(int i = 0; i < mProcesses.size(); i++)
    {
    	mProcesses[i]->start();
        Log(lInfo) << "Started Action \"" << mProcesses[i]->getProcessName()<<"\"";
    }

	return Process::start();
}

bool ParallellProcess::stop()
{
	for(int i = 0; i < mProcesses.size(); i++)
    {
    	mProcesses[i]->stop();
    }

	return Process::stop();
}

bool ParallellProcess::isDone()
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

bool ParallellProcess::undo()
{
	return false;
}
