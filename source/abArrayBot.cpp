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
mIsShuttingDown(false),
mJSSettings("JOYSTICK SETTINGS", mIniFile),
mLifts("PAIRED_MOVES", mIniFile)
{}

ArrayBot::~ArrayBot()
{}

JoyStickSettings& ArrayBot::getJoyStickSettings()
{
	return mJSSettings;
}

bool ArrayBot::readINIParameters()
{
	mLifts.readINIParameters();
	mJSSettings.readINIParameters();
    return true;
}

bool ArrayBot::writeINIParameters()
{
	mJSSettings.writeINIParameters();
    mLifts.writeINIParameters();
    return true;
}

bool ArrayBot::isActive()
{
	return mCoverSlip.isActive() || mWhisker.isActive();// || mCoverSlipAngleController.isActive() || mCameraAngleController.isActive();
}

bool ArrayBot::isShuttingDown()
{
	return mIsShuttingDown;
}

void ArrayBot::initialize()
{
	mCoverSlip.initialize();
	mWhisker.initialize();
}

APTMotor* ArrayBot::getCoverSlipAngleController()
{
	return mCoverSlip.getAngleMotor();
}

APTMotor* ArrayBot::getCameraAngleController()
{
	return mWhisker.getAngleMotor();
}

//Todo: setup mechanism to check if the units were shutdown properly
bool ArrayBot::shutDown()
{
    getJoyStick().disable();
	mCoverSlip.shutDown();
	mWhisker.shutDown();
	mIsShuttingDown = true;
    return true;
}

void ArrayBot::stopAll()
{
	//In case the JoyStick is running amok, disable it
    mJoyStick.disable();
    mCoverSlip.stopAll();
    mWhisker.stopAll();
}

bool ArrayBot::applyJoyStickSetting(const string& settingName)
{
	JoyStickSetting *jss = mJSSettings.getSetting(settingName);
    if(!jss)
    {
    	Log(lError) <<"No joystick setting with name: "<<settingName;
        return false;
    }

	vector<double> vals = jss->get();
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
        getWhiskerUnit().getXMotor()->setPotentiometerVelocity(vals[0]);
        getWhiskerUnit().getYMotor()->setPotentiometerVelocity(vals[0]);

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

bool ArrayBot::enableJoyStick()
{
 	//enable angle motor controls
    mCoverSlip.attachJoyStick(&getJoyStick());
    mJoyStick.getX1Axis().setSenseOfDirection(1);

	mWhisker.attachJoyStick(&getJoyStick());
    mJoyStick.getX2Axis().setSenseOfDirection(-1);

    return mJoyStick.enable();
}

void ArrayBot::disableJoyStick()
{
    mCoverSlip.detachJoyStick();
    mWhisker.detachJoyStick();
    mJoyStick.disable();
}

ArrayBotJoyStick& ArrayBot::getJoyStick()
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


