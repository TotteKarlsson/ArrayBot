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
    mCutThicknessPreset(0),
    mSectionCount(0),
    mDesiredRibbonLength(0),
    mAutoPuff(false),
    mAutoZeroCut(false)
{}

RibbonLengthController::~RibbonLengthController()
{}

void RibbonLengthController::check()
{
    if(mAutoPuff)
    {
        if(mSectionCount == mDesiredRibbonLength - 2)
        {
            stringstream msg;
            msg <<"GET_READY_FOR_ZERO_CUT_1";
            mArduinoServer.updateClients(msg.str());
        }

        else if(mSectionCount == mDesiredRibbonLength - 1)
        {
            stringstream msg;
            msg <<"GET_READY_FOR_ZERO_CUT_2";
            mArduinoServer.updateClients(msg.str());
        }

        else if(mSectionCount == mDesiredRibbonLength && mAutoZeroCut == true)
        {
            stringstream msg;
            msg <<"SET_ZERO_CUT";
            setZeroCut();
            mArduinoServer.updateClients(msg.str());
        }

        if(mSectionCount >= mDesiredRibbonLength)
        {
            try
            {
                enablePuffer();
            }
            catch(...)
            {
                Log(lError) << "SuperError";
            }
            mSectionCount = 0;
            stringstream msg;

            msg <<"RESTORE_FROM_ZERO_CUT";
            mArduinoServer.updateClients(msg.str());
        }
    }
    else
    {
       ;
    }
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

bool RibbonLengthController::setZeroCut()
{
	return mArduinoServer.mPufferArduino.setCutPreset(1);
}

bool RibbonLengthController::setCutThicknessPreset(int preset)
{
	mCutThicknessPreset = preset;
}

int	RibbonLengthController::getCutThicknessPreset()
{
	return mCutThicknessPreset;
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

void RibbonLengthController::enablePuffer()
{
	mArduinoServer.mPufferArduino.enablePuffer();
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
    mArduinoServer.updateClients(msg.str());
}




