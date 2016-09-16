#pragma hdrstop
#include "abRibbonLengthController.h"
#include <sstream>
#include "abArduinoServer.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------
using namespace mtk;
using namespace std;

RibbonLengthController::RibbonLengthController(ArduinoServer& s)
:
	mArduinoServer(s),
    mSectionCount(0),
    mDesiredRibbonLength(0),
    mAutoPuff(false),
    mAutoZeroCut(false),
    mPrepareForNewRibbon(false),
    mLastCutThicknessPreset(1)
{}

RibbonLengthController::~RibbonLengthController()
{}

void RibbonLengthController::checkProgress()
{
    if(mPrepareForNewRibbon)
    {
        disablePuffer();
        resetSectionCount();
        setCutThicknessPreset(mLastCutThicknessPreset);

        stringstream msg;
    	msg <<"SET_CUT_THICKNESS_PRESET="<<mLastCutThicknessPreset;

        //Post message to the server
    	mArduinoServer.request(msg.str());
        mPrepareForNewRibbon = false;
        return;
    }

    if(mAutoPuff)
    {
        stringstream msg;
        if(mSectionCount == mDesiredRibbonLength - 2)
        {
            msg <<"GET_READY_FOR_ZERO_CUT_1";
        }
        //Next stroke creates ribbon of desired length
        else if(mSectionCount == mDesiredRibbonLength - 1)
        {
            msg <<"GET_READY_FOR_ZERO_CUT_2";
        }
        else if(mSectionCount == mDesiredRibbonLength && mAutoZeroCut == true)
        {
            setZeroCut();
            enablePuffer();
            msg <<"RIBBON_IS_SEPARATING";
        }
        else if(mSectionCount >= mDesiredRibbonLength)
        {
            msg <<"RESTORE_FROM_ZERO_CUT";
        }

        //Post message to the server
        mArduinoServer.notifyClients(msg.str());
    }
}

bool RibbonLengthController::setCutThicknessPreset(int preset)
{
	if(preset != 1)
    {
		mLastCutThicknessPreset = preset;
    }

	return true;
}

bool RibbonLengthController::setZeroCut()
{
    return mArduinoServer.request("SET_CUT_THICKNESS_PRESET=1");
}

bool RibbonLengthController::manualPuff()
{
    resetSectionCount();
	return true;
}

int	RibbonLengthController::getSectionCount()
{
	return mSectionCount;
}

void RibbonLengthController::incrementSectionCount()
{
	mSectionCount++;
}

void RibbonLengthController::setSectionCount(int n)
{
	mSectionCount = n;
}

void RibbonLengthController::resetSectionCount()
{
	mSectionCount = 0;
}

void RibbonLengthController::enableAutoPuff()
{
	mAutoPuff = true;
}

void RibbonLengthController::disableAutoPuff()
{
	mAutoPuff = false;
}

bool RibbonLengthController::getAutoPuffSetting()
{
	return mAutoPuff;
}

void RibbonLengthController::prepareForNewRibbon()
{
	mPrepareForNewRibbon = true;
}

bool RibbonLengthController::enablePuffer()
{
    return mArduinoServer.request("ENABLE_PUFFER");
}

bool RibbonLengthController::disablePuffer()
{
    return mArduinoServer.request("DISABLE_PUFFER");
}

void RibbonLengthController::enableAutoZeroCut()
{
	mAutoZeroCut = true;
}

void RibbonLengthController::disableAutoZeroCut()
{
	mAutoZeroCut = false;
}

bool RibbonLengthController::getAutoZeroCutSetting()
{
	return mAutoZeroCut;
}

int	RibbonLengthController::getDesiredRibbonLength()
{
	return mDesiredRibbonLength;
}

void RibbonLengthController::setDesiredRibbonLength(int n)
{
	mDesiredRibbonLength = n;
}




