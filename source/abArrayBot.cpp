#pragma hdrstop
#include "abArrayBot.h"
//---------------------------------------------------------------------------

ArrayBot::ArrayBot(IniFile& ini)
:
mIniFile(ini),
mCoverSlip("CoverSlip Unit", mIniFile),
mWhisker("Whisker Unit", mIniFile),
mJoyStick(NULL),
mCSAngleController("CS Angle Controller", mIniFile),
mCSLift("COVERSLIP_LIFT"),
mIsShuttingDown(false)
{
	mCSLift.readProperties(mIniFile);
}

ArrayBot::~ArrayBot()
{}

bool ArrayBot::isActive()
{
	return mCoverSlip.isActive() || mWhisker.isActive() || mCSAngleController.isActive();
}

bool ArrayBot::isShuttingDown()
{
	return mIsShuttingDown;
}

void ArrayBot::initialize()
{
//	mCoverSlip.initialize();
//	mWhisker.initialize();
//    mCSAngleController.initialize();
}

CoverSlipAngleController& ArrayBot::getAngleController()
{
	return mCSAngleController;
}

//Todo: setup mechanism to check if the units were shutdown properly
bool ArrayBot::shutDown()
{
	mIsShuttingDown = true;
    getJoyStick().disable();
	mCSAngleController.shutDown();
	mCoverSlip.shutDown();
	mWhisker.shutDown();

    return true;
}

void ArrayBot::stopAll()
{
    mJoyStick.disable();
    mCoverSlip.stopAll();
    mWhisker.stopAll();
	mCSAngleController.stop();
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

void ArrayBot::home()
{
	mWhisker.home();
    mCoverSlip.home();
}

void ArrayBot::initWorkingPosition()
{
	//Tell Whisker and Cover slip units to go to
    //Working position
}

void ArrayBot::stow()
{
	mWhisker.stow();
    mCoverSlip.stow();
}

XYZUnit& ArrayBot::getCoverSlipUnit()
{
	return mCoverSlip;
}

XYZUnit& ArrayBot::getWhiskerUnit()
{
	return mWhisker;
}



