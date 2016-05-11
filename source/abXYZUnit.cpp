#pragma hdrstop
#include "abJoyStick.h"
#include "abXYZUnit.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"

//---------------------------------------------------------------------------
using namespace mtk;
XYZUnit::XYZUnit(const string& name, JoyStick* js, IniFile& iniFile)
:
mXMotorSerialNr(-1),
mYMotorSerialNr(-1),
mZMotorSerialNr(-1),
mName(name),
mXMotor(NULL),
mYMotor(NULL),
mZMotor(NULL),
mJoyStick(js),
mIniFile(iniFile)
{
	//Setup properties
    mProperties.setSection(name);
    mProperties.add((BaseProperty*) &mXMotorSerialNr.setup("XMotorSerial", -1, true));
    mProperties.add((BaseProperty*) &mYMotorSerialNr.setup("YMotorSerial", -1, true));
    mProperties.add((BaseProperty*) &mZMotorSerialNr.setup("ZMotorSerial", -1, true));

	//Load Properties
    mIniFile.load();
    mProperties.setIniFile(&mIniFile);
    mProperties.read();

    //Check for positions
}

XYZUnit::~XYZUnit()
{
	//Save positions

    mIniFile.save();
}

void XYZUnit::shutDown()
{
	mDeviceManager.disConnectAll();

	//Save Properties
	mProperties.write();
    mIniFile.save();
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
	mDeviceManager.reBuildDeviceList();
	//Setup all the motors
    mXMotor = dynamic_cast<APTMotor*>(mDeviceManager.connectDevice(mXMotorSerialNr));
    if(mXMotor)
    {
    	Log(lInfo) << "X motor is connected";

        //Load Motor Properties
        mXMotor->loadProperties(mIniFile);

        mXMotor->setName(mName + ":X");
        if(mJoyStick)
        {
        	mJoyStick->getXAxis().assignMotor(mXMotor);
			mJoyStick->getXAxis().setMaxVelocity(mXMotor->getJogVelocity());
			mJoyStick->getXAxis().setAcceleration(mXMotor->getJogAcceleration());
        }
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

        if(mJoyStick)
        {
        	mJoyStick->getYAxis().assignMotor(mYMotor);
			mJoyStick->getYAxis().setMaxVelocity(mYMotor->getJogVelocity());
			mJoyStick->getYAxis().setAcceleration(mYMotor->getJogAcceleration());
        }
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

        if(mJoyStick)
        {
   			mJoyStick->getButton(3).assignMotor(mZMotor);
			mJoyStick->getButton(4).assignMotor(mZMotor);

            mJoyStick->getButton(3).setForward();
            mJoyStick->getButton(4).setReverse();
        }
    }
    else
    {
		Log(lError) << "Z motor is NOT connected";
    }
	return true;
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
