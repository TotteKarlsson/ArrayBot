#pragma hdrstop
#include "abAngleController.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"
#include "abJoyStick.h"
//---------------------------------------------------------------------------
using namespace mtk;

AngleController::AngleController(const string& name, IniFile& iniFile)
:
mMotorSerial(-1),
mName(name),
mAngle(0),
mAngleOffset(0),
mIniFile(iniFile),
mMotor(NULL),
mJoyStick(NULL)
{
    mProperties.setSection(name);
    mProperties.add((BaseProperty*) &mMotorSerial.setup("MOTOR_SERIAL", -1, true));
    mProperties.add((BaseProperty*) &mAngle.setup("ANGLE", 1, true));
    mProperties.add((BaseProperty*) &mAngleOffset.setup("ANGLE_OFFSET", 1, true));
    mProperties.setIniFile(&mIniFile);
}

AngleController::~AngleController()
{}

void AngleController::enableJoyStick(JoyStick* js)
{
	if(!js)
    {
    	return;
    }

    mJoyStick = js;
	if(mName == "COVERSLIP ANGLE CONTROLLER")
    {
        if(mMotor)
        {
            mJoyStick->getPOVButton(1).assignMotor(mMotor);
            mJoyStick->getPOVButton(3).assignMotor(mMotor);

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
    else if(mName == "CAMERA ANGLE CONTROLLER")
    {
        if(mMotor)
        {
            mJoyStick->getButton(1).assignMotor(mMotor);
            mJoyStick->getButton(3).assignMotor(mMotor);

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

    mJoyStick->enable();
}

void AngleController::disableJoyStick()
{
	if(mJoyStick)
    {
		mJoyStick->disable();
    }
}

double AngleController::getAngle()
{
	if(mMotor)
    {
		mAngle = mMotor->getPosition();
    }
	return mAngle - mAngleOffset;
}

void AngleController::setAngle(double a)
{
    mAngle = a;
    if(mMotor)
    {
        mMotor->moveAbsolute(a + mAngleOffset);
    }
}

bool AngleController::isActive()
{
	return (mMotor) ? mMotor->isActive() : false;
}

APTMotor* AngleController::getMotor()
{
	return mMotor;
}

void AngleController::stop()
{
	if(mMotor)
    {
	    mMotor->stop();
    }
}

bool AngleController::initialize()
{
	mDeviceManager.reBuildDeviceList();
    mProperties.read();

    Log(lInfo) << "Initializing: "<< mName;
	//Setup the motor
    mMotor = dynamic_cast<APTMotor*>(mDeviceManager.connectDevice(mMotorSerial));
    if(mMotor)
    {
    	Log(lInfo)<<"Motor to control "<<mName<<" is connected";

        //Load Motor Properties
        mMotor->loadProperties(mIniFile);
        mMotor->setName(mName + "_MOTOR");
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
    mMotor = NULL;

	//Save Properties
	mProperties.write();
}

string AngleController::getName() const
{
	return mName;
}


