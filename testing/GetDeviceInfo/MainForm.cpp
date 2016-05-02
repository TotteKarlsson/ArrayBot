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
mMotorMessageProcessor(mMotorMessageContainer)
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
        joyTimer->Enabled = true;
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
//    APTMotor* motor = dynamic_cast<APTMotor*>(getCurrentDevice());
//    if(motor)
//    {
//    	motor->stop();
//    }

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


void __fastcall TMain::joyTimerTimer(TObject *Sender)
{
	//read trackbar
    APTMotor* motor = getCurrentMotor();
    if(motor == NULL)
    {
    	Log(lInfo) << "Motor object is null..";
    	return;
    }

	double vel = TrackBar1->Position/50.0;

    if(mLastVel == vel)
    {
    	return ;
    }



    if( fabs(vel) <= 0.1)
    {
    	stopMotorExecute(Sender);
//		//    	motor->stop();
//        Log(lInfo) << "Stopping motor";
        return;
    }

    if (vel > 0.5)
    {
    	MotorCommand cmd(mcSetVelocity,  vel);
		mMotorMessageContainer.post(cmd);
		moveForwardExecute(Sender);
        Log(lInfo) << "Setting forward velocity: "<<vel;
    }
    else
    {
    	MotorCommand cmd(mcSetVelocity,  fabs(vel));
		mMotorMessageContainer.post(cmd);
		moveBackwardExecute(Sender);
        Log(lInfo) << "Setting reverse velocity: "<<fabs(vel);
    }
	mLastVel = vel;
}

//---------------------------------------------------------------------------
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

//---------------------------------------------------------------------------

