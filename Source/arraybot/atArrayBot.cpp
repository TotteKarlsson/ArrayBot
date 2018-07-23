#pragma hdrstop
#include "atArrayBot.h"
#include "dslLogger.h"
#include "apt/atAPTMotor.h"
//---------------------------------------------------------------------------

using namespace dsl;

namespace at
{
    ArrayBot::ArrayBot(IniFile& ini, const string& appFolder)
    :
    mIsShuttingDown(false),
    mAppDataFolder(appFolder),
    mIniFile(ini),
    mJoyStickID(-1),
    mJoyStick(mJoyStickID.getReference()),

    mRightJoyStickXLeftDeadZone(0),
    mRightJoyStickXRightDeadZone(0),
    mRightJoyStickYLeftDeadZone(0),
    mRightJoyStickYRightDeadZone(0),

    mLeftJoyStickXLeftDeadZone(0),
    mLeftJoyStickXRightDeadZone(0),
    mLeftJoyStickYLeftDeadZone(0),
    mLeftJoyStickYRightDeadZone(0),

    mJSSettings("JOYSTICK SETTINGS",	mIniFile),
    mCoverSlip(	"COVERSLIP UNIT", 		mIniFile, appFolder),
    mWhisker(	"WHISKER UNIT", 		mIniFile, appFolder),
    mLifts(		"PAIRED_MOVES", 		mIniFile)//,
    //mServer(*this)
    {
    	//Setup UI properties
        mProperties.setSection("ARRAYBOT_GENERAL");
    	mProperties.setIniFile(&mIniFile);
    	mProperties.add((BaseProperty*)  &mJoyStickID.setup( 	                "JOYSTICK_ID",    	                1));

    	//Read JS deadzones
    	mProperties.add((BaseProperty*)  &mRightJoyStickXLeftDeadZone.setup( 	"JS_RIGHT_X_AXIS_LEFT_DEADZONE",         0));
    	mProperties.add((BaseProperty*)  &mRightJoyStickXRightDeadZone.setup(   "JS_RIGHT_X_AXIS_RIGHT_DEADZONE",        0));
    	mProperties.add((BaseProperty*)  &mRightJoyStickYLeftDeadZone.setup( 	"JS_RIGHT_Y_AXIS_TOP_DEADZONE",          0));
    	mProperties.add((BaseProperty*)  &mRightJoyStickYRightDeadZone.setup(   "JS_RIGHT_Y_AXIS_BOTTOM_DEADZONE",       0));

    	mProperties.add((BaseProperty*)  &mLeftJoyStickXLeftDeadZone.setup( 	"JS_LEFT_X_AXIS_LEFt_DEADZONE",         0));
    	mProperties.add((BaseProperty*)  &mLeftJoyStickXRightDeadZone.setup(    "JS_LEFT_X_AXIS_RIGHT_DEADZONE",        0));
    	mProperties.add((BaseProperty*)  &mLeftJoyStickYLeftDeadZone.setup( 	"JS_LEFT_Y_AXIS_TOP_DEADZONE",          0));
    	mProperties.add((BaseProperty*)  &mLeftJoyStickYRightDeadZone.setup(    "JS_LEFT_Y_AXIS_BOTTOM_DEADZONE",       0));

        mProperties.read();

    	mJoyStick.getX1Axis().setDeadZones(mRightJoyStickXLeftDeadZone, mLeftJoyStickXRightDeadZone);
    	mJoyStick.getY1Axis().setDeadZones(mRightJoyStickXLeftDeadZone, mLeftJoyStickXRightDeadZone);

    	mJoyStick.getX2Axis().setDeadZones(mRightJoyStickXLeftDeadZone, mRightJoyStickXRightDeadZone);
    	mJoyStick.getY2Axis().setDeadZones(mRightJoyStickXLeftDeadZone, mRightJoyStickXRightDeadZone);


        if(!mJoyStick.enableJoyStickWithID(mJoyStickID))
        {
        	Log(lWarning) << "Joystick with ID: " << mJoyStickID << " was not enabled.";
        }
    }

    ArrayBot::~ArrayBot()
    {
        mProperties.write();
    }

    bool ArrayBot::enableCoverSlipUnit()
    {
    	mCoverSlip.enableJSAxes();
        mCoverSlip.enableZButtons();
        return true;
    }

    bool ArrayBot::disableCoverSlipUnit()
    {
    	mCoverSlip.disableJSAxes();
        mCoverSlip.disableZButtons();
        return true;
    }

    bool ArrayBot::enableWhiskerUnit()
    {
    	mWhisker.enableJSAxes();
        return true;
    }

    bool ArrayBot::disableWhiskerUnit()
    {
    	mWhisker.disableJSAxes();
        return true;
    }

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

    APTMotor* ArrayBot::getMotorWithSerial(const string& s)
    {
    	vector<APTMotor*> ms = getAllMotors();
        for(int i = 0; i < ms.size(); i++)
        {
        	if(ms[i]->getSerial() == s)
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
        mProperties.read();
    	mLifts.readINIParameters();
    	mJSSettings.readINIParameters();
        return true;
    }

    bool ArrayBot::writeINIParameters()
    {
        mProperties.write();
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
    //    sleep(500);
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
    	//In case the JoyStick is running amok, disable it (has never happened actually..)
        mJoyStick.disable();
        mCoverSlip.stopAll();
        mWhisker.stopAll();
    }

    void ArrayBot::homeAll()
    {
        mJoyStick.disable();
        mCoverSlip.home();
        mWhisker.home();
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
    	if(!mJoyStick.isValid())
        {
    		return false;
        }

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

    void ArrayBot::enableJoyStickAxes()
    {
    	mWhisker.enableJSAxes();
        mCoverSlip.enableJSAxes();

        if(mJSSettings.getCurrent())
        {
    		applyJoyStickSetting(mJSSettings.getCurrent()->getLabel());
        }
        else
        {
        	Log(lError) << "No JOYSTICK setting to set! Setup ini file!!";
        }
    }

    void ArrayBot::disableJoyStickAxes()
    {
    	mWhisker.disableJSAxes();
        mCoverSlip.disableJSAxes();
    }

    XYZUnit& ArrayBot::getCoverSlipUnit()
    {
    	return mCoverSlip;
    }

    XYZUnit& ArrayBot::getWhiskerUnit()
    {
    	return mWhisker;
    }


}
