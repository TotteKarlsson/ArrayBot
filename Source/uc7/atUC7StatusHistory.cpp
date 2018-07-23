#pragma hdrstop
#include "atUC7StatusHistory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

UC7StatusHistory::UC7StatusHistory()
:
mLastStatus(ssUndefined)
{}

UC7StatusHistory::~UC7StatusHistory()
{}

void UC7StatusHistory::clearAll()
{
	clearCycleData();
	clearHistoryData();
}

void UC7StatusHistory::clearCycleData()
{
	mPresentCycle.clear();
}

void UC7StatusHistory::clearHistoryData()
{
	mHistory.clear();
}

deque<UC7StatusPoint> UC7StatusHistory::getCurrentCycle()
{
	return mPresentCycle;
}

void UC7StatusHistory::insert(const UC7StatusPoint& sp)
{
	//Check if we are starting new cycle, i.e. last point was Retracting and
    //new point is Berfore Cutting
    if(sp.status == ssBeforeCutting && mLastStatus.status == ssRetracting)
    {
    	//New cycle started, save current data to the history and start new cycle
        mHistory.push_back(mPresentCycle);
		mPresentCycle.clear();
    }
	mPresentCycle.push_back(sp);
    mLastStatus.status = sp.status;
}

