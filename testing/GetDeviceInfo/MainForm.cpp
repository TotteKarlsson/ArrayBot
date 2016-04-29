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
mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", gLogFileName), logMsgMethod)
{
	TMemoLogger::mMemoIsEnabled = false;
}

//This one is called from the reader thread
void __fastcall TMain::logMsg()
{
    infoMemo->Lines->Add(vclstr(mLogFileReader.getData()));
    mLogFileReader.purge();
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
    	Close();
    }
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
}

//---------------------------------------------------------------------------
void __fastcall TMain::ShutDownTimerTimer(TObject *Sender)
{
	ShutDownTimer->Enabled = false;
	if(mLogFileReader.isRunning())
	{
		Log(lDebug) << "Shutting down log file reader";
		mLogFileReader.stop();
	}
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	Log(lInfo) << "Closing down....";

	//Check if we can close.. abort all threads..
	CanClose = (mLogFileReader.isRunning()) ? false : true;

	if(CanClose == false)
	{
		ShutDownTimer->Enabled = true;
	}
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	Log(lInfo) << "In FormClose";
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
	//Use whatever speed is selected
    APTMotor* motor = dynamic_cast<APTMotor*>(getCurrentDevice());
    if(motor)
    {
    	motor->forward();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::moveBackwardExecute(TObject *Sender)
{
	//Use whatever speed is selected
    APTMotor* motor = dynamic_cast<APTMotor*>(getCurrentDevice());
    if(motor)
    {
    	motor->reverse();
    }
}

void __fastcall TMain::stopMotorExecute(TObject *Sender)
{
    APTMotor* motor = dynamic_cast<APTMotor*>(getCurrentDevice());
    if(motor)
    {
    	motor->stop();
    }
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
	stopMotorExecute(Sender);
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

       	mIsActiveLabel->Caption = (motor->isActive()) 	? "Active" : "Idle";
        mIsHomingLabel->Caption = (motor->isHoming()) 	? "Is homing" : "Not Homing";
        mIsHomedLabel->Caption  = (motor->isHomed()) 	? "Is homed" : "Not Homed";
    }
}

void __fastcall	TMain::OnException()
{
	Log(lInfo) << "Exception TMain::OnException()";
}

//---------------------------------------------------------------------------
void __fastcall TMain::ApplicationEvents1Exception(TObject *Sender, Exception *E)
{
	Log(lInfo) << "Application Exception...."<<stdstr(E->Message);
}


void __fastcall TMain::BitBtn3Click(TObject *Sender)
{
	infoMemo->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TMain::Button5Click(TObject *Sender)
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
        Log(lInfo) << motor->getEncoderCounts();
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
//                if(motor->isForwarding())
//                {
//                	motor->forward();
//                }
//                else if (motor->isReversing())
//                {
//                	motor->reverse();
//                }
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

void __fastcall TMain::TrackBar1Change(TObject *Sender)
{
	Log(lInfo) <<"Applying new velocity:" <<TrackBar1->Position/2.0;

	double vel = TrackBar1->Position/2.0;
    APTMotor* motor = getCurrentMotor();
    if(motor == NULL)
    {
    	Log(lInfo) << "Motor object is null..";
    	return;
    }

    if(-0.1 >= vel <= 0.1 )
    {
    	motor->stop();
        Log(lInfo) << "Stopping motor";
    }

    if (vel > 0.1)
    {
        motor->forward();
    	motor->setMaxVelocity(vel);
        Log(lInfo) << "Setting forward velocity: "<<vel;
    }

    if (vel < -0.1)
    {
        motor->reverse();
    	motor->setMaxVelocity(fabs(vel));
        Log(lInfo) << "Setting reverse velocity: "<<vel;
    }
}


