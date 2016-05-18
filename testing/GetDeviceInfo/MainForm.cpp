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
#pragma link "TFloatLabeledEdit"
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
    mJoyStick((int) Handle)
{
	TMemoLogger::mMemoIsEnabled = false;

}

__fastcall TMain::~TMain()
{}

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

	mJoyStick.connect();
    mJoyStick.enable();
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
        	double v = motor->getVelocity();
			mMaxVelocity->SetNumber(v);

        	double a = motor->getAcceleration();
			mAcceleration->SetNumber(a);

            v = motor->getJogVelocity();
            mJogVelocity->SetNumber(v);

            a = motor->getJogAcceleration();
            mJogAcc->SetNumber(a);

            JogMoveMode jm = motor->getJogMoveMode();
            mJogModeCB->Checked = (jm == jmContinuous) ? true : false;

            StopMode sm = motor->getJogStopMode();
            mJogStopModeCB->Checked = (sm == smProfiled) ? true : false;

			mJoyStick.getXAxis().assignMotor(motor);
			mJoyStick.getYAxis().assignMotor(motor);

			mJoyStick.getXAxis().setMaxVelocity(mJogVelocity->GetNumber());
			mJoyStick.getYAxis().setMaxVelocity(mJogVelocity->GetNumber());

			mJoyStick.getButton(3).assignMotor(motor);
			mJoyStick.getButton(4).assignMotor(motor);

            mJoyStick.getButton(3).setForward();
            mJoyStick.getButton(4).setReverse();

            updateJoyStickAxes();
        }

    	//Populate device frame
        device->identify();
		StatusTimer->Enabled = true;
    }
}

void TMain::updateJoyStickAxes()
{
    switch(jsAxisRG->ItemIndex)
    {
        case 0:
            mJoyStick.getXAxis().enable();
            mJoyStick.getYAxis().disable();
            mJoyStick.getZAxis().disable();
        break;
        case 1:
            mJoyStick.getXAxis().disable();
            mJoyStick.getYAxis().enable();
            mJoyStick.getZAxis().disable();
        break;
        case 2:
            mJoyStick.getXAxis().disable();
            mJoyStick.getYAxis().disable();
            mJoyStick.getZAxis().enable();
        break;
        default:
            Log(lError) << "Bad joystick axes";
        break;
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
//	MotorCommand cmd(mcReverse);
//	mMotorMessageContainer.post(cmd);
}

void __fastcall TMain::stopMotorExecute(TObject *Sender)
{
	//Use whatever speed is selected
    APTMotor* motor = dynamic_cast<APTMotor*>(getCurrentDevice());
    if(motor)
    {
    	motor->stop();
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

        bitset<32> bits(motor->getStatusBits());
//        Log(lInfo) << bits;
//        String line1 = " 0  1  2  3  4  5  6  7  8  9  10";
//        String line2 = bits.test(0) ? " 1" : " 0";
//        line2 += bits.test(1) ? "  1" : "  0" ;
//        line2 += bits.test(2) ? "  1" : "  0" ;
//        line2 += bits.test(3) ? "  1" : "  0" ;
//        line2 += bits.test(4) ? "  1" : "  0" ;
//        line2 += bits.test(5) ? "  1" : "  0" ;
//        line2 += bits.test(6) ? "  1" : "  0" ;
//        line2 += bits.test(7) ? "  1" : "  0" ;
//        line2 += bits.test(8) ? "  1" : "  0" ;
//        line2 += bits.test(9) ? "  1" : "  0" ;
//        line2 += bits.test(10) ? "   1" : "   0" ;

//		  Memo1->Clear();
//        Memo1->Lines->Add(line1);
//        Memo1->Lines->Add(line2);

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

//---------------------------------------------------------------------------
void __fastcall TMain::mDeviceValueEdit(TObject *Sender, WORD &Key, TShiftState Shift)
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

	TFloatLabeledEdit* e = dynamic_cast<TFloatLabeledEdit*>(Sender);
    if(e == mMaxVelocity)
    {
        double vel = mMaxVelocity->GetValue();
        Log(lInfo) << "New velocity: " <<vel;
        motor->setVelocity(vel);
    }
    else if(e == mAcceleration)
    {
        double a = mAcceleration->GetValue();
        Log(lInfo) << "New acceleration: " <<a;
        motor->setAcceleration(a);
    }
    else if(e == mJogVelocity)
    {
        double vel = mJogVelocity->GetValue();
        Log(lInfo) << "New JOG velocity (mm/s): " <<vel;
        motor->setJogVelocity(vel);
		mJoyStick.getXAxis().setMaxVelocity(vel);
		mJoyStick.getYAxis().setMaxVelocity(vel);
    }
    else if(e == mJogAcc)
    {
        double a = mJogAcc->GetValue();
        Log(lInfo) << "New JOG acceleration (mm/(s*s)): " <<a;
        motor->setJogAcceleration(a);
    }
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

//	MotorCommand cmd(mcSetVelocity,  cVel + delta);
//	mMotorMessageContainer.post(cmd);
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

//	MotorCommand cmd(mcSetVelocity,  cVel - delta);
//	mMotorMessageContainer.post(cmd);
}

//---------------------------------------------------------------------------
void __fastcall TMain::switchdirectionBtnClick(TObject *Sender)
{
//	MotorCommand cmd(mcSwitchDirection);
//	mMotorMessageContainer.post(cmd);
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

    if(btn == fwdDriveBtn)
    {
		moveForwardExecute(Sender);
    }
    else if(btn == revDriveBtn)
    {
		moveBackwardExecute(Sender);
    }

    jsStateRG->ItemIndex = 1; //Disabled
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

void __fastcall TMain::Button5Click(TObject *Sender)
{
    APTMotor* motor = getCurrentMotor();
    if(motor == NULL)
    {
    	Log(lInfo) << "Motor object is null..";
    	return;
    }
	motor->getEncoderCounts();
}

//---------------------------------------------------------------------------
void __fastcall TMain::jsAxisRGClick(TObject *Sender)
{
	TRadioGroup *rg = (TRadioGroup*)(Sender);

	if(rg == jsAxisRG)
    {
		updateJoyStickAxes();
    }
    else if(rg == jsStateRG)
    {
    	jsStateRG->ItemIndex == 0 ?
    		mJoyStick.enable() : mJoyStick.disable();
    }
}



