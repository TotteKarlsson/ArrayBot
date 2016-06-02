#pragma hdrstop
#include "abJoyStick.h"
#include "abXYZUnit.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"

//---------------------------------------------------------------------------
using namespace mtk;
XYZUnit::XYZUnit(const string& name, IniFile& iniFile)
:
mXMotorSerialNr(-1),
mYMotorSerialNr(-1),
mZMotorSerialNr(-1),
mName(name),
mXMotor(NULL),
mYMotor(NULL),
mZMotor(NULL),
mJoyStick(NULL),
mIniFile(iniFile)
{
	//Setup properties
    mProperties.setSection(name);
    mProperties.add((BaseProperty*) &mXMotorSerialNr.setup("XMotorSerial", -1, true));
    mProperties.add((BaseProperty*) &mYMotorSerialNr.setup("YMotorSerial", -1, true));
    mProperties.add((BaseProperty*) &mZMotorSerialNr.setup("ZMotorSerial", -1, true));

	//assign inifile to use with the properties
    mProperties.setIniFile(&mIniFile);
}

XYZUnit::~XYZUnit()
{}

bool XYZUnit::isActive()
{
	bool xa(false), ya(false), za(false);

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

    return xa || ya || za;
}

bool XYZUnit::initialize()
{
    mProperties.read();
	mDeviceManager.reBuildDeviceList();
    Log(lInfo) << "Initializing: "<< mName;

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
	return true;
}

void XYZUnit::shutDown()
{
	mDeviceManager.disConnectAll();

    //Now motors are NULL.. make them smart pointers
    mXMotor = mYMotor = mZMotor = NULL;

	//Save Properties
	mProperties.write();
}

void XYZUnit::stow()
{}

string XYZUnit::getName()
{
	return mName;
}

bool XYZUnit::moveAbsolute(const ab::Position& pos)
{
	if(mXMotor && mYMotor && mZMotor)
    {
        //Check pos validity..
        mXMotor->moveAbsolute(pos.x());
        mYMotor->moveAbsolute(pos.y());
        mZMotor->moveAbsolute(pos.z());
        return true;
    }

    return false;
}

bool XYZUnit::moveRelative(const ab::Position& pos)
{
	if(mXMotor)
    {
    	mXMotor->moveRelative(pos.x());
    }

	if(mYMotor)
    {
    	mYMotor->moveRelative(pos.y());
    }

   	if(mZMotor)
    {
    	mZMotor->moveRelative(pos.z());
    }
    return true;
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

    if(mZMotor && mYMotor)
    {
        while(mZMotor->isHoming() || mYMotor->isHoming())
        {
            sleep(100);
            Log(lInfo) << "Homing...";
        }
    }
}

void XYZUnit::enableJoyStick(JoyStick* js)
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
            mJoyStick->getX1Axis().assignMotor(mXMotor);
            mJoyStick->getX1Axis().setMaxVelocity(mXMotor->getJogVelocity());
            mJoyStick->getX1Axis().setAcceleration(mXMotor->getJogAcceleration());
            mJoyStick->getX1Axis().enable();
        }
        else
        {
            mJoyStick->getX1Axis().disable();
        }

        if(mYMotor)
        {
            mJoyStick->getY1Axis().assignMotor(mYMotor);
            mJoyStick->getY1Axis().setMaxVelocity(mYMotor->getJogVelocity());
            mJoyStick->getY1Axis().setAcceleration(mYMotor->getJogAcceleration());
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
    }
    else if(mName == "WHISKER UNIT")
    {
        if(mXMotor)
        {
            mJoyStick->getX2Axis().assignMotor(mXMotor);
            mJoyStick->getX2Axis().setMaxVelocity(mXMotor->getJogVelocity());
            mJoyStick->getX2Axis().setAcceleration(mXMotor->getJogAcceleration());
            mJoyStick->getX2Axis().enable();
        }
        else
        {
            mJoyStick->getX2Axis().disable();
        }

        if(mYMotor)
        {
            mJoyStick->getY2Axis().assignMotor(mYMotor);
            mJoyStick->getY2Axis().setMaxVelocity(mYMotor->getJogVelocity());
            mJoyStick->getY2Axis().setAcceleration(mYMotor->getJogAcceleration());
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
    }

    mJoyStick->enable();
}

void XYZUnit::disableJoyStick()
{
	if(mJoyStick)
    {
		mJoyStick->disable();
    }
}

APTMotor* XYZUnit::getXMotor()
{
	return mXMotor;
}

APTMotor* XYZUnit::getYMotor()
{
	return mYMotor;
}

APTMotor* XYZUnit::getZMotor()
{
	return mZMotor;
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
    return true;
}
