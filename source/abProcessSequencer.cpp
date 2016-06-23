#pragma hdrstop
#include "abProcessSequencer.h"
#include "mtkLogger.h"
#include "abProcess.h"
#include "mtkUtils.h"


//---------------------------------------------------------------------------
using namespace mtk;

ProcessSequencer::ProcessSequencer()
:
mSequence(),
mSequenceTimer(100)
{
	inThreadCB = runThreaded;
	mSequenceTimer.assignTimerFunction(inThreadCB);
}

bool ProcessSequencer::assignUnit(ABObject* o)
{
	mSequence.assignUnit(o);
    return true;
}

bool ProcessSequencer::load(const string& seqFName)
{
	mSequence.clear();
	return mSequence.read(seqFName);
}

bool ProcessSequencer::save(const string& folder)
{
	return mSequence.write(folder);
}

void ProcessSequencer::clear()
{
	mSequence.clear();
}

void ProcessSequencer::runThreaded()
{
	if(!isProcessActive())
    {
    	//Check if we are to move forward in the sequence
        Process* p = mSequence.getCurrent();
        if(!p)
        {
        	//We have finished
            mSequenceTimer.stop();
            Log(lInfo) << "Finished processing sequence: " << mSequence.getName();
        }
        else if(p->isDone() == true )
        {
        	sleep(p->getDwellTime());
        	forward();
        }
        else if(p->isTimedOut())
        {
        	Log(lError) << "Process: "<<p->getProcessName()<<" timed out";
        	stop();
        }
    }
}

void ProcessSequencer::start(bool autoExecute)
{
	mExecuteAutomatic = autoExecute;
	Process* aMove = mSequence.getFirst();
    if(aMove)
    {
    	Log(lInfo) << "Executing first move";
    	bool res = aMove->execute();
        if(!res)
        {
        	Log(lError) << "Failed executing move: "<<aMove->getProcessName();
            return;
        }

        if(mExecuteAutomatic)
        {
        	//Make sure the process started.. (really need a sleep?)
        	//sleep(300);
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
	Process* aMove = mSequence.getNext();
    if(aMove)
    {
    	if(!aMove->execute())
        {
        	Log(lError) << "Failed executing a move: " << aMove->getProcessName();
			Log(lError) << "Aborting execution of process sequence: "<<mSequence.getName();
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
	Process* aMove = mSequence.getCurrent();
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

    if(mSequence.getCurrent())
    {
	   mSequence.getCurrent()->stop();
    }
}

string ProcessSequencer::getCurrentProcessName()
{
	Process* p = mSequence.getCurrent();
    if(p)
    {
    	return p->getProcessName();
    }

    return "<none>";
}

void ProcessSequencer::addProcess(Process* newMove)
{
	mSequence.add(newMove);
}

bool ProcessSequencer::removeProcess(Process* p)
{
	return mSequence.remove(p);
}

bool ProcessSequencer::removeProcess(const string& name)
{
	return mSequence.remove(name);
}

bool ProcessSequencer::isRunning()
{
	return mSequenceTimer.isRunning();
}

bool ProcessSequencer::isProcessActive()
{
	Process* m = mSequence.getCurrent();
    if(m)
    {
	    return m->isActive();
    }

    return false;
}

