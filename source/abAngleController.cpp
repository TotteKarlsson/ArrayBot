#pragma hdrstop
#include "abAngleController.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"
//---------------------------------------------------------------------------
using namespace mtk;

AngleController::AngleController(const string& name, IniFile& iniFile)
:
mMotorSerial(-1),
mName(name),
mAngle(0),
mAngleOffset(0),
mIniFile(iniFile),
mAngleMotor(NULL)
{
    mProperties.setSection(name);
    mProperties.add((BaseProperty*) &mMotorSerial.setup("MOTOR_SERIAL", -1, true));
    mProperties.add((BaseProperty*) &mAngle.setup("ANGLE", 1, true));
    mProperties.add((BaseProperty*) &mAngleOffset.setup("ANGLE_OFFSET", 1, true));
    mProperties.setIniFile(&mIniFile);
}

AngleController::~AngleController()
{}

double AngleController::getAngle()
{
	if(mAngleMotor)
    {
		mAngle = mAngleMotor->getPosition();
    }
	return mAngle - mAngleOffset;
}

void AngleController::setAngle(double a)
{
    mAngle = a;
    if(mAngleMotor)
    {
        mAngleMotor->moveAbsolute(a + mAngleOffset);
    }
}

bool AngleController::isActive()
{
	return (mAngleMotor) ? mAngleMotor->isActive() : false;
}

APTMotor* AngleController::getMotor()
{
	return mAngleMotor;
}

void AngleController::stop()
{
	if(mAngleMotor)
    {
	    mAngleMotor->stop();
    }
}

bool AngleController::initialize()
{
	mDeviceManager.reBuildDeviceList();
    mProperties.read();

    Log(lInfo) << "Initializing: "<< mName;
	//Setup the motor
    mAngleMotor = dynamic_cast<APTMotor*>(mDeviceManager.connectDevice(mMotorSerial));
    if(mAngleMotor)
    {
    	Log(lInfo)<<"Motor to control "<<mName<<" is connected";

        //Load Motor Properties
        mAngleMotor->loadProperties(mIniFile);
        mAngleMotor->setName(mName + "_MOTOR");
    }
    else
    {
		Log(lError) <<"Motor to control "<<mName<<" is not connected";
    }

	return true;
}

void AngleController::shutDown()
{
	mDeviceManager.disConnectAll();

    //Now motors are NULL.. make them smart pointers
    mAngleMotor = NULL;

	//Save Properties
	mProperties.write();
}

string AngleController::getName() const
{
	return mName;
}


