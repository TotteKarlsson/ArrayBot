#pragma hdrstop
#include "abWhiskerUnit.h"
#include "mtkProperties.h"
#include "abArrayBotJoyStick.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"
//---------------------------------------------------------------------------

using namespace mtk;
WhiskerUnit::WhiskerUnit(IniFile& iniFile, const string& appDataFolder)
:
XYZUnit("WHISKER UNIT", iniFile, appDataFolder),
mZ2MotorSerialNr(-1),
mZ2Motor(NULL)
{
    mProperties.add((BaseProperty*) &mZ2MotorSerialNr.setup("Z2MotorSerial", -1, true));
}


bool WhiskerUnit::initialize()
{
	XYZUnit::initialize();

    mZ2Motor = dynamic_cast<APTMotor*>(mDeviceManager.connectDevice(mZ2MotorSerialNr));
    if(mZ2Motor)
    {
    	Log(lInfo) << "Z2 motor is connected";

        //Load Motor Properties
        mZ2Motor->loadProperties(mIniFile);
        mZ2Motor->setName(mName + "_Z2");
    }
    else
    {
		Log(lError) << "Z2 motor is NOT connected";
    }

	return true;
}

vector<APTMotor*> WhiskerUnit::getAllMotors()
{
	vector<APTMotor*> ms = XYZUnit::getAllMotors();
	if(mZ2Motor)
    {
        ms.push_back(mZ2Motor);
    }

	return ms;
}

bool WhiskerUnit::stopAll()
{
   	if(mZ2Motor)
    {
    	mZ2Motor->stop();
    }
	return XYZUnit::stopAll();
}

void WhiskerUnit::attachJoyStick(ArrayBotJoyStick* js)
{
	if(!js)
    {
    	return;
    }

    mJoyStick = js;

    if(mName == "WHISKER UNIT")
    {
    	XYZUnit::attachJoyStick(js);
        if(mZ2Motor)
        {
            mJoyStick->getButton(7).assignMotor(mZ2Motor);
            mJoyStick->getButton(8).assignMotor(mZ2Motor);

            mJoyStick->getButton(7).setReverse();
            mJoyStick->getButton(8).setForward();

            mJoyStick->getButton(7).enable();
            mJoyStick->getButton(8).enable();
        }
        else
        {
            mJoyStick->getButton(7).disable();
            mJoyStick->getButton(8).disable();
        }
    }
}

