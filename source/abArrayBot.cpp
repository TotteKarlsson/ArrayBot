#pragma hdrstop
#include "abArrayBot.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"
//---------------------------------------------------------------------------

using namespace mtk;

ArrayBot::ArrayBot(IniFile& ini, const string& appFolder)
:
mAppDataFolder(appFolder),
mIniFile(ini),
mCoverSlip("COVERSLIP UNIT", mIniFile, appFolder),
mWhisker("WHISKER UNIT", mIniFile, appFolder),
mJoyStick(),
mIsShuttingDown(false),
mJSSettings("JOYSTICK SETTINGS", mIniFile),
mLifts("PAIRED_MOVES", mIniFile)
{}

ArrayBot::~ArrayBot()
{}

vector<APTMotor*> ArrayBot::getAllMotors()
{
	vector<APTMotor*> ms;
	vector<APTMotor*> ms1 = mCoverSlip.getAllMotors();
	vector<APTMotor*> ms2 = mWhisker.getAllMotors();

	ms.insert(ms.begin(), ms1.begin(), ms1.end());
	ms.insert(ms.end(), ms2.begin(), ms2.end());

    return ms;
}

APTMotor* ArrayBot::getMotorWithName(const string& mn)
{
	vector<APTMotor*> ms = getAllMotors();
    for(int i = 0; i < ms.size(); i++)
    {
    	if(ms[i]->getName() == mn)
        {
        	return ms[i];
        }
    }
    return NULL;
}

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
	return mCoverSlip.isActive() || mWhisker.isActive();
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

    //This is the max velocity that can be achieved using the JoyStick
    mJoyStick.setAxesMaxVelocity(vals[0]);

    Log(lDebug) << "New Z jog velocity (mm/s): " <<vals[2];
    Log(lDebug) << "New Z jog acceleration (mm/(s*s)): " <<vals[3];

    //TODO: Clean this up
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
        getCoverSlipUnit().getZMotor()->setJogMoveParameters(vals[2], vals[3]);
    }

    if(getWhiskerUnit().getZMotor())
    {
        getWhiskerUnit().getZMotor()->setJogMoveParameters(vals[2], vals[3]);
    }

    Log(lDebug) << "New Angle Jog Velocity (mm/s): " <<vals[4];
    Log(lDebug) << "New Angle Jog Acceleration (mm/(s*s)): " <<vals[5];

    if(getCoverSlipUnit().getAngleMotor())
    {
        getCoverSlipUnit().getAngleMotor()->setJogMoveParameters(vals[4], vals[5]);
    }

    if(getWhiskerUnit().getAngleMotor())
    {
        getWhiskerUnit().getAngleMotor()->setJogMoveParameters(vals[4], vals[5]);
    }

	return true;
}

ArrayBotJoyStick& ArrayBot::getJoyStick()
{
	return mJoyStick;
}

bool ArrayBot::enableJoyStick()
{
    mCoverSlip.attachJoyStick(&getJoyStick());
    mJoyStick.getX1Axis().setSenseOfDirection(1);

	mWhisker.attachJoyStick(&getJoyStick());
    mJoyStick.getX2Axis().setSenseOfDirection(-1);

    return mJoyStick.enable();
}

void ArrayBot::disableJoyStick()
{
    mJoyStick.disable();
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
    mCoverSlip.stow();
	mWhisker.stow();
}

XYZUnit& ArrayBot::getCoverSlipUnit()
{
	return mCoverSlip;
}

XYZUnit& ArrayBot::getWhiskerUnit()
{
	return mWhisker;
}


