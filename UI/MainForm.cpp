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

extern string gLogFileLocation;
extern string gLogFileName;

using namespace mtk;
//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
:
	TRegistryForm("Test", "MainForm", Owner),
	logMsgMethod(&logMsg),
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", gLogFileName), logMsgMethod),
    mIniFile("ArrayBot.ini"),
	mAB(mIniFile),
    mBottomPanelHeight(100)
{
	TMemoLogger::mMemoIsEnabled = false;

    mIniFile.load();

    mProperties.setSection("UI");
    mProperties.add((BaseProperty*) &mBottomPanelHeight.setup("BOTTOM_PANEL_HEIGHT", 			100, true));

	mProperties.setIniFile(&mIniFile);
    mProperties.read();

    mAB.assignWindowHandle((int) Handle);
}

__fastcall TMain::~TMain()
{
	mProperties.write();
    mIniFile.save();
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject *Sender)
{
	TMemoLogger::mMemoIsEnabled = true;
	mLogFileReader.start(true);
    sleep(100);
	initBotAExecute(NULL);

    //Select joystick control for CoverSlip Unit
	JoyControlRG->ItemIndex = 0;
    JoyControlRG->OnClick(NULL);

    //Select medium speed on start
	JSSpeedsRG->ItemIndex = 1;
    JSSpeedsRG->OnClick(NULL);
    BottomPanel->Height = mBottomPanelHeight;
}

void __fastcall TMain::initBotAExecute(TObject *Sender)
{
	mAB.initialize();

	TXYZUnitFrame1->assignUnit(&mAB.getCoverSlipUnit());
	TXYZUnitFrame2->assignUnit(&mAB.getWhiskerUnit());

    //JoyStick stuff.....
    mMaxXYJogVelocityJoystick->SetNumber(mAB.getJoyStick().getXAxis().getMaxVelocity());
    mXYJogAccelerationJoystick->SetNumber(mAB.getJoyStick().getXAxis().getAcceleration());

    if(mAB.getCoverSlipUnit().getZMotor())
    {
    	mMaxZJogVelocityJoystick->SetNumber(mAB.getCoverSlipUnit().getZMotor()->getVelocity());
    	mZJogAccelerationJoystick->SetNumber(mAB.getCoverSlipUnit().getZMotor()->getAcceleration());
    }

	mAB.getJoyStick().connect();
    InitCloseBtn->Action = ShutDownA;
}

void __fastcall TMain::ShutDownAExecute(TObject *Sender)
{
	StatusTimer->Enabled = false;

    mAB.getJoyStick().disable();

    TXYZUnitFrame1->disable();
    TXYZUnitFrame2->disable();

    //The shutdown disconnects all devices
    mAB.shutDown();
    InitCloseBtn->Action = initBotA;
}

//---------------------------------------------------------------------------
void __fastcall TMain::JoyControlRGClick(TObject *Sender)
{
	//Update joystick control
    if(JoyControlRG->ItemIndex == 0)
    {
    	mAB.enableCoverSlipJoyStick();
    }
    else if(JoyControlRG->ItemIndex == 1)
    {
    	mAB.enableWhiskerJoyStick();
    }
    else
    {
    	mAB.disableJoyStick();
    }
}

void __fastcall TMain::stopAllAExecute(TObject *Sender)
{
	mAB.stopAll();
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
        Log(lDebug) << "New jog velocity (mm/s): " <<vel;
		mAB.getJoyStick().getXAxis().setMaxVelocity(vel);
		mAB.getJoyStick().getYAxis().setMaxVelocity(vel);
    }
    else if(e == mXYJogAccelerationJoystick)
    {
        double a = mXYJogAccelerationJoystick->GetValue();
        Log(lDebug) << "New jog acceleration (mm/(s*s)): " <<a;
        mAB.getCoverSlipUnit().getXMotor()->setJogAcceleration(a);
        mAB.getCoverSlipUnit().getYMotor()->setJogAcceleration(a);
        mAB.getWhiskerUnit().getXMotor()->setJogAcceleration(a);
        mAB.getWhiskerUnit().getYMotor()->setJogAcceleration(a);
    }
    else if(e == mMaxZJogVelocityJoystick)
    {
        double v = mMaxZJogVelocityJoystick->GetValue();
        Log(lDebug) << "New Z jog velocity (mm/s): " <<v;
        mAB.getCoverSlipUnit().getZMotor()->setJogVelocity(v);
        mAB.getWhiskerUnit().getZMotor()->setJogVelocity(v);
    }
    else if(e == mZJogAccelerationJoystick)
    {
        double a = mZJogAccelerationJoystick->GetValue();
        Log(lDebug) << "New Z jog acceleration (mm/(s*s)): " <<a;
        mAB.getCoverSlipUnit().getZMotor()->setJogAcceleration(a);
        mAB.getWhiskerUnit().getZMotor()->setJogAcceleration(a);
    }
    else if(Sender == NULL) //Manually update velocities
    {
        double vel = mMaxXYJogVelocityJoystick->GetValue();
        double aXY = mXYJogAccelerationJoystick->GetValue();
        Log(lDebug) << "New jog velocity (mm/s): " <<vel;
        Log(lDebug) << "New jog acceleration (mm/(s*s)): " <<aXY;
		mAB.getJoyStick().getXAxis().setMaxVelocity(vel);
		mAB.getJoyStick().getYAxis().setMaxVelocity(vel);

        double vZ  = mMaxZJogVelocityJoystick->GetValue();
   	    double aZ  = mZJogAccelerationJoystick->GetValue();

        Log(lDebug) << "New Z jog acceleration (mm/(s*s)): " <<aZ;
        Log(lDebug) << "New Z jog velocity (mm/s): " <<vZ;
        if(mAB.getCoverSlipUnit().getXMotor() && mAB.getCoverSlipUnit().getYMotor())
        {
            mAB.getCoverSlipUnit().getXMotor()->setJogAcceleration(aXY);
            mAB.getCoverSlipUnit().getYMotor()->setJogAcceleration(aXY);

            mAB.getCoverSlipUnit().getXMotor()->setPotentiometerVelocity(vel);
            mAB.getCoverSlipUnit().getYMotor()->setPotentiometerVelocity(vel);
        }
        if(mAB.getWhiskerUnit().getXMotor() && mAB.getWhiskerUnit().getYMotor())
        {
            mAB.getWhiskerUnit().getXMotor()->setJogAcceleration(aXY);
            mAB.getWhiskerUnit().getYMotor()->setJogAcceleration(aXY);
        }

        if(mAB.getCoverSlipUnit().getZMotor())
        {
        	mAB.getCoverSlipUnit().getZMotor()->setJogVelocity(vZ);
	        mAB.getCoverSlipUnit().getZMotor()->setJogAcceleration(aZ);
        }

        if(mAB.getWhiskerUnit().getZMotor())
        {
	        mAB.getWhiskerUnit().getZMotor()->setJogVelocity(vZ);
        	mAB.getWhiskerUnit().getZMotor()->setJogAcceleration(aZ);
        }
    }
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

void __fastcall TMain::MoveBtnClick(TObject *Sender)
{
    APTMotor* yCS 	= mAB.getCoverSlipUnit().getYMotor();
	APTMotor* zCS 	= mAB.getCoverSlipUnit().getZMotor();

    APTMotor* yW 	= mAB.getWhiskerUnit().getYMotor();
	APTMotor* zW 	= mAB.getWhiskerUnit().getZMotor();

	if(!yCS || !zCS || !yW || !zW)
    {
    	Log(lError) << "Can't carry out this move.. at least one motor is absent";
        return;
    }

    double vertVel 	= mMoveVelocityVerticalE->GetNumber();
    double horizVel = mMoveVelHorizE->GetNumber();
    double acc 		= mMoveAccelerationE->GetNumber();

	//Update motors with current parameters and start the move
    zCS->setJogVelocity(vertVel);
    zCS->setJogAcceleration(acc);

    zW->setJogVelocity(vertVel);
    zW->setJogAcceleration(acc);

    double tanTheta = tan(toRadians(mMoveAngleE->GetValue()));
    yCS->setJogVelocity(horizVel);
    yCS->setJogAcceleration(acc / tanTheta);

    yW->setJogVelocity(horizVel);
    yW->setJogAcceleration(acc / tanTheta);

    //get current positions and carry out some moveTo's
    double yPos = yCS->getPosition();
    double zPos = zCS->getPosition();

	double newCSZPos = zPos + mVerticalMoveDistanceE->GetValue();
	double newCSYPos = (tanTheta != 0) ?
    					yPos + (newCSZPos - zPos) / tanTheta : yPos;

	//Calculate for the whisker
    yPos = yW->getPosition();
    zPos = zW->getPosition();

	double newWZPos = zPos + mVerticalMoveDistanceE->GetValue();
	double newWYPos = (tanTheta != 0) ?
    					(yPos + (newWZPos - zPos) / tanTheta) : yPos;

    Log(lInfo) << "Moving CS Vertical to: "	<<newCSZPos;
    Log(lInfo) << "Moving CS Horiz to: "	<<newCSYPos;

    Log(lInfo) << "Moving W Vertical to: "	<<newWZPos;
    Log(lInfo) << "Moving W Horiz to: "		<<newWYPos;


    if(newCSYPos >=150 || newWYPos >=150 )
    {
    	Log(lError) << "New CoverSlip or Whisker Y position to big: "<<newCSYPos;
        return;
    }

    if(newCSZPos >=25 || newWZPos >=25)
    {
    	Log(lError) << "New CoverSlip or Whisker Z position to big: "<<newWYPos;
        return;
    }

    yCS->moveToPosition(newCSYPos);
    zCS->moveToPosition(newCSZPos);

    yW->moveToPosition(newWYPos);
    zW->moveToPosition(newWZPos);
}

//---------------------------------------------------------------------------
void __fastcall TMain::JSSpeedsRGClick(TObject *Sender)
{
    unsigned short key  = 13;
    TShiftState ss;
	if(JSSpeedsRG->ItemIndex == 0) //Fast
    {
		mMaxXYJogVelocityJoystick->SetNumber(30);
		mXYJogAccelerationJoystick->SetNumber(10);
		mMaxZJogVelocityJoystick->SetNumber(2);
		mZJogAccelerationJoystick->SetNumber(1.5);
    }
    else if (JSSpeedsRG->ItemIndex == 1) //Medium
    {
		mMaxXYJogVelocityJoystick->SetNumber(10);
		mXYJogAccelerationJoystick->SetNumber(5);
		mMaxZJogVelocityJoystick->SetNumber(1.5);
		mZJogAccelerationJoystick->SetNumber(3);
    }
    else if (JSSpeedsRG->ItemIndex == 2) //Slow
    {
		mMaxXYJogVelocityJoystick->SetNumber(1);
		mXYJogAccelerationJoystick->SetNumber(1);
		mMaxZJogVelocityJoystick->SetNumber(0.5);
		mZJogAccelerationJoystick->SetNumber(0.1);
    }
	JoyStickValueEdit(NULL, key, ss);
}

//---------------------------------------------------------------------------
void __fastcall TMain::Button2Click(TObject *Sender)
{
	BottomPanel->Visible = !BottomPanel->Visible;
}



