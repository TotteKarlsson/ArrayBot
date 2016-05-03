#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "abTLWrapper.h"
#include "TMemoLogger.h"
#include "mtkStringList.h"
#include "abUtilities.h"
#include "abAPTMotor.h"
#include "abTCubeDCServo.h"
#include "mtkVCLUtils.h"
#include "mtkLogger.h"
#include <bitset>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntegerLabeledEdit"
#pragma link "mtkFloatLabeledEdit"
#pragma resource "*.dfm"
TMain *Main;

extern string       gLogFileLocation;
extern string       gLogFileName;

using namespace mtk;
//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
:
	TForm(Owner),
	logMsgMethod(&logMsg),
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", gLogFileName), logMsgMethod),
	mMotorMessageProcessor(mMotorMessageContainer),
	mRunningZAverage(0),
	mAlpha(0.1)

{
	TMemoLogger::mMemoIsEnabled = false;
}

//---------------------------------------------------------------------------
void __fastcall TMain::checkForDevicesExecute(TObject *Sender)
{
	if(!buildDeviceList())
    {
    	Log(lError) <<"Failed building device list";
        return;
    }

    for(int i = 0; i < 90; i++)
    {
		StringList serials = getSerialsForDeviceType(i);
        for(int j = 0; j < serials.count(); j++)
        {
            Log(lInfo) <<"Found device of type '"<<::toString((DeviceTypeID) i)<<"' with serial: " <<serials[j];
        }
    }
}

void __fastcall TMain::connectAllDevicesExecute(TObject *Sender)
{
	//Connect all available devices
    mDeviceManager.connectAllDevices();

  	APTDevice* device = mDeviceManager.getFirst();
	while(device)
    {
		string serial = device->getSerial();

        //Add to listbox
        devicesLB->Items->AddObject(serial.c_str(), (TObject*) device);
        device = mDeviceManager.getNext();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject *Sender)
{
	TMemoLogger::mMemoIsEnabled = true;
	mLogFileReader.start(true);

    connectAllDevicesExecute(Sender);
	mMotorMessageProcessor.start(true);


    mJoyStickConnected = false;
    MMRESULT  JoyResult;
    JOYINFO JoyInfo;

    // the joystick could be disconnected even if the driver is
    // loaded. use joyGetPos to detect if a joystick is connected
    // it returns JOYERR_NOERROR if the joystick is plugged in
	// find out how many joysticks the driver supports
  	mJoyStickDriverCount = joyGetNumDevs();

  	if(mJoyStickDriverCount == 0)    // can any joysticks be supported
  	{
		return;
  	}
    // test for joystick1
    JoyResult = joyGetPos(JOYSTICKID1,&JoyInfo);
    if(JoyResult != JOYERR_UNPLUGGED)
    {
      mJoyStickConnected = true;
      mJoystickID = JOYSTICKID1;
    }
    else if(JoyResult == MMSYSERR_INVALPARAM)
    {
    	// INVALIDPARAM means something is bad. quit now without
	    // checking for joystick 2
      	Application->MessageBox(L"An error occured while calling joyGetPosEx", L"Error", MB_OK);
    }
    else if((JoyResult=joyGetPos(JOYSTICKID2,&JoyInfo)) == JOYERR_NOERROR)
    {
      // if joystick1 is unconnected, check for joystick2
      mJoyStickConnected = true;
      mJoystickID = JOYSTICKID2;
    }

//  ShowDeviceInfo(); // initialize the labels.
//  ShowStatusInfo();
    // use joyGetDevCaps to display information from JOYCAPS structure
    // note that not all of the information from joyGetDevCaps is shown
    // here. consult the win32 SDK help file for a full description of
    // joyGetDevCaps
    joyGetDevCaps(mJoystickID, &mJoyCaps, sizeof(JOYCAPS));

    // Tell Windows we want to receive joystick events.
    // Handle = receiver, JoystickID = joystick we're using
    // 3rd arg = how often MM_JOYMOVE events happen
	if(mJoyStickConnected)
  	{
    	joySetCapture(Handle, mJoystickID, 2*mJoyCaps.wPeriodMin,FALSE);
  	}

}


//---------------------------------------------------------------------------
void __fastcall TMain::devicesLBClick(TObject *Sender)
{
	//Query the device
    int ii = devicesLB->ItemIndex;
    if(ii == -1)
    {
    	return;
    }

    APTDevice* device = (APTDevice*) devicesLB->Items->Objects[ii];
    if(device)
    {
    	//Populate device frame
        device->identify();
        //Check position for current device
        APTMotor* motor = dynamic_cast<APTMotor*>(device);
        if(motor)
        {
        	double v = motor->getVelocity();
			mMaxVelocity->SetNumber(v);

        	double a = motor->getAcceleration();
			mAcceleration->SetNumber(a);

            mMotorMessageProcessor.assignMotor(motor);
        }

		StatusTimer->Enabled = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::identifyCurrentExecute(TObject *Sender)
{
	APTDevice* device = getCurrentDevice();
    if(device)
    {
    	device->identify();
    }
}

APTDevice* TMain::getCurrentDevice()
{
    int ii = devicesLB->ItemIndex;
    if(ii == -1)
    {
    	return NULL;
    }

    APTDevice* device = (APTDevice*) devicesLB->Items->Objects[ii];
	return device;
}

//---------------------------------------------------------------------------
void __fastcall TMain::homeDeviceExecute(TObject *Sender)
{
    APTMotor* motor = dynamic_cast<APTMotor*>(getCurrentDevice());
    if(motor)
    {
    	motor->home();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::jogForwardExecute(TObject *Sender)
{
    APTMotor* motor = dynamic_cast<APTMotor*>(getCurrentDevice());
    if(motor)
    {
    	motor->jogForward();
    }
}

void __fastcall TMain::jogBackwardsExecute(TObject *Sender)
{
    APTMotor* motor = dynamic_cast<APTMotor*>(getCurrentDevice());
    if(motor)
    {
    	motor->jogForward();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::moveForwardExecute(TObject *Sender)
{
//	//Use whatever speed is selected
//    APTMotor* motor = dynamic_cast<APTMotor*>(getCurrentDevice());
//    if(motor)
//    {
//    	motor->forward();
//    }
	MotorCommand cmd(mcForward);
	mMotorMessageContainer.post(cmd);
}

//---------------------------------------------------------------------------
void __fastcall TMain::moveBackwardExecute(TObject *Sender)
{
//	//Use whatever speed is selected
//    APTMotor* motor = dynamic_cast<APTMotor*>(getCurrentDevice());
//    if(motor)
//    {
//    	motor->reverse();
//    }
	MotorCommand cmd(mcReverse);
	mMotorMessageContainer.post(cmd);
}

void __fastcall TMain::stopMotorExecute(TObject *Sender)
{
	MotorCommand cmd(mcStopHard);
	mMotorMessageContainer.post(cmd);
}

void __fastcall TMain::driveBtnDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	TButton* btn = (TButton*) Sender;
    if(btn == fwdDriveBtn)
    {
		moveForwardExecute(Sender);
    }
    else if(btn == revDriveBtn)
    {
		moveBackwardExecute(Sender);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::driveBtnUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(!ContinousMoveCB->Checked)
    {
    	stopMotorExecute(Sender);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::StatusTimerTimer(TObject *Sender)
{
    int ii = devicesLB->ItemIndex;
    if(ii > -1)
    {
        APTDevice* device = (APTDevice*) devicesLB->Items->Objects[ii];

        //Check position for current device
        APTMotor* motor = dynamic_cast<APTMotor*>(device);
        if(!motor)
        {
        	return;
        }

		double p = motor->getPosition();
        double v = motor->getVelocity();
        double a = motor->getAcceleration();

        motorPositionE->SetNumber(p);

       	mIsActiveLabel->Caption 	= (motor->isActive()) 	    ? "True" : "False";
        mIsHomingLabel->Caption 	= (motor->isHoming()) 	    ? "True" : "False";
        mIsHomedLabel->Caption  	= (motor->isHomed()) 	    ? "True" : "False";
        mIsForwardingLabel->Caption = (motor->isForwarding()) 	? "True" : "False";
        mIsReversingLabel->Caption  = (motor->isReversing()) 	? "True" : "False";

		if(motor->isActive())
        {
			mVelocityLbl->Caption = FloatToStrF(v,ffFixed, 4,3);
        }
        else
        {
			mVelocityLbl->Caption = FloatToStrF(0,ffFixed, 4,3);
        }
    }
}

APTMotor* TMain::getCurrentMotor()
{
    int ii = devicesLB->ItemIndex;
    if(ii > -1)
    {
        APTDevice* device = (APTDevice*) devicesLB->Items->Objects[ii];

        //Check position for current device
        return dynamic_cast<APTMotor*>(device);
    }
    return NULL;
}

//---------------------------------------------------------------------------
void __fastcall TMain::mMaxVelocityKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	mtkFloatLabeledEdit* e = dynamic_cast<mtkFloatLabeledEdit*>(Sender);
	if(Key == vkReturn)
    {
        APTMotor* motor = getCurrentMotor();
    	if(e == mMaxVelocity)
        {
            double vel = mMaxVelocity->GetValue();
            Log(lInfo) << "New velocity: " <<vel;

            if(motor)
            {
                motor->setMaxVelocity(vel);
            }
        }
       	if(e == mAcceleration)
        {
            double a = mAcceleration->GetValue();
            Log(lInfo) << "New acceleration: " <<a;

            if(motor)
            {
                motor->setAcceleration(a);
            }
        }
    }
}

void __fastcall TMain::Button5Click(TObject *Sender)
{
	MotorCommand cmd(mcStopProfiled);
	mMotorMessageContainer.post(cmd);
}


void __fastcall TMain::IncreaseVelBtnClick(TObject *Sender)
{
	//Increase velocity
	double delta = 	mVelDeltaE->GetNumber();

    APTMotor* motor = getCurrentMotor();
    if(motor == NULL)
    {
    	Log(lInfo) << "Motor object is null..";
    	return;
    }
	double cVel = motor->getVelocity();
	MotorCommand cmd(mcSetVelocity,  cVel + delta);
	mMotorMessageContainer.post(cmd);
}

void __fastcall TMain::DecreaseVelBtnClick(TObject *Sender)
{
	//Increase velocity
	double delta = 	mVelDeltaE->GetNumber();

    APTMotor* motor = getCurrentMotor();
    if(motor == NULL)
    {
    	Log(lInfo) << "Motor object is null..";
    	return;
    }
	double cVel = motor->getVelocity();
	MotorCommand cmd(mcSetVelocity,  cVel - delta);
	mMotorMessageContainer.post(cmd);
}

//---------------------------------------------------------------------------
void __fastcall TMain::switchdirectionBtnClick(TObject *Sender)
{
	MotorCommand cmd(mcSwitchDirection);
	mMotorMessageContainer.post(cmd);
}

bool sameSign(double x, double y)
{
	return x*y >= 0.0f;
}
//---------------------------------------------------------------------------
void __fastcall TMain::JMXMove(TMessage &msg)
{
	double fullVelRange = 10.0;
	double scalingFactor = fullVelRange/ 65535.0;
	double pos = (msg.LParamLo * scalingFactor - fullVelRange/2) * 2.0;

	double step = fullVelRange / 4.0;
    mRunningZAverage = (mAlpha * pos) + (1.0 - mAlpha) * mRunningZAverage;
    JoystickZPosition->Caption = "X Position = " + FloatToStrF(pos, ffFixed, 4,2);
    JoystickAvgZPos->Caption = "X Average Position = " + FloatToStrF(mRunningZAverage, ffFixed, 4,2);

	//Check if joystick value have changed more than previous command
	double vel = mRunningZAverage;
    if(fabs(vel - mValCommand) > step)
    {
    	stringstream msg;
        msg<<"New value: "<<vel;
        msg<<"Old value: "<<mValCommand;

        Log(lInfo) << msg.str();

        //Did we switch direction?
        if(!sameSign(vel,mValCommand))
        {
			MotorCommand cmd(mcSwitchDirection);
        }

        mValCommand = vel;
        if( fabs(mValCommand) <= step)
        {
            MotorCommand cmd(mcStopHard,  vel);
            mMotorMessageContainer.post(cmd);
            Log(lInfo) << "Motor is stopping. ";
            return;
        }

        if (vel > step)
        {
            MotorCommand cmd(mcSetVelocityForward,  vel);
            mMotorMessageContainer.post(cmd);
            Log(lInfo) << "Setting forward velocity: "<<vel;
        }
        else
        {
            MotorCommand cmd(mcSetVelocityReverse,  fabs(vel));
            mMotorMessageContainer.post(cmd);
            Log(lInfo) << "Setting reverse velocity: "<<fabs(vel);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormDestroy(TObject *Sender)
{
	if(mJoyStickConnected)
    {
  		joyReleaseCapture(mJoystickID);
    }
}



