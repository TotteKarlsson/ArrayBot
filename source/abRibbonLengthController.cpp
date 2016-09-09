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

void RibbonLengthController::check()
{
    if(mPrepareForNewRibbon)
    {
        disablePuffer();
        resetSectionCount();
        setCutThicknessPreset(mLastCutThicknessPreset);

        stringstream msg;
    	msg <<"SET_CUT_PRESET="<<mLastCutThicknessPreset;
	    IPCMessage ipc_msg(-1, msg.str());
    	mArduinoServer.postIPCMessage(ipc_msg);

        mPrepareForNewRibbon = false;
        return;
    }

    if(mAutoPuff)
    {
        stringstream msg;
        if(mSectionCount == mDesiredRibbonLength - 2)
        {
            msg <<"GET_READY_FOR_ZERO_CUT_1";
            mArduinoServer.notifyClients(msg.str());
        }
        //Next stroke creates ribbon of desired length
        else if(mSectionCount == mDesiredRibbonLength - 1)
        {
            msg <<"GET_READY_FOR_ZERO_CUT_2";
            mArduinoServer.notifyClients(msg.str());
        }
        else if(mSectionCount == mDesiredRibbonLength && mAutoZeroCut == true)
        {
            setZeroCut();
            enablePuffer();
            msg <<"RIBBON_IS_SEPARATING";
            mArduinoServer.notifyClients(msg.str());
        }
        else if(mSectionCount >= mDesiredRibbonLength)
        {
            msg <<"RESTORE_FROM_ZERO_CUT";
            mArduinoServer.notifyClients(msg.str());
        }
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
    stringstream msg;
    msg <<"SET_CUT_PRESET="<<1;
    IPCMessage ipc_msg(-1, msg.str());
    return mArduinoServer.postIPCMessage(ipc_msg);
}

bool RibbonLengthController::manualPuff()
{
	bool res = mArduinoServer.mPufferArduino.manualPuff();
    if(res)
    {
        resetSectionCount();
    }
	return res;
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
    stringstream msg;
    msg <<"ENABLE_PUFFER";
    IPCMessage ipc_msg(-1, msg.str());
    return mArduinoServer.postIPCMessage(ipc_msg);
}

bool RibbonLengthController::disablePuffer()
{
    stringstream msg;
    msg <<"DISABLE_PUFFER";
    IPCMessage ipc_msg(-1, msg.str());
    return mArduinoServer.postIPCMessage(ipc_msg);
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
    stringstream msg;
    msg <<"DESIRED_RIBBON_LENGTH="<<n;
    mArduinoServer.notifyClients(msg.str());
}




