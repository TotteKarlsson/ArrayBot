#pragma hdrstop
#include "abCombinedLinearMove.h"
#include "abXYZUnit.h"
#include "abAPTMotor.h"
#include "abPosition.h"
#include "mtkLogger.h"

using namespace mtk;
using namespace ab;

//---------------------------------------------------------------------------
CombinedLinearMove::CombinedLinearMove(const string& lbl)
:
Process(lbl, NULL)
{
	mProcessType = ptCombinedLinearMove;
}

void CombinedLinearMove::addMove(LinearMove& lm)
{
	mLinearMoves.push_back(lm);
}

bool CombinedLinearMove::isBeingProcessed()
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

bool CombinedLinearMove::isProcessed()
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
    else
    {
        return false;
    }

	return false;
}

bool CombinedLinearMove::isDone()
{

    return false;
}

bool CombinedLinearMove::isCommandPending()
{
	return false;
}

bool CombinedLinearMove::areMotorsActive()
{
    return false;
}

bool CombinedLinearMove::write(IniSection* sec)
{
    return true;
}

bool CombinedLinearMove::read(IniSection* sec)
{
    return true;
}

bool CombinedLinearMove::start()
{
	Process::start();
    return false;
}

bool CombinedLinearMove::stop()
{
	Process::stop();

    return false;
}

bool CombinedLinearMove::undo()
{
	return false;
}
