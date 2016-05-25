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
#pragma link "TFloatLabeledEdit"
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
    mBottomPanelHeight(100),
    mBottomPanelVisible(true),
    mTopPanelHeight(360),
    mIniFile("ArrayBot.ini", true, true),
	mAB(mIniFile)
{
	TMemoLogger::mMemoIsEnabled = false;

	//Setup UI properties
    mProperties.setSection("UI");
    mProperties.add((BaseProperty*) &mBottomPanelHeight.setup("BOTTOM_PANEL_HEIGHT", 			100, true));
    mProperties.add((BaseProperty*) &mTopPanelHeight.setup("TOP_PANEL_HEIGHT", 					360, true));
    mProperties.add((BaseProperty*) &mBottomPanelVisible.setup("BOTTOM_PANEL_VISIBLE",			true, true));
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

	//Initialize UI
    mCSAngleE->setValue(mAB.getCoverSlipAngleController().getAngle());

    //Assign editbox references to Lifting parameters
    mMoveAngleE->assignExternalProperty(&(mAB.getCombinedMove().mAngle), true);
    mCSAngleE->assignExternalProperty(&mAB.getCoverSlipAngleController().mAngle, true);

    mJSNoneBtn->Down 		= true;
	mJSSpeedMediumBtn->Click();

    //JoyStick Settings
    JoyStickSettings& js = mAB.getJoyStickSettings();
    JoyStickSetting* jss = js.getFirst();
    while(jss)
    {
    	JoyStickSettingsCB->Items->AddObject(jss->getLabel().c_str(), (TObject*) jss);
        jss = js.getNext();
    }
	JoyStickSettingsCB->ItemIndex = 0;
}

void __fastcall TMain::initBotAExecute(TObject *Sender)
{
	mAB.initialize();

	TXYZUnitFrame1->assignUnit(&mAB.getCoverSlipUnit());
	TXYZUnitFrame2->assignUnit(&mAB.getWhiskerUnit());

	TMotorFrame1->assignMotor(mAB.getCoverSlipAngleController().getMotor());
    //JoyStick stuff.....
    mMaxXYJogVelocityJoystick->setValue(mAB.getJoyStick().getXAxis().getMaxVelocity());
    mXYJogAccelerationJoystick->setValue(mAB.getJoyStick().getXAxis().getAcceleration());

    if(mAB.getCoverSlipUnit().getZMotor())
    {
    	mMaxZJogVelocityJoystick->setValue(mAB.getCoverSlipUnit().getZMotor()->getVelocity());
    	mZJogAccelerationJoystick->setValue(mAB.getCoverSlipUnit().getZMotor()->getAcceleration());
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

void __fastcall TMain::stopAllAExecute(TObject *Sender)
{
	mAB.stopAll();
}

//---------------------------------------------------------------------------
void __fastcall TMain::moveEdit(TObject *Sender, WORD &Key, TShiftState Shift)
{
	//Depending on which edit was edited, update the other ones
	if(Key != vkReturn)
    {
    	return;
    }

	TFloatLabeledEdit* e = dynamic_cast<TFloatLabeledEdit*>(Sender);

    if(e == mMoveVelocityVerticalE || e == mMoveAngleE)
    {
    	//Update horiz value using the angle
        double tanTheta = tan(toRadians(mMoveAngleE->getValue()));
        if(tanTheta != 0.0)
        {
        	mMoveVelHorizE->setValue(mMoveVelocityVerticalE->getValue()/tanTheta);
        }
        else
        {
			mMoveVelHorizE->setValue(0.0);
        }
    }

    mMoveAngleE->Update();
}

void __fastcall TMain::LiftCSBtnClick(TObject *Sender)
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

    double vertVel 	= mMoveVelocityVerticalE->getValue();
    double horizVel = mMoveVelHorizE->getValue();
    double acc 		= mMoveAccelerationE->getValue();

	//Update motors with current parameters and start the move
    zCS->setJogVelocity(vertVel);
    zCS->setJogAcceleration(acc);

    zW->setJogVelocity(vertVel);
    zW->setJogAcceleration(acc);

    double tanTheta = tan(toRadians(mMoveAngleE->getValue()));
    yCS->setJogVelocity(horizVel);
    yCS->setJogAcceleration(acc / tanTheta);

    yW->setJogVelocity(horizVel);
    yW->setJogAcceleration(acc / tanTheta);

    //get current positions and carry out some moveTo's
    double yPos = yCS->getPosition();
    double zPos = zCS->getPosition();

	double newCSZPos = zPos + mVerticalMoveDistanceE->getValue();
	double newCSYPos = (tanTheta != 0) ?
    					yPos + (newCSZPos - zPos) / tanTheta : yPos;

	//Calculate for the whisker
    yPos = yW->getPosition();
    zPos = zW->getPosition();

	double newWZPos = zPos + mVerticalMoveDistanceE->getValue();
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

	//Initiate the move
    yCS->moveAbsolute(newCSYPos);
    yW->moveAbsolute(newWYPos);

    zCS->moveAbsolute(newCSZPos);
    zW->moveAbsolute(newWZPos);
}

//---------------------------------------------------------------------------
void __fastcall TMain::Button2Click(TObject *Sender)
{
    if(BottomPanel->Visible)
    {
		BottomPanel->Visible = false;
		this->Height = this->Height - BottomPanel->Height;
    }
    else
    {
		BottomPanel->Visible = true;
        this->Height = BottomPanel->Height + TopPanel->Height;
        BottomPanel->Top = this->Height;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::Button3Click(TObject *Sender)
{
	mAB.home();
}

//---------------------------------------------------------------------------
void __fastcall TMain::stowBtnClick(TObject *Sender)
{
	mAB.stow();
}

//---------------------------------------------------------------------------
void __fastcall TMain::mCSAngleEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	TFloatLabeledEdit* e = dynamic_cast<TFloatLabeledEdit*>(Sender);
	if(Key != vkReturn)
    {
    	return;
    }

    if(e == mCSAngleE)
    {
    	mAB.getCoverSlipAngleController().setAngle(mCSAngleE->getValue() + 225.0);
    }
    else if (e == mCameraAngleEdit)
    {
    	mAB.getCameraAngleController().setAngle(mCameraAngleEdit->getValue());
    }
}

void __fastcall TMain::LiftAngleButtonUpRightClick(TObject *Sender)
{
// 	TRzSpinButtons* btn = dynamic_cast<TRzSpinButtons*>(Sender);
//    if(btn == LiftAngleButton)
//    {
//	    mMoveAngleE->setValue(mMoveAngleE->getValue() + 1);
//    }
//    else if (btn == CSAngleButton)
//    {
//		mCSAngleE->setValue(mCSAngleE->getValue() + 1);
//    }
}
//---------------------------------------------------------------------------

void __fastcall TMain::LiftAngleButtonDownLeftClick(TObject *Sender)
{
// 	TRzSpinButtons* btn = dynamic_cast<TRzSpinButtons*>(Sender);
//    if(btn == LiftAngleButton)
//    {
//	    mMoveAngleE->setValue(mMoveAngleE->getValue() + 1);
//    }
//    else if (btn == CSAngleButton)
//    {
//		mCSAngleE->setValue(mCSAngleE->getValue() + 1);
//    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::JSControlClick(TObject *Sender)
{
	//Setup Joystick control
    TSpeedButton* btn = dynamic_cast<TSpeedButton*>(Sender);
    if(btn == mJSCSBtn)
    {
		mAB.enableCoverSlipJoyStick();
    }
    else if(btn == mJSWhiskerBtn)
    {
	 	mAB.enableWhiskerJoyStick();
    }
    else
    {
	 	mAB.disableJoyStick();
    }
}

void __fastcall TMain::JSSpeedBtnClick(TObject *Sender)
{
    TSpeedButton* btn = dynamic_cast<TSpeedButton*>(Sender);
	if(btn == mJSSpeedFastBtn) //Fast
    {
    	//Apply "FAST" JS setting
        mAB.applyJoyStickSetting("Fast");
    }
    else if (btn == mJSSpeedMediumBtn) //Medium
    {
        mAB.applyJoyStickSetting("Medium");
    }
    else if (btn == mJSSpeedSlowBtn) //Slow
    {
        mAB.applyJoyStickSetting("Slow");
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::JoyStickValueEdit(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key != vkReturn)
    {
    	return;
    }

	//Get current setting
    int index = JoyStickSettingsCB->ItemIndex;
    if(index == -1)
    {
    	return;
    }

    JoyStickSetting* jss = (JoyStickSetting*) JoyStickSettingsCB->Items->Objects[index];
    if(!jss)
    {
    	return;
    }

    // Update setting from edits
    jss->set(mMaxXYJogVelocityJoystick->getValue(), mXYJogAccelerationJoystick->getValue(),
			 mMaxZJogVelocityJoystick->getValue(), mZJogAccelerationJoystick->getValue());
}

