#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
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
#pragma link "TSTDStringLabeledEdit"
#pragma link "abXYZUnitFrame"
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
    mIniFile("ArrayBot.ini"),
    mJoyStick((int) Handle),
    mXYZUnit1("CoverSlip Unit", &mJoyStick, mIniFile),
    mXYZUnit2("Whisker Unit", &mJoyStick, mIniFile)

{
	TMemoLogger::mMemoIsEnabled = false;
}

__fastcall TMain::~TMain()
{

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

//---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject *Sender)
{
	TMemoLogger::mMemoIsEnabled = true;
	mLogFileReader.start(true);
}

void __fastcall TMain::InitializeUnitsAExecute(TObject *Sender)
{
	mXYZUnit1.initialize();
    addDevicesToListBoxExecute(Sender);

    //Fill out edits
    mMaxXYJogVelocityJoystick->SetNumber(mJoyStick.getXAxis().getMaxVelocity());
    mXYJogAccelerationJoystick->SetNumber(mJoyStick.getXAxis().getAcceleration());

    if(mXYZUnit1.getZMotor())
    {
    	mMaxZJogVelocityJoystick->SetNumber(mXYZUnit1.getZMotor()->getVelocity());
    	mZJogAccelerationJoystick->SetNumber(mXYZUnit1.getZMotor()->getAcceleration());
    }

	mNrOfGearsLbl->setValue(mJoyStick.getXAxis().getNumberOfGears());
	mJoyStick.connect();

	TXYZUnitFrame1->assignUnit(&mXYZUnit1);
    InitCloseBtn->Action = ShutDownA;
}

void __fastcall TMain::ShutDownAExecute(TObject *Sender)
{
	StatusTimer->Enabled = false;
	devicesLB->Clear();

    //The shutdown disconnects all devices
	mXYZUnit1.shutDown();
    InitCloseBtn->Action = InitializeUnitsA;
}

void __fastcall TMain::addDevicesToListBoxExecute(TObject *Sender)
{
	//Connect all available devices
  	APTDevice* device = mXYZUnit1.mDeviceManager.getFirst();
	while(device)
    {
		string serial = device->getSerial();

        //Add to listbox
        devicesLB->Items->AddObject(serial.c_str(), (TObject*) device);
        device = mXYZUnit1.mDeviceManager.getNext();
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
        //Check position for current device
        APTMotor* motor = dynamic_cast<APTMotor*>(device);
        if(motor)
        {
            double v = motor->getJogVelocity();
            mJogVelocity->SetNumber(v);

            double a = motor->getJogAcceleration();
            mJogAcc->SetNumber(a);

            JogMoveMode jm = motor->getJogMoveMode();
            mJogModeCB->Checked = (jm == jmContinuous) ? true : false;

            StopMode sm = motor->getJogStopMode();
            mJogStopModeCB->Checked = (sm == smProfiled) ? true : false;
        }

    	//Populate device frame
        device->identify();
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
    APTMotor* motor = getCurrentMotor();
    if(motor)
    {
    	motor->home();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::jogForwardExecute(TObject *Sender)
{
    APTMotor* motor = getCurrentMotor();
    if(motor)
    {
		Log(lDebug) << "Jog Forward executes";
    	motor->jogForward();
    }
}

void __fastcall TMain::jogBackwardsExecute(TObject *Sender)
{
    APTMotor* motor = getCurrentMotor();
    if(motor)
    {
		Log(lDebug) << "Jog Reverse Executes";
    	motor->jogReverse();
    }
}

void __fastcall TMain::stopMotorExecute(TObject *Sender)
{
	//Use whatever speed is selected
    APTMotor* motor = dynamic_cast<APTMotor*>(getCurrentDevice());
    if(motor)
    {
    	motor->stop();
    }

    mJoyStick.disable();
    mXYZUnit1.stopAll();
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

        bitset<32> bits(motor->getStatusBits());

       	mIsActiveLabel->Caption 	= (motor->isActive()) 	    ? "True" : "False";
        mIsHomingLabel->Caption 	= (motor->isHoming()) 	    ? "True" : "False";
        mIsHomedLabel->Caption  	= (motor->isHomed()) 	    ? "True" : "False";
        mIsForwardingLabel->Caption = (motor->isForwarding()) 	? "True" : "False";
        mIsReversingLabel->Caption  = (motor->isReversing()) 	? "True" : "False";

		if(motor->isActive())
        {
			mVelocityLbl->Caption = FloatToStrF(v, ffFixed, 4,3);
        }
        else
        {
			mVelocityLbl->Caption = FloatToStrF(0,ffFixed, 4,3);
        }
    }
}

void __fastcall TMain::DeviceValueEdit(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key != vkReturn)
    {
    	return;
    }
    APTMotor* motor = getCurrentMotor();

    if(!motor)
    {
    	Log(lError) << "No motor to set values for";
        return;
    }

	mtkFloatLabeledEdit* e = dynamic_cast<mtkFloatLabeledEdit*>(Sender);
    if(e == mJogVelocity)
    {
        double vel = mJogVelocity->GetValue();
        Log(lInfo) << "New JOG velocity (mm/s): " <<vel;
        motor->setJogVelocity(vel);
    }
    else if(e == mJogAcc)
    {
        double a = mJogAcc->GetValue();
        Log(lInfo) << "New JOG acceleration (mm/(s*s)): " <<a;
        motor->setJogAcceleration(a);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::JoyStickValueEdit(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key != vkReturn)
    {
    	return;
    }

	mtkFloatLabeledEdit* e = dynamic_cast<mtkFloatLabeledEdit*>(Sender);
    if(e == mMaxXYJogVelocityJoystick)
    {
        double vel = mMaxXYJogVelocityJoystick->GetValue();
        Log(lInfo) << "New jog velocity (mm/s): " <<vel;
		mJoyStick.getXAxis().setMaxVelocity(vel);
		mJoyStick.getYAxis().setMaxVelocity(vel);
    }
    else if(e == mXYJogAccelerationJoystick)
    {
        double a = mXYJogAccelerationJoystick->GetValue();
        Log(lInfo) << "New jog acceleration (mm/(s*s)): " <<a;
        mXYZUnit1.getXMotor()->setJogAcceleration(a);
        mXYZUnit1.getYMotor()->setJogAcceleration(a);
    }
    else if(e == mMaxZJogVelocityJoystick)
    {
        double v = mMaxZJogVelocityJoystick->GetValue();
        Log(lInfo) << "New Z jog velocity (mm/s): " <<v;
        mXYZUnit1.getZMotor()->setJogVelocity(v);
    }
    else if(e == mZJogAccelerationJoystick)
    {
        double a = mZJogAccelerationJoystick->GetValue();
        Log(lInfo) << "New Z jog acceleration (mm/(s*s)): " <<a;
        mXYZUnit1.getZMotor()->setJogAcceleration(a);
    }
    else if(e == mNrOfGearsLbl)
    {
        int g = mNrOfGearsLbl->getValue();
        Log(lInfo) << "New number of gears): " <<g;
        mJoyStick.getXAxis().setNumberOfGears(g);
        mJoyStick.getYAxis().setNumberOfGears(g);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::mJogModeCBClick(TObject *Sender)
{
    APTMotor* motor = getCurrentMotor();
    if(motor == NULL)
    {
    	Log(lInfo) << "Motor object is null..";
    	return;
    }

	TCheckBox* cb = (TCheckBox*)(Sender);
    if(cb == mJogModeCB)
    {
        if(mJogModeCB->Checked)
        {
            motor->setJogMoveMode(jmContinuous);
        }
        else
        {
            motor->setJogMoveMode(jmSingleStep);
        }
    }
    else if(cb == mJogStopModeCB)
    {
        if(mJogStopModeCB->Checked)
        {
            motor->setJogStopMode(smProfiled);
        }
        else
        {
            motor->setJogStopMode(smImmediate);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::DeviceBtnDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{

	TButton* btn = (TButton*)(Sender);
    if(btn == Button3)
    {
		jogForwardExecute(NULL);
    }

    if(btn == Button4)
    {
		jogBackwardsExecute(NULL);
    }

    if(btn == mJogStopBtn)
    {
	    stopMotorExecute(btn);
    }


    jsStateRG->ItemIndex = 1; //Disable Joystick
}

//---------------------------------------------------------------------------
void __fastcall TMain::jsAxisRGClick(TObject *Sender)
{
	TRadioGroup *rg = (TRadioGroup*)(Sender);
	if(rg == jsStateRG)
   	{
   		jsStateRG->ItemIndex == 0 ?
   		mJoyStick.enable() : mJoyStick.disable();
   	}
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

