#pragma hdrstop
#include "abCoverSlipAngleController.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"
//---------------------------------------------------------------------------
using namespace mtk;

CoverSlipAngleController::CoverSlipAngleController(const string& name, IniFile& iniFile)
:
mMotorSerial(-1),
mName(name),
mIniFile(iniFile)
{
    mProperties.setSection(name);
    mProperties.add((BaseProperty*) &mMotorSerial.setup("CoverSlipAngleMotorSerial", -1, true));
    mProperties.setIniFile(&mIniFile);
}

CoverSlipAngleController::~CoverSlipAngleController()
{}

bool CoverSlipAngleController::initialize()
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
    }
    else
    {
		Log(lError) << "The CoverSlip Angle control motor is NOT connected";
    }

	return true;
}

void CoverSlipAngleController::shutDown()
{
	mDeviceManager.disConnectAll();

	//Save Properties
	mProperties.write();
}

string CoverSlipAngleController::getName() const
{
	return mName;
}

void CoverSlipAngleController::setAngle(double a)
{

}

