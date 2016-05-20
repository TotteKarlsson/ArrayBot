#pragma hdrstop
#include "abMoveSequencer.h"
#include "abSMove.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------

using namespace mtk;

MoveSequencer::MoveSequencer()
:
mIsRunning(false),
mSequenceTimer(100)
{
	inThreadCB = runThreaded;
	mSequenceTimer.assignTimerFunction(inThreadCB);
}

bool MoveSequencer::assignUnit(ABObject* o)
{
	mSequence.assignUnit(o);
}

bool MoveSequencer::load(const string& seqFName)
{
	mSequence.load(seqFName);
}

bool MoveSequencer::save()
{
	mSequence.save();
}

void MoveSequencer::clear()
{
	mSequence.clear();
}

void MoveSequencer::runThreaded()
{
	if(!isRunning())
    {
    	//Check if are to forward
        SMove* aMove = mSequence.getCurrent();
        if(!aMove)
        {
        	//We have finished
            mSequenceTimer.stop();
        }

        if(aMove && aMove->achievedPosition() == true )
        {
        	forward();
        }
    }
}

void MoveSequencer::start(bool cont)
{
	mRunContinous = cont;
	SMove* aMove = mSequence.getFirst();
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

void MoveSequencer::forward()
{
	SMove* aMove = mSequence.getNext();
    if(aMove)
    {
    	aMove->execute();
    }
    else
    {
    	Log(lError) << "No more moves..";
    }
}

void MoveSequencer::reverse()
{
	SMove* aMove = mSequence.getCurrent();
    if(aMove)
    {
    	aMove->undo();
    }
    else
    {
    	Log(lError) << "Can't reverse that move";
    }
}

void MoveSequencer::stop()
{}

void MoveSequencer::addMove(SMove* newMove)
{
	mSequence.add(newMove);
}

bool MoveSequencer::isRunning()
{
	SMove* m = mSequence.getCurrent();
    if(m)
    {
	    return m->isActive();
    }

    return false;
}

