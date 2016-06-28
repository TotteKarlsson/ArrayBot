#pragma hdrstop
#include "abProcessSequencer.h"
#include "mtkLogger.h"
#include "abProcess.h"
#include "mtkUtils.h"


//---------------------------------------------------------------------------
using namespace mtk;

ProcessSequencer::ProcessSequencer()
:
mSequence(NULL),
mSequenceTimer(100)
{
	inThreadCB = runThreaded;
	mSequenceTimer.assignTimerFunction(inThreadCB);
}

bool ProcessSequencer::assignUnit(ABObject* o)
{
	if(mSequence)
    {
		mSequence->assignUnit(o);
    }
    return true;
}

string ProcessSequencer::getCurrentSequenceName()
{
	return mSequence ? mSequence->getName() : string("");
}

int	ProcessSequencer::getNumberOfProcesses()
{
	return mSequence ? mSequence->getNumberOfProcesses() : -1;
}

void ProcessSequencer::assignSequence(ProcessSequence* seq)
{
	mSequence = seq;
}

bool ProcessSequencer::load(const string& seqFName)
{
	if(!mSequence)
    {
        mSequence = new ProcessSequence;
    }

	return mSequence->read(seqFName);
}

bool ProcessSequencer::saveCurrent(const string& folderName)
{
    if(mSequence)
    {
    	return mSequence->write(folderName);
    }

	return false;
}

void ProcessSequencer::clear()
{
	if(mSequence)
    {
		mSequence->clear();
    }
}

bool ProcessSequencer::isCurrentProcessActive()
{
	if(!mSequence)
    {
    	return false;
    }

	Process* p = mSequence->getCurrent();
    if(p)
    {
	    return p->isBeingProcessed();
    }

    return false;
}

void ProcessSequencer::runThreaded()
{
	if(!mSequence)
    {
    	return;
    }

    Process* p = mSequence->getCurrent();
	if(p)
    {
    	//Check if we are to move forward in the sequence
        if(p->isProcessed() == true)
        {
        	sleep(p->getPostDwellTime());
        	forward();
        }
        else if (mSequence->isFirst(p) && p->isStarted() == false)
        {

        	sleep(p->getPreDwellTime());
            bool res = p->start();
            if(!res)
            {
                Log(lError) << "Failed executing move: "<<p->getProcessName();
				Log(lError) << "Aborting execution of process sequence: "<<mSequence->getName();
	            mSequenceTimer.stop();
                return;
            }
        }
        else if(p->isTimedOut())
        {
        	Log(lError) << "Process: "<<p->getProcessName()<<" timed out";
        	stop();
        }
    }
    else
    {
        //We have finished
        mSequenceTimer.stop();
        Log(lInfo) << "Finished processing sequence: " << mSequence->getName();
        return;
    }
}

void ProcessSequencer::start(bool autoExecute)
{
	if(!mSequence)
    {
    	return;
    }

	mExecuteAutomatic = autoExecute;

    //ReInit sequence so it can be executed over and over
    mSequence->init();

	Process* aMove = mSequence->getFirst();
    if(aMove)
    {
        if(mExecuteAutomatic)
        {
	    	Log(lInfo) << "Executing sequence";
	        mSequenceTimer.start();
        }
    }
    else
    {
    	Log(lError) << "There are no processes to sequence!";
    }
}

void ProcessSequencer::forward()
{
	if(!mSequence)
    {
    	return;
    }

	Process* aMove = mSequence->getNext();
    if(aMove)
    {
    	if(!aMove->start())
        {
        	Log(lError) << "Failed executing a move: " << aMove->getProcessName();
			Log(lError) << "Aborting execution of process sequence: "<<mSequence->getName();
            mSequenceTimer.stop();
        }
    }
    else
    {
    	Log(lInfo) << "Reached the end of process pipeline";
    }
}

void ProcessSequencer::reverse()
{
	if(!mSequence)
    {
    	return;
    }

	Process* aMove = mSequence->getCurrent();
    if(aMove)
    {
    	aMove->undo();
    }
    else
    {
    	Log(lError) << "Can't reverse that move";
    }
}

void ProcessSequencer::stop()
{
	mSequenceTimer.stop();

	if(!mSequence)
    {
    	return;
    }

    if(mSequence->getCurrent())
    {
	   mSequence->getCurrent()->stop();
    }
}

string ProcessSequencer::getCurrentProcessName()
{
	if(!mSequence)
    {
    	return "<none>";
    }

	Process* p = mSequence->getCurrent();
    if(p)
    {
    	return p->getProcessName();
    }

    return "<none>";
}

void ProcessSequencer::addProcess(Process* newMove)
{
	if(!mSequence)
    {
    	return;
    }

	mSequence->add(newMove);
}

bool ProcessSequencer::removeProcess(Process* p)
{
	if(!mSequence)
    {
    	return false;
    }

	return mSequence->remove(p);
}

bool ProcessSequencer::removeProcess(const string& name)
{
	if(!mSequence)
    {
    	return false;
    }

	return mSequence->remove(name);
}

bool ProcessSequencer::isRunning()
{
	return mSequenceTimer.isRunning();
}

