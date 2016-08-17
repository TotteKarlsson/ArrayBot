#pragma hdrstop
#include "abXYZUnit.h"
#include "abArrayBotJoyStick.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"

//---------------------------------------------------------------------------
using namespace mtk;

XYZUnit::XYZUnit(const string& name, IniFile& iniFile, const string& appDataFolder)
:
mAppDataFolder(appDataFolder),
mXMotorSerialNr(-1),
mYMotorSerialNr(-1),
mZMotorSerialNr(-1),
mAngleMotorSerialNr(-1),
mName(name),
mXMotor(NULL),
mYMotor(NULL),
mZMotor(NULL),
mAngleMotor(NULL),
mJoyStick(NULL),
mIniFile(iniFile)
{
	//Setup properties
    mProperties.setSection(name);
    mProperties.add((BaseProperty*) &mXMotorSerialNr.setup("XMotorSerial", -1, true));
    mProperties.add((BaseProperty*) &mYMotorSerialNr.setup("YMotorSerial", -1, true));
    mProperties.add((BaseProperty*) &mZMotorSerialNr.setup("ZMotorSerial", -1, true));
    mProperties.add((BaseProperty*) &mAngleMotorSerialNr.setup("AngleMotorSerial", -1, true));

	//assign inifile to use with the properties
    mProperties.setIniFile(&mIniFile);
}

XYZUnit::~XYZUnit()
{}

vector<APTMotor*> XYZUnit::getAllMotors()
{
	vector<APTMotor*> ms;

	if(mXMotor)
    {
        ms.push_back(mXMotor);
    }

	if(mYMotor)
    {
        ms.push_back(mYMotor);
    }

	if(mZMotor)
    {
        ms.push_back(mZMotor);
    }

    if(mAngleMotor)
    {
        ms.push_back(mAngleMotor);
    }
	return ms;
}

bool XYZUnit::isActive()
{
	bool xa(false), ya(false), za(false), ca(false);

	if(mXMotor)
    {
        xa = mXMotor->isActive();
    }

	if(mYMotor)
    {
        ya = mYMotor->isActive();
    }

	if(mZMotor)
    {
        za = mZMotor->isActive();
    }

    if(mAngleMotor)
    {
    	ca = mAngleMotor->isActive();
    }

    return xa || ya || za || ca;
}

bool XYZUnit::initialize()
{
    mProperties.read();
	mDeviceManager.reBuildDeviceList();
    Log(lInfo) << "Initializing XYZUnit: "<< mName;

	//Setup all the motors
    mXMotor = dynamic_cast<APTMotor*>(mDeviceManager.connectDevice(mXMotorSerialNr));
    if(mXMotor)
    {
    	Log(lInfo)<<"X motor is connected";

        //Load Motor Properties
        mXMotor->loadProperties(mIniFile);
        mXMotor->setName(mName + "_X");
    }
    else
    {
		Log(lError) << "X motor is NOT connected";
    }

    mYMotor = dynamic_cast<APTMotor*>(mDeviceManager.connectDevice(mYMotorSerialNr));
    if(mYMotor)
    {
    	Log(lInfo) << "Y motor is connected";
        //Load Motor Properties
        mYMotor->loadProperties(mIniFile);
        mYMotor->setName(mName + "_Y");
    }
    else
    {
		Log(lError) << "Y motor is NOT connected";
    }

    mZMotor = dynamic_cast<APTMotor*>(mDeviceManager.connectDevice(mZMotorSerialNr));
    if(mZMotor)
    {
    	Log(lInfo) << "Zmotor is connected";

        //Load Motor Properties
        mZMotor->loadProperties(mIniFile);
        mZMotor->setName(mName + "_Z");
    }
    else
    {
		Log(lError) << "Z motor is NOT connected";
    }

    mAngleMotor = dynamic_cast<APTMotor*>(mDeviceManager.connectDevice(mAngleMotorSerialNr));
    if(mAngleMotor)
    {
    	Log(lInfo) << "Angle motor is connected";

        //Load Motor Properties
        mAngleMotor->loadProperties(mIniFile);
        mAngleMotor->setName(mName + "_Angle");
    }
    else
    {
		Log(lError) << "Angle motor is NOT connected";
    }

	return true;
}

bool XYZUnit::enableZButtons()
{
	if(mJoyStick)
    {
    	if(mName == "COVERSLIP UNIT")
        {
        	mJoyStick->enableCoverSlipZButtons();
        }
        else if(mName == "WHISKER UNIT")
        {
        	mJoyStick->enableWhiskerZButtons();
        }
	    return true;
    }
    return false;
}

bool XYZUnit::disableZButtons()
{
	if(mJoyStick)
    {
    	if(mName == "COVERSLIP UNIT")
        {
        	mJoyStick->disableCoverSlipZButtons();
        }
        else if(mName == "WHISKER UNIT")
        {
        	mJoyStick->disableWhiskerZButtons();
        }
	    return true;
    }
    return false;
}

bool XYZUnit::enableJSAxes()
{
	if(mJoyStick)
    {
    	if(mName == "COVERSLIP UNIT")
        {
    		mJoyStick->enableCoverSlipAxes();
        }
        else if(mName == "WHISKER UNIT")
        {
    		mJoyStick->enableWhiskerAxes();
        }
	    return true;
    }
    return false;
}

bool XYZUnit::disableJSAxes()
{
	if(mJoyStick)
    {
    	if(mName == "COVERSLIP UNIT")
        {
    		mJoyStick->disableCoverSlipAxes();
        }
        else if(mName == "WHISKER UNIT")
        {
    		mJoyStick->disableWhiskerAxes();
        }
	    return true;
    }
    return false;
}

void XYZUnit::shutDown()
{
	mDeviceManager.disConnectAll();

    //Now motors are NULL.. make them smart pointers
    mXMotor = mYMotor = mZMotor = mAngleMotor = NULL;

	//Save Properties
	mProperties.write();
}

void XYZUnit::stow()
{
//	//The stow function rely on a Process Sequence named "stow"
//    string fName("Sequence 1." + getName());
//	if(mMoveSequencer.load(joinPath(mAppDataFolder, fName)))
//    {
//        mMoveSequencer.assignUnit(this);
//     	Log(lInfo) << "Loaded process sequence: "<<mMoveSequencer.getSequence().getName();
//        mMoveSequencer.start();
//       	Log(lInfo) << "Started sequence: "<<mMoveSequencer.getSequence().getName();
//    }
}

string XYZUnit::getName() const
{
	return mName;
}

void XYZUnit::home()
{
    if(mXMotor)
    {
    	Log(lDebug)<<"Homing X Motor..";
		mXMotor->home();
    }

    if(mYMotor)
    {
    	Log(lDebug)<<"Homing Y Motor..";
		mYMotor->home();
    }

    if(mZMotor)
    {
    	Log(lDebug)<<"Homing Z Motor..";
		mZMotor->home();
    }
}

void XYZUnit::attachJoyStick(ArrayBotJoyStick* js)
{
	if(!js)
    {
    	return;
    }

    mJoyStick = js;

    if(mName == "COVERSLIP UNIT")
    {
        if(mXMotor)
        {
	        mJoyStick->getX1Axis().setup(mXMotor, mXMotor->getJogVelocity(), mXMotor->getJogAcceleration());
            mJoyStick->getX1Axis().enable();
        }
        else
        {
            mJoyStick->getX1Axis().disable();
        }

        if(mYMotor)
        {
            mJoyStick->getY1Axis().setup(mYMotor, mYMotor->getJogVelocity(), mYMotor->getJogAcceleration());
            mJoyStick->getY1Axis().enable();
        }
        else
        {
            mJoyStick->getY1Axis().disable();
        }

        if(mZMotor)
        {
            mJoyStick->getPOVButton(2).assignMotor(mZMotor);
            mJoyStick->getPOVButton(4).assignMotor(mZMotor);

            mJoyStick->getPOVButton(2).setReverse();
            mJoyStick->getPOVButton(4).setForward();

            mJoyStick->getPOVButton(2).enable();
            mJoyStick->getPOVButton(4).enable();
        }
        else
        {
            mJoyStick->getPOVButton(2).disable();
            mJoyStick->getPOVButton(4).disable();
        }

        if(mAngleMotor)
        {
            mJoyStick->getPOVButton(1).assignMotor(mAngleMotor);
            mJoyStick->getPOVButton(3).assignMotor(mAngleMotor);

            mJoyStick->getPOVButton(1).setReverse();
            mJoyStick->getPOVButton(3).setForward();

            mJoyStick->getPOVButton(1).enable();
            mJoyStick->getPOVButton(3).enable();
        }
        else
        {
            mJoyStick->getPOVButton(1).disable();
            mJoyStick->getPOVButton(3).disable();
        }

    }
    else if(mName == "WHISKER UNIT")
    {
        if(mXMotor)
        {
            mJoyStick->getX2Axis().setup(mXMotor, mXMotor->getJogVelocity(), mXMotor->getJogAcceleration());
            mJoyStick->getX2Axis().enable();
        }
        else
        {
            mJoyStick->getX2Axis().disable();
        }

        if(mYMotor)
        {
            mJoyStick->getY2Axis().setup(mYMotor, mYMotor->getJogVelocity(), mYMotor->getJogAcceleration());
            mJoyStick->getY2Axis().enable();
        }
        else
        {
            mJoyStick->getY2Axis().disable();
        }

        if(mZMotor)
        {
            mJoyStick->getButton(2).assignMotor(mZMotor);
            mJoyStick->getButton(4).assignMotor(mZMotor);

            mJoyStick->getButton(2).setReverse();
            mJoyStick->getButton(4).setForward();

            mJoyStick->getButton(2).enable();
            mJoyStick->getButton(4).enable();
        }
        else
        {
            mJoyStick->getButton(2).disable();
            mJoyStick->getButton(4).disable();
        }

        if(mAngleMotor)
        {
            mJoyStick->getButton(1).assignMotor(mAngleMotor);
            mJoyStick->getButton(3).assignMotor(mAngleMotor);

            mJoyStick->getButton(1).setReverse();
            mJoyStick->getButton(3).setForward();

            mJoyStick->getButton(1).enable();
            mJoyStick->getButton(3).enable();
        }
        else
        {
            mJoyStick->getButton(1).disable();
            mJoyStick->getButton(3).disable();
        }
    }
}

void XYZUnit::detachJoyStick()
{
	mJoyStick = NULL;
}

APTMotor* XYZUnit::getMotorWithName(const string& name)
{
	if(getXMotor() && getXMotor()->getName() == name)
    {
    	return getXMotor();
    }

	if(getYMotor() && getYMotor()->getName() == name)
    {
    	return getYMotor();
    }

	if(getZMotor() && getZMotor()->getName() == name)
    {
    	return getZMotor();
    }

	if(getAngleMotor() && getAngleMotor()->getName() == name)
    {
    	return getAngleMotor();
    }

    return NULL;
}

APTMotor* XYZUnit::getMotorWithSerial(const string& serial)
{
	if(getXMotor() && getXMotor()->getSerial() == serial)
    {
    	return getXMotor();
    }

	if(getYMotor() && getYMotor()->getSerial() == serial)
    {
    	return getYMotor();
    }

	if(getZMotor() && getZMotor()->getSerial() == serial)
    {
    	return getZMotor();
    }

	if(getAngleMotor() && getAngleMotor()->getSerial() == serial)
    {
    	return getAngleMotor();
    }

    return NULL;
}

APTMotor* XYZUnit::getXMotor() const
{
	return mXMotor;
}

APTMotor* XYZUnit::getYMotor() const
{
	return mYMotor;
}

APTMotor* XYZUnit::getZMotor() const
{
	return mZMotor;
}

APTMotor* XYZUnit::getAngleMotor() const
{
	return mAngleMotor;
}

bool XYZUnit::stopAll()
{
	if(mXMotor)
    {
    	mXMotor->stop();
    }

	if(mYMotor)
    {
    	mYMotor->stop();
    }

	if(mZMotor)
    {
    	mZMotor->stop();
    }

    if(mAngleMotor)
    {
		mAngleMotor->stop();
    }
    return true;
}
