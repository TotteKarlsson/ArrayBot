#pragma hdrstop
#include "abProcessSequencer.h"
#include "mtkLogger.h"
#include "abProcess.h"
#include "mtkUtils.h"


//---------------------------------------------------------------------------
using namespace mtk;

ProcessSequencer::ProcessSequencer()
:
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
	return mSequence.read(seqFName);
}

bool ProcessSequencer::save()
{
	return mSequence.write();
}

void ProcessSequencer::clear()
{
	mSequence.clear();
}

void ProcessSequencer::runThreaded()
{
	if(!isRunning())
    {
    	//Check if are to move forward in the sequence
        Process* p = mSequence.getCurrent();
        if(!p)
        {
        	//We have finished
            mSequenceTimer.stop();
        }
        else if(p->isDone() == true )
        {
        	sleep(p->getDwellTime());
        	forward();
        }
    }
}

void ProcessSequencer::start(bool cont)
{
	mRunContinous = cont;
	Process* aMove = mSequence.getFirst();
    if(aMove)
    {
    	Log(lError) << "Executing first move";
    	aMove->execute();
        if(mRunContinous)
        {
        	sleep(300);
	        mSequenceTimer.start();
        }
    }
    else
    {
    	Log(lError) << "No more moves..";
    }
}

void ProcessSequencer::forward()
{
	Process* aMove = mSequence.getNext();
    if(aMove)
    {
    	aMove->execute();
    }
    else
    {
    	Log(lError) << "No more moves..";
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
{}

void ProcessSequencer::addProcess(Process* newMove)
{
	mSequence.add(newMove);
}

bool ProcessSequencer::isRunning()
{
	Process* m = mSequence.getCurrent();
    if(m)
    {
	    return m->isActive();
    }

    return false;
}

