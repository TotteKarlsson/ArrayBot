 #pragma hdrstop
#include "abProcessSequencer.h"
#include "mtkLogger.h"
#include "abProcess.h"
#include "mtkUtils.h"

//---------------------------------------------------------------------------
using namespace mtk;

ProcessSequencer::ProcessSequencer(ArrayBot& ab, const string& fileFolder)
:
mAB(ab),
mSequences(fileFolder, "abp", mAB),
mSequenceTimer(100)
{
	mSequenceTimer.assignTimerFunction(onTimerFunc);
}

ProcessSequence* ProcessSequencer::getCurrentSequence()
{
	return mSequences.getCurrent();
}

bool ProcessSequencer::deleteSequence(const string& seq)
{
	return mSequences.remove(seq);
}

bool ProcessSequencer::selectSequence(const string& sName)
{
	return mSequences.select(sName) != NULL ? true : false;
}

bool ProcessSequencer::loadAll(const string& fileFolder)
{
	return mSequences.loadAll(fileFolder);
}

ProcessSequences& ProcessSequencer::getSequences()
{
	return mSequences;
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

void ProcessSequencer::onTimerFunc()
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
	        Log(lInfo) << "Process \"" << p->getProcessName() <<"\" finished";
        	forward();
        }
        else if (s->isFirst(p) && p->isStarted() == false)
        {
	        Log(lInfo) << "Executing process \"" << p->getProcessName() <<"\" of type: "<<p->getProcessType();
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
        	Log(lError) << "Process \""<<p->getProcessName()<<"\" timed out";
        	stop();
        }
    }
    else
    {
        //We have finished
        mSequenceTimer.stop();
        Log(lInfo) << "Finished processing sequence: " << s->getName();
        //Enable the JoyStick

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
    if(!p)
    {
    	Log(lInfo) << "Reached the end of process pipeline";
        return;
    }

    Log(lInfo) << "Executing process \"" << p->getProcessName() <<"\" of type: "<<p->getProcessType();
    if(!p->start())
    {
        Log(lError) << "Failed executing a move: " << p->getProcessName();
        Log(lError) << "Aborting execution of process sequence: "<<s->getName();
        mSequenceTimer.stop();
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
   	return p ? p->getProcessName() : string("");
}

bool ProcessSequencer::isRunning()
{
	return mSequenceTimer.isRunning();
}

