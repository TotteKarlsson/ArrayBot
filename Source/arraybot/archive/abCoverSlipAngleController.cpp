#pragma hdrstop
#include "atAngleController.h"
#include "dslLogger.h"
#include "atAPTMotor.h"
//---------------------------------------------------------------------------
using namespace dsl;

AngleController::AngleController(const string& name, IniFile& iniFile)
:
mMotorSerial(-1),
mName(name),
mAngle(0),
mIniFile(iniFile),
mAngleMotor(NULL),
mAngleOffset(225)
{
    mProperties.setSection(name);
    mProperties.add((BaseProperty*) &mMotorSerial.setup("CoverSlipAngleMotorSerial", -1, true));
    mProperties.add((BaseProperty*) &mAngle.setup("Angle", 1, true));
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
    	Log(lInfo)<<"CoverSlip Angle control  motor is connected";

        //Load Motor Properties
        mAngleMotor->loadProperties(mIniFile);
        mAngleMotor->setName("CoverSlipAngleMotor");
    }
    else
    {
		Log(lError) << "The CoverSlip Angle control motor is NOT connected";
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


