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
mSequenceTimer(50)
{
	mSequenceTimer.assignTimerFunction(onTimerFunc);
}

ProcessSequencer::~ProcessSequencer()
{
	mSequenceTimer.assignTimerFunction(NULL);
	mSequenceTimer.stop();
}

void ProcessSequencer::start(bool autoExecute)
{
 	ProcessSequence* s = mSequences.getCurrent();
    if(!s)
    {
    	return;
    }

    //ReInit sequence so it can be executed over and over
    s->init();

	mExecuteAutomatic = autoExecute;
	Process* p = s->getFirst();
    if(p)
    {
    	Log(lInfo) << "Executing sequence";
        mSequenceTimer.start();
    }
    else
    {
    	Log(lError) << "There are no processes to sequence!";
    }
}

bool ProcessSequencer::reset()
{
 	ProcessSequence* s = mSequences.getCurrent();
    if(!s)
    {
    	return false;
    }
	s->init();
    return true;
}

bool ProcessSequencer::continueExecution()
{
 	ProcessSequence* s = mSequences.getCurrent();
    if(!s)
    {
    	return false;
    }

	Process* p = s->getCurrent();
    if(p)
    {
        mSequenceTimer.start();
	    Log(lInfo) << "Executing process \"" << p->getProcessName() <<"\" of type: "<<p->getProcessType();
        if(!p->start())
        {
            Log(lError) << "Failed executing a process: " << p->getProcessName();
            Log(lError) << "Aborting execution of process sequence: "<<s->getName();
            mSequenceTimer.stop();
            return false;
        }
	}
    else
    {
    	Log(lError) << "There are no processes to sequence!";
        return false;
    }
    return true;
}

string ProcessSequencer::getNextProcessName()
{
 	ProcessSequence* s = mSequences.getCurrent();
    if(!s)
    {
    	return false;
    }

    if(s->peekNext() != NULL)
    {
    	return s->peekNext()->getProcessName();
    }
    return gNoneString;
}

bool ProcessSequencer::isDone()
{
 	ProcessSequence* s = mSequences.getCurrent();
    if(!s)
    {
    	return true;
    }

	return s->getCurrent() == NULL ? true : false;
}

bool ProcessSequencer::canContinue()
{
 	ProcessSequence* s = mSequences.getCurrent();
    if(!s)
    {
    	return false;
    }
    return s->peekNext() == NULL ? false : true;
}

bool ProcessSequencer::forward()
{
 	ProcessSequence* s = mSequences.getCurrent();
    if(!s)
    {
    	return false;
    }

	Process* p = s->getNext();
    if(!p)
    {
    	Log(lInfo) << "Reached the end of process pipeline";
        return false;
    }

  	Log(lInfo) << "Sequence was forwarded";


    if(mExecuteAutomatic)
    {
	    Log(lInfo) << "Executing process \"" << p->getProcessName() <<"\" of type: "<<p->getProcessType();
        if(!p->start())
        {
            Log(lError) << "Failed executing a move: " << p->getProcessName();
            Log(lError) << "Aborting execution of process sequence: "<<s->getName();
            mSequenceTimer.stop();
            return false;
        }
    }
    return true;
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
        if(p->isProcessed() == true && mExecuteAutomatic)
        {
	        Log(lInfo) << "Process \"" << p->getProcessName() <<"\" finished";
        	forward();
        }
        else if (s->isFirst(p) && p->isStarted() == false)
        {
	        Log(lInfo) << "Executing process \"" << p->getProcessName() <<"\" of type: "<<p->getProcessType();
            if(!p->start())
            {
                Log(lError) << "Failed executing process: "<<p->getProcessName();
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
        else if(p->isProcessed() == true && mExecuteAutomatic == false)
        {
            //We have finished one process in the sequence
            mSequenceTimer.stop();
            Log(lInfo) << "Finished processing process: "<<p->getProcessName()<<" in the sequence: " << s->getName();
        }
    }
    else
    {
        //Null process indicate that we have finished
        mSequenceTimer.stop();
        Log(lInfo) << "Finished processing sequence: " << s->getName();
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

