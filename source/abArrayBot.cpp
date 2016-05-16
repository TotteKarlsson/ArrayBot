#pragma hdrstop
#include "abArrayBot.h"
//---------------------------------------------------------------------------

ArrayBot::ArrayBot(IniFile& ini)
:
mIniFile(ini),
mCoverSlip("CoverSlip Unit", mIniFile),
mWhisker("Whisker Unit", mIniFile),
mJoyStick(NULL)
{

}

ArrayBot::~ArrayBot()
{
}

void ArrayBot::stopAll()
{
    mJoyStick.disable();
    mCoverSlip.stopAll();
    mWhisker.stopAll();
}

void ArrayBot::enableWhiskerJoyStick()
{
    mWhisker.enableJoyStick(&getJoyStick());
	mJoyStick.getXAxis().setSenseOfDirection(-1);
    mCoverSlip.disableJoyStick();
    mJoyStick.enable();
}

void ArrayBot::enableCoverSlipJoyStick()
{
    mCoverSlip.enableJoyStick(&getJoyStick());
    mJoyStick.getXAxis().setSenseOfDirection(1);
    mWhisker.disableJoyStick();
    mJoyStick.enable();
}

void ArrayBot::disableJoyStick()
{
    mCoverSlip.disableJoyStick();
    mWhisker.disableJoyStick();
    mJoyStick.disable();

}

void ArrayBot::assignWindowHandle(int handle)
{
	mJoyStick.setWindowHandle(handle);
}

JoyStick& ArrayBot::getJoyStick()
{
	return mJoyStick;
}

//Todo: setup mechanism to check if the units were shutdown properly
bool ArrayBot::shutDown()
{
	mCoverSlip.shutDown();
	mWhisker.shutDown();

    return true;
}

XYZUnit& ArrayBot::getCoverSlipUnit()
{
	return mCoverSlip;
}

XYZUnit& ArrayBot::getWhiskerUnit()
{
	return mWhisker;
}

void ArrayBot::initialize()
{
	mCoverSlip.initialize();
	mWhisker.initialize();
}



