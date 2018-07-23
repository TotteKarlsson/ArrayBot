 #pragma hdrstop
#include "atProcessSequencer.h"
#include "dslLogger.h"
#include "core/atProcess.h"
#include "dslUtils.h"
#include "atStopAndResumeProcess.h"
//---------------------------------------------------------------------------
using namespace dsl;

namespace at
{
ProcessSequencer::ProcessSequencer(ArrayBot& ab, ArrayCamClient& acc,  const string& fileFolder)
:
mAB(ab),
mArrayCamClient(acc),
mSequences(fileFolder, "abp", acc, mAB),
mSequenceTimer(Poco::Timespan::MILLISECONDS * 50)
{
	mSequenceTimer.assignTimerFunction(onTimerFunc);
}

ProcessSequencer::~ProcessSequencer()
{
	mSequenceTimer.assignTimerFunction(NULL);
	mSequenceTimer.stop();
}

bool ProcessSequencer::initCurrentSequence()
{
 	ProcessSequence* s = mSequences.getCurrent();
    if(!s)
    {
    	return false;
    }

    //ReInit sequence so it can be executed over and over
    s->init();
	return true;
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

    //
	Process* p = s->getFirst();
    if(p)
    {
    	Log(lInfo) << "Starting Process Sequence";
        mSequenceTimer.start();
    }
    else
    {
    	Log(lError) << "There are no processes to execute in the process sequence!";
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

void ProcessSequencer::pause()
{
	mSequenceTimer.pause();
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

bool ProcessSequencer::resume()
{
	//Get current process, and 'resume' it
 	ProcessSequence* s = mSequences.getCurrent();
    if(!s)
    {
    	return false;
    }

	Process* p = s->getCurrent();
    if(!p)
    {
    	Log(lInfo) << "The end of process pipeline was reached";
        return false;
    }

    p->resume();
	mSequenceTimer.resume();
  	Log(lInfo) << "The process sequence was resumed";
    return true;
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
	    Log(lInfo) << "Executing process \"" << p->getProcessName() <<"\" of type: "<<p->getProcessTypeAsString();
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
    return gEmptyString;
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
    	Log(lInfo) << "The process sequencer reached the end of the process pipeline";
        return false;
    }

  	Log(lInfo) << "Sequence was forwarded";
    if(mExecuteAutomatic)
    {
	    Log(lInfo) << "Executing process \"" << p->getProcessName() <<"\" of type: "<<p->getProcessTypeAsString();
        if(!p->start())
        {
            Log(lError) << "Failed executing the process: " << p->getProcessName();
            Log(lError) << "Aborting execution of process sequence: "<<s->getName();
            mSequenceTimer.stop();
            return false;
        }
    }
    return true;
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
    	Log(lError) << "No Process Sequence in: "<<__FUNC__;
    	return;
    }

    Process* p = s->getCurrent();
	if(!p)
    {
        //Null process indicate that we have finished
        mSequenceTimer.stop();
        Log(lInfo) << "Finished processing sequence: " << s->getName();
        return;
    }

    //Check if we are to move forward in the sequence
    if(p->isStarted() && p->isProcessed() == true)
    {
        Log(lInfo) << "The process \"" << p->getProcessName() <<"\" finished";

        if(mExecuteAutomatic)
        {
            forward();
        }
        else
        {
            mSequenceTimer.stop();
        }
    }
    else if (s->isFirst(p) && p->isStarted() == false)
    {
        Log(lInfo) << "Executing the first process \"" << p->getProcessName() <<"\" of type: "<<p->getProcessTypeAsString();
        if(!p->start())
        {
            Log(lError) << "Failed executing process: "<<p->getProcessName();
            Log(lError) << "Aborting execution of process sequence: "<<s->getName();
            mSequenceTimer.stop();
            return;
        }
    }
    else if(p->isStarted() && dynamic_cast<StopAndResumeProcess*>(p) != NULL)
    {
        StopAndResumeProcess* srp = dynamic_cast<StopAndResumeProcess*>(p);
        if(srp->isDone() && mExecuteAutomatic == false)
        {
            //The stop and resume process finished
            mSequenceTimer.stop();
            Log(lInfo) << "Finished processing process: "<<srp->getProcessName()<<" in the sequence: " << s->getName();
            return;
        }
        else
        {
            //Tell the UI to show a dialog to resume processing...
            pause();

            //Show dialog showing the information for the StopAndResume process
            srp->showInfoMessageDialog();
            Log(lInfo) << "Enable the resume flag for this process, and execute resume()!";
        }
    }
    else if(p->isTimedOut())
    {
        Log(lError) << "The process \""<<p->getProcessName()<<"\" timed out";
        stop();
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

bool ProcessSequencer::isPaused()
{
	return mSequenceTimer.isPaused();
}

}

