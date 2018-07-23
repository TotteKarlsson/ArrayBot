#pragma hdrstop
#include "atRibbonController.h"
#include <sstream>
#include "atArduinoServer.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
using namespace dsl;
using namespace std;

RibbonController::RibbonController(ArduinoServer& s)
:
	mArduinoServer(s),
    mSectionCount(0),
    mDesiredRibbonLength(0),
    mAutoPuff(false),
    mAutoZeroCut(false),
    mPrepareForNewRibbon(false),
    mLastCutThicknessPreset(1)
{}

RibbonController::~RibbonController()
{}

void RibbonController::checkProgress()
{
	static bool isDesiredLengthAchieved(false);

    if(mPrepareForNewRibbon) //Reset ribbon creation
    {
        disablePuffer();
        resetSectionCount();
        setCutThicknessPreset(mLastCutThicknessPreset);

        stringstream msg;
    	msg <<"SET_CUT_THICKNESS_PRESET="<<mLastCutThicknessPreset;

        //Post message to the server
    	mArduinoServer.request(msg.str());
        mPrepareForNewRibbon = false;
		isDesiredLengthAchieved = false;
        return;
    }

    if(mAutoPuff || mAutoZeroCut)
    {
    	//The message is meant for clients
        stringstream msg;
        if(mSectionCount == mDesiredRibbonLength - 2)
        {
            msg << "GET_READY_FOR_ZERO_CUT_1";
        }
        //Next stroke creates ribbon of desired length
        else if(mSectionCount == mDesiredRibbonLength - 1)
        {
            msg << "GET_READY_FOR_ZERO_CUT_2";
        }
        else if(mSectionCount == mDesiredRibbonLength)
        {
        	//Do this only once
            if(isDesiredLengthAchieved == false)
            {
            	if(mAutoZeroCut)
                {
            		setZeroCut();
                }

                if(mAutoPuff)
                {
		            enablePuffer();
                }

                isDesiredLengthAchieved = true;
            }
            msg << "RIBBON_IS_SEPARATING";
        }
        else if(mSectionCount >= mDesiredRibbonLength)
        {
            msg << "RESTORE_FROM_ZERO_CUT";
        }

        //Post message to the server
        mArduinoServer.notifyClients(msg.str());
    }
}

bool RibbonController::setCutThicknessPreset(int preset)
{
	if(preset != 1)
    {
		mLastCutThicknessPreset = preset;
    }

	return true;
}

bool RibbonController::setZeroCut()
{
    return mArduinoServer.request("SET_CUT_THICKNESS_PRESET=1");
}

bool RibbonController::manualPuff()
{
    resetSectionCount();
	return true;
}

int	RibbonController::getSectionCount()
{
	return mSectionCount;
}

void RibbonController::incrementSectionCount()
{
	mSectionCount++;
}

void RibbonController::setSectionCount(int n)
{
	mSectionCount = n;
}

void RibbonController::resetSectionCount()
{
	mSectionCount = 0;
}

void RibbonController::enableAutoPuff()
{
	mAutoPuff = true;
}

void RibbonController::disableAutoPuff()
{
	mAutoPuff = false;
}

bool RibbonController::getAutoPuffSetting()
{
	return mAutoPuff;
}

void RibbonController::prepareForNewRibbon()
{
	mPrepareForNewRibbon = true;
}

bool RibbonController::enablePuffer()
{
    return mArduinoServer.request("ENABLE_PUFFER");
}

bool RibbonController::disablePuffer()
{
    return mArduinoServer.request("DISABLE_PUFFER");
}

void RibbonController::enableAutoZeroCut()
{
	mAutoZeroCut = true;
}

void RibbonController::disableAutoZeroCut()
{
	mAutoZeroCut = false;
}

bool RibbonController::getAutoZeroCutSetting()
{
	return mAutoZeroCut;
}

int	RibbonController::getDesiredRibbonLength()
{
	return mDesiredRibbonLength;
}

void RibbonController::setDesiredRibbonLength(int n)
{
	mDesiredRibbonLength = n;
}




