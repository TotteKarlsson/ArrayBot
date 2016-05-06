#pragma hdrstop
//#include <mmsystem.h>
#include "abJoyStick.h"
#include "abXYZUnit.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"

//---------------------------------------------------------------------------

using namespace mtk;
XYZUnit::XYZUnit(JoyStick* js)
:
mJoyStick(js),
mXMotor(NULL),
mYMotor(NULL),
mZMotor(NULL),
mXMotorSerialNr(-1),
mYMotorSerialNr(-1),
mZMotorSerialNr(-1),
mIniFile("ArrayBotProps.ini")
{
	//Setup properties
    mProperties.setSection("CoverSlip Properties");
    mProperties.add((BaseProperty*) &mXMotorSerialNr.setup("XMotorSerial", -1, true));
    mProperties.add((BaseProperty*) &mYMotorSerialNr.setup("YMotorSerial", -1, true));
    mProperties.add((BaseProperty*) &mZMotorSerialNr.setup("ZMotorSerial", -1, true));

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
        if(mJoyStick)
        {
        	mJoyStick->getXAxis().assignMotor(mXMotor);
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
