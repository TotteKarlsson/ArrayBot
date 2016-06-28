#pragma hdrstop
#include "abProcessSequencer.h"
#include "mtkLogger.h"
#include "abProcess.h"
#include "mtkUtils.h"


//---------------------------------------------------------------------------
using namespace mtk;

ProcessSequencer::ProcessSequencer(const string& fileFolder)
:
mSequences(fileFolder),
mSequenceTimer(100)
{
	inThreadCB = runThreaded;
	mSequenceTimer.assignTimerFunction(inThreadCB);
}

ProcessSequence* ProcessSequencer::getCurrentSequence()
{
	return mSequences.getCurrent();
}

bool ProcessSequencer::assignUnit(ABObject* o)
{
// 	mSequences.assignUnit(o);
    return true;
}

string ProcessSequencer::getCurrentSequenceName()
{
	return mSequences.getCurrentSequenceName();
}

bool ProcessSequencer::addSequence(ProcessSequence* seq)
{
	if(!seq)
    {
    	return false;
    }

	return mSequences.add(seq);
}

bool ProcessSequencer::load(const string& seqName)
{
	return mSequences.load(seqName);
}

bool ProcessSequencer::saveCurrent()
{
	return mSequences.saveCurrent();
}

void ProcessSequencer::clear()
{
	mSequences.clear();
}

bool ProcessSequencer::isCurrentProcessActive()
{
	ProcessSequence* s = mSequences.getCurrent();
    if(!s)
    {
    	return false;
    }

	Process* p = s->getCurrent();
    if(p)
    {
	    return p->isBeingProcessed();
    }

    return false;
}

void ProcessSequencer::runThreaded()
{
 	ProcessSequence* s = mSequences.getCurrent();
    if(!s)
    {
    	return;
    }

    Process* p = s->getCurrent();
	if(p)
    {
    	//Check if we are to move forward in the sequence
        if(p->isProcessed() == true)
        {
        	sleep(p->getPostDwellTime());
        	forward();
        }
        else if (s->isFirst(p) && p->isStarted() == false)
        {

        	sleep(p->getPreDwellTime());
            bool res = p->start();
            if(!res)
            {
                Log(lError) << "Failed executing move: "<<p->getProcessName();
				Log(lError) << "Aborting execution of process sequence: "<<s->getName();
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
        Log(lInfo) << "Finished processing sequence: " << s->getName();
        return;
    }
}

void ProcessSequencer::start(bool autoExecute)
{
 	ProcessSequence* s = mSequences.getCurrent();
    if(!s)
    {
    	return;
    }

	mExecuteAutomatic = autoExecute;

    //ReInit sequence so it can be executed over and over
    s->init();

	Process* aMove = s->getFirst();
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
 	ProcessSequence* s = mSequences.getCurrent();
    if(!s)
    {
    	return;
    }

	Process* p = s->getNext();
    if(p)
    {
    	if(!p->start())
        {
        	Log(lError) << "Failed executing a move: " << p->getProcessName();
			Log(lError) << "Aborting execution of process sequence: "<<s->getName();
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
 	ProcessSequence* s = mSequences.getCurrent();
    if(!s)
    {
    	return;
    }

	Process* p = s->getCurrent();
    if(p)
    {
    	p->undo();
    }
    else
    {
    	Log(lError) << "Can't reverse that move";
    }
}

void ProcessSequencer::stop()
{
	mSequenceTimer.stop();

 	ProcessSequence* s = mSequences.getCurrent();
    if(!s)
    {
    	return;
    }

    if(s->getCurrent())
    {
	   s->getCurrent()->stop();
    }
}

string ProcessSequencer::getCurrentProcessName()
{
 	ProcessSequence* s = mSequences.getCurrent();
    if(!s)
    {
	    return "<none>";
    }

	Process* p = s->getCurrent();
   	return p ? p->getProcessName() : string("<none>");
}

//void ProcessSequencer::addProcess(Process* newMove)
//{
// 	ProcessSequence* s = mSequences.getCurrent();
//    if(!s)
//    {
//	    return;
//    }
//
//
//	mSequences->add(newMove);
//}
//
//bool ProcessSequencer::removeProcess(Process* p)
//{
//	if(!mSequences)
//    {
//    	return false;
//    }
//
//	return mSequences->remove(p);
//}
//
//bool ProcessSequencer::removeProcess(const string& name)
//{
//	if(!mSequences)
//    {
//    	return false;
//    }
//
//	return mSequences->remove(name);
//}

bool ProcessSequencer::isRunning()
{
	return mSequenceTimer.isRunning();
}

