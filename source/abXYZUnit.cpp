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

	//Load Properties
    mProperties.setIniFile(&mIniFile);

}

XYZUnit::~XYZUnit()
{}

void XYZUnit::shutDown()
{
	mDeviceManager.disConnectAll();

	//Save Properties
	mProperties.write();
}

string XYZUnit::getName()
{
	return mName;
}

bool XYZUnit::moveToPosition(const XYZUnitPosition& pos)
{
	if(mXMotor && mYMotor && mZMotor)
    {
        //Check pos validity..
        mXMotor->moveToPosition(pos.x());
        mYMotor->moveToPosition(pos.y());
        mZMotor->moveToPosition(pos.z());
        return true;
    }

    return false;
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
        mXMotor->setName(mName + ":X");
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
        mYMotor->setName(mName + ":Y");
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
        mZMotor->setName(mName + ":Z");
    }
    else
    {
		Log(lError) << "Z motor is NOT connected";
    }
	return true;
}

void XYZUnit::enableJoyStick(JoyStick* js)
{
	if(!js)
    {
    	return;
    }

    mJoyStick = js;

    if(mXMotor)
    {
        mJoyStick->getXAxis().assignMotor(mXMotor);
        mJoyStick->getXAxis().setMaxVelocity(mXMotor->getJogVelocity());
        mJoyStick->getXAxis().setAcceleration(mXMotor->getJogAcceleration());
        mJoyStick->getXAxis().enable();
    }
    else
    {
    	mJoyStick->getXAxis().disable();
    }


    if(mYMotor)
    {
        mJoyStick->getYAxis().assignMotor(mYMotor);
        mJoyStick->getYAxis().setMaxVelocity(mYMotor->getJogVelocity());
        mJoyStick->getYAxis().setAcceleration(mYMotor->getJogAcceleration());
        mJoyStick->getYAxis().enable();
    }
    else
    {
    	mJoyStick->getYAxis().disable();
    }

    if(mZMotor)
    {
        mJoyStick->getButton(3).assignMotor(mZMotor);
        mJoyStick->getButton(4).assignMotor(mZMotor);
        mJoyStick->getButton(3).setForward();
        mJoyStick->getButton(4).setReverse();
        mJoyStick->getButton(3).enable();
        mJoyStick->getButton(4).enable();
    }
    else
    {
        mJoyStick->getButton(3).disable();
        mJoyStick->getButton(4).disable();
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
