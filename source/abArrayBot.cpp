#pragma hdrstop
#include "abArrayBot.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"
//---------------------------------------------------------------------------

using namespace mtk;

ArrayBot::ArrayBot(IniFile& ini)
:
mIniFile(ini),
mCoverSlip("COVERSLIP UNIT", mIniFile),
mWhisker("WHISKER UNIT", mIniFile),
mJoyStick(),
mCoverSlipAngleController("COVERSLIP ANGLE CONTROLLER", mIniFile),
mCameraAngleController("CAMERA ANGLE CONTROLLER", mIniFile),
mCSLift("COVERSLIP LIFT"),
mIsShuttingDown(false),
mJSSettings("JOYSTICK SETTINGS", mIniFile)
{
	mCSLift.readProperties(mIniFile);
}

ArrayBot::~ArrayBot()
{}

bool ArrayBot::isActive()
{
	return mCoverSlip.isActive() || mWhisker.isActive() || mCoverSlipAngleController.isActive() || mCameraAngleController.isActive() ||     mJoyStick.isEnabled();
}

bool ArrayBot::isShuttingDown()
{
	return mIsShuttingDown;
}

void ArrayBot::initialize()
{
	mCoverSlip.initialize();
	mWhisker.initialize();
    mCoverSlipAngleController.initialize();
    mCameraAngleController.initialize();
}

AngleController& ArrayBot::getCoverSlipAngleController()
{
	return mCoverSlipAngleController;
}

AngleController& ArrayBot::getCameraAngleController()
{
	return mCameraAngleController;
}

//Todo: setup mechanism to check if the units were shutdown properly
bool ArrayBot::shutDown()
{
    getJoyStick().disable();
	mCoverSlipAngleController.shutDown();
	mCameraAngleController.shutDown();
	mCoverSlip.shutDown();
	mWhisker.shutDown();
	mCSLift.writeProperties();
	mIsShuttingDown = true;
    return true;
}

void ArrayBot::stopAll()
{
    mJoyStick.disable();
    mCoverSlip.stopAll();
    mWhisker.stopAll();
	mCoverSlipAngleController.stop();
}

bool ArrayBot::applyJoyStickSetting(const string& settingName)
{
	JoyStickSetting *s = mJSSettings.getSetting(settingName);
    if(!s)
    {
    	Log(lError) <<"No joystick setting with name: "<<settingName;
        return false;
    }

	vector<double> vals = s->get();
    Log(lDebug) << "New XY jog velocity (mm/s): " <<vals[0];
    Log(lDebug) << "New XY jog acceleration (mm/(s*s)): " <<vals[1];

    getJoyStick().getX1Axis().setMaxVelocity(vals[0]);
    getJoyStick().getY1Axis().setMaxVelocity(vals[0]);

    getJoyStick().getX2Axis().setMaxVelocity(vals[0]);
    getJoyStick().getY2Axis().setMaxVelocity(vals[0]);

    Log(lDebug) << "New Z jog velocity (mm/s): " <<vals[2];
    Log(lDebug) << "New Z jog acceleration (mm/(s*s)): " <<vals[3];

    if(getCoverSlipUnit().getXMotor() && getCoverSlipUnit().getYMotor())
    {
        getCoverSlipUnit().getXMotor()->setPotentiometerVelocity(vals[0]);
        getCoverSlipUnit().getYMotor()->setPotentiometerVelocity(vals[0]);

        getCoverSlipUnit().getXMotor()->setJogAcceleration(vals[1]);
        getCoverSlipUnit().getYMotor()->setJogAcceleration(vals[1]);
    }

    if(getWhiskerUnit().getXMotor() && getWhiskerUnit().getYMotor())
    {
        getWhiskerUnit().getXMotor()->setJogAcceleration(vals[1]);
        getWhiskerUnit().getYMotor()->setJogAcceleration(vals[1]);
    }

    if(getCoverSlipUnit().getZMotor())
    {
        getCoverSlipUnit().getZMotor()->setJogVelocity(vals[2]);
        getCoverSlipUnit().getZMotor()->setJogAcceleration(vals[3]);
    }

    if(getWhiskerUnit().getZMotor())
    {
        getWhiskerUnit().getZMotor()->setJogVelocity(vals[2]);
        getWhiskerUnit().getZMotor()->setJogAcceleration(vals[3]);
    }

	return true;
}

void ArrayBot::enableJoyStick()
{
 	//enable angle motor controls
    mCoverSlipAngleController.enableJoyStick(&getJoyStick());
    mCameraAngleController.enableJoyStick(&getJoyStick());

    mCoverSlip.enableJoyStick(&getJoyStick());
    mJoyStick.getX1Axis().setSenseOfDirection(1);

	mWhisker.enableJoyStick(&getJoyStick());
    mJoyStick.getX2Axis().setSenseOfDirection(-1);

    mJoyStick.enable();
}

void ArrayBot::disableJoyStick()
{
    mCoverSlip.disableJoyStick();
    mWhisker.disableJoyStick();
    mJoyStick.disable();
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


