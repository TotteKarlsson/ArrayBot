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
#include "mtkMathUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntegerLabeledEdit"
#pragma link "mtkFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "abXYZUnitFrame"
#pragma link "abMotorFrame"
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
    mCoverSlip("CoverSlip Unit", &mJoyStick, mIniFile),
    mWhisker("Whisker Unit", &mJoyStick, mIniFile)

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

//---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject *Sender)
{
	TMemoLogger::mMemoIsEnabled = true;
	mLogFileReader.start(true);
	InitializeUnitsAExecute(NULL);
}

void __fastcall TMain::InitializeUnitsAExecute(TObject *Sender)
{
	mCoverSlip.initialize();
    addDevicesToListBoxExecute(Sender);

    //Fill out edits
    mMaxXYJogVelocityJoystick->SetNumber(mJoyStick.getXAxis().getMaxVelocity());
    mXYJogAccelerationJoystick->SetNumber(mJoyStick.getXAxis().getAcceleration());

    if(mCoverSlip.getZMotor())
    {
    	mMaxZJogVelocityJoystick->SetNumber(mCoverSlip.getZMotor()->getVelocity());
    	mZJogAccelerationJoystick->SetNumber(mCoverSlip.getZMotor()->getAcceleration());
    }

	mNrOfGearsLbl->setValue(mJoyStick.getXAxis().getNumberOfGears());
	mJoyStick.connect();

	TXYZUnitFrame1->assignUnit(&mCoverSlip);
    InitCloseBtn->Action = ShutDownA;
}

void __fastcall TMain::ShutDownAExecute(TObject *Sender)
{
	StatusTimer->Enabled = false;
	devicesLB->Clear();

    mJoyStick.disable();

    TXYZUnitFrame1->disable();

    //The shutdown disconnects all devices
	mCoverSlip.shutDown();
    InitCloseBtn->Action = InitializeUnitsA;
}

void __fastcall TMain::addDevicesToListBoxExecute(TObject *Sender)
{
	//Connect all available devices
  	APTDevice* device = mCoverSlip.mDeviceManager.getFirst();
	while(device)
    {
		string serial = device->getSerial();

        //Add to listbox
        devicesLB->Items->AddObject(serial.c_str(), (TObject*) device);
        device = mCoverSlip.mDeviceManager.getNext();
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

        APTMotor* motor = dynamic_cast<APTMotor*>(device);
        if(motor)
        {
      		//Fill out motor frame
        }
        device->identify();
    }
}

void __fastcall TMain::stopAllAExecute(TObject *Sender)
{
    mJoyStick.disable();
    mCoverSlip.stopAll();
}

//---------------------------------------------------------------------------
void __fastcall TMain::StatusTimerTimer(TObject *Sender)
{
    int ii = devicesLB->ItemIndex;
    if(ii > -1)
    {
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
        mCoverSlip.getXMotor()->setJogAcceleration(a);
        mCoverSlip.getYMotor()->setJogAcceleration(a);
    }
    else if(e == mMaxZJogVelocityJoystick)
    {
        double v = mMaxZJogVelocityJoystick->GetValue();
        Log(lInfo) << "New Z jog velocity (mm/s): " <<v;
        mCoverSlip.getZMotor()->setJogVelocity(v);
    }
    else if(e == mZJogAccelerationJoystick)
    {
        double a = mZJogAccelerationJoystick->GetValue();
        Log(lInfo) << "New Z jog acceleration (mm/(s*s)): " <<a;
        mCoverSlip.getZMotor()->setJogAcceleration(a);
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
void __fastcall TMain::GotoBtnClick(TObject *Sender)
{
    APTMotor* x = mCoverSlip.getXMotor();
    APTMotor* y = mCoverSlip.getYMotor();
    APTMotor* z = mCoverSlip.getZMotor();

    if(x && y && z)
    {
    	int index = PositionsCB->ItemIndex;
        if(index <= 0)
        {
        	return;
        }

    	XYZUnitPosition* pos = (XYZUnitPosition*)PositionsCB->Items->Objects[index];
        if(pos)
        {
	        mCoverSlip.moveToPosition((*pos));
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::PositionsCBChange(TObject *Sender)
{
	if(PositionsCB->ItemIndex == 0)
    {
    	//Open edit positions form
    }
}


//---------------------------------------------------------------------------
void __fastcall TMain::Button5Click(TObject *Sender)
{
	//Add position
    XYZUnitPosition* newPos = new XYZUnitPosition(mPositionLabelE->getValue(),
    			mXPosE->GetValue(),
                mYPosE->GetValue(),
                mZPosE->GetValue());

	PositionsCB->Items->InsertObject(PositionsCB->Items->Count, newPos->getLabel().c_str(), (TObject*) newPos);

	mCoverSlip.positions().add(*newPos);
}

//---------------------------------------------------------------------------
void __fastcall TMain::moveEdit(TObject *Sender, WORD &Key, TShiftState Shift)
{
	//Depending on which edit was edited, update the other ones
	if(Key != vkReturn)
    {
    	return;
    }

	mtkFloatLabeledEdit* e = dynamic_cast<mtkFloatLabeledEdit*>(Sender);

    if(e == mMoveVelocityVerticalE || e == mMoveAngleE)
    {
    	//Update horiz value using the angle
        double tanTheta = tan(toRadians(mMoveAngleE->GetValue()));
        if(tanTheta != 0.0)
        {
        	mMoveVelHorizE->SetNumber(mMoveVelocityVerticalE->GetValue()/tanTheta);
        }
        else
        {
			mMoveVelHorizE->SetNumber(0.0);
        }
    }
}

void __fastcall TMain::LiftRibbonBtnClick(TObject *Sender)
{
	APTMotor* z = mCoverSlip.getZMotor();
    APTMotor* x = mCoverSlip.getXMotor();
    double tanTheta = tan(toRadians(mMoveAngleE->GetValue()));

	//Update motors with current parameters and start the move
    z->setJogVelocity(mMoveVelocityVerticalE->GetNumber());
    z->setJogAcceleration(mMoveAccelerationE->GetNumber());

    x->setJogVelocity(mMoveVelHorizE->GetNumber());
    x->setJogAcceleration(mMoveAccelerationE->GetNumber()/tanTheta);

    //get current positions and carry out some moveTo's
    double xPos = x->getPosition();
    double zPos = z->getPosition();

	double newZPos = zPos + mVertticalMoveDistanceE->GetValue();
	double newXPos;// = xPos + mVertticalMoveDistanceE->GetValue();
    if(tanTheta != 0)
    {
		newXPos = xPos + (newZPos - zPos) / tanTheta;
    }
    else
    {
		newXPos = xPos;
    }

    Log(lInfo) << "Moving Vertical to: "<<newZPos;
    Log(lInfo) << "Moving Horiz to: "<<newXPos;
    z->moveToPosition(newZPos);
    x->moveToPosition(newXPos);
}


