#pragma hdrstop
//#include <mmsystem.h>
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
mName("<none>"),
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
    mProperties.add((BaseProperty*) &mName.setup("XYZUnit Name", 			"<none>", true));
	//Load Properties
    mIniFile.load();
    mProperties.setIniFile(&mIniFile);
    mProperties.read();
}

XYZUnit::~XYZUnit()
{
	//Save Properties
	mProperties.write();
    mIniFile.save();
}


bool XYZUnit::initialize()
{
	mDeviceManager.reBuildDeviceList();
	//Setup all the motors
    mXMotor = dynamic_cast<APTMotor*>(mDeviceManager.connectDevice(mXMotorSerialNr));
    if(mXMotor)
    {
    	Log(lInfo) << "Xmotor is connected";
        //Load Motor Properties
        if(mJoyStick)
        {
        	mJoyStick->getXAxis().assignMotor(mXMotor);
			mJoyStick->getXAxis().setMaxVelocity(mXMotor->getJogVelocity());
			mJoyStick->getXAxis().setAcceleration(mXMotor->getJogAcceleration());
            mJoyStick->getXAxis().setSenseOfDirection(-1);
        }
    }
    else
    {
		Log(lError) << "Xmotor is NOT connected";
    }

    mYMotor = dynamic_cast<APTMotor*>(mDeviceManager.connectDevice(mYMotorSerialNr));
    if(mYMotor)
    {
    	Log(lInfo) << "Ymotor is connected";
        if(mJoyStick)
        {
        	mJoyStick->getYAxis().assignMotor(mYMotor);
			mJoyStick->getYAxis().setMaxVelocity(mYMotor->getJogVelocity());
			mJoyStick->getYAxis().setAcceleration(mYMotor->getJogAcceleration());
        }
    }
    else
    {
		Log(lError) << "Ymotor is NOT connected";
    }

    mZMotor = dynamic_cast<APTMotor*>(mDeviceManager.connectDevice(mZMotorSerialNr));
    if(mZMotor)
    {
    	Log(lInfo) << "Zmotor is connected";
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
		Log(lError) << "Zmotor is NOT connected";
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
}
