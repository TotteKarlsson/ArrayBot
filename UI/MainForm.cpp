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
#include "abExceptions.h"

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
extern string gAppDataFolder;

using namespace mtk;
//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
:
	TRegistryForm("Test", "MainForm", Owner),
	logMsgMethod(&logMsg),
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", gLogFileName), logMsgMethod),
    mIniFile(joinPath(gAppDataFolder, "ArrayBot.ini"), true, true)
{
	TMemoLogger::mMemoIsEnabled = false;

    try
    {
		mAB = new ArrayBot(mIniFile);
    }
    catch(const ABException& e)
    {
		MessageDlg(e.Message().c_str(), mtWarning, TMsgDlgButtons() << mbOK, 0);
    }
	//Setup UI properties
    mProperties.setSection("UI");
	mProperties.setIniFile(&mIniFile);
    mProperties.read();
}

__fastcall TMain::~TMain()
{
	delete mAB;
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
    mCSAngleE->setValue(mAB->getCoverSlipAngleController().getAngle());

    //Assign editbox references to Lifting parameters
	//    mMoveAngleE->assignExternalProperty(&(mAB->getCombinedMove().mAngle), true);
	//    mCSAngleE->assignExternalProperty(&mAB->getCoverSlipAngleController().mAngle, true);

    //JoyStick Settings CB
    JoyStickSettings& js = mAB->getJoyStickSettings();
    JoyStickSetting* jss = js.getFirst();
    while(jss)
    {
    	JoyStickSettingsCB->Items->AddObject(jss->getLabel().c_str(), (TObject*) jss);
        jss = js.getNext();
    }

	JoyStickSettingsCB->ItemIndex = 0;
    JoyStickSettingsCB->OnChange(NULL);
	mJSSpeedMediumBtn->Click();
}

void __fastcall TMain::initBotAExecute(TObject *Sender)
{
	mAB->initialize();

	TXYZUnitFrame1->assignUnit(&mAB->getCoverSlipUnit());
	TXYZUnitFrame2->assignUnit(&mAB->getWhiskerUnit());

	TMotorFrame1->assignMotor(mAB->getCoverSlipAngleController().getMotor());
	TMotorFrame2->assignMotor(mAB->getCameraAngleController().getMotor());

    //ArrayBotJoyStick stuff.....
    mMaxXYJogVelocityJoystick->setValue(mAB->getJoyStick().getX1Axis().getMaxVelocity());
    mXYJogAccelerationJoystick->setValue(mAB->getJoyStick().getX1Axis().getAcceleration());

    if(mAB->getCoverSlipUnit().getZMotor())
    {
    	mMaxZJogVelocityJoystick->setValue(mAB->getCoverSlipUnit().getZMotor()->getVelocity());
    	mZJogAccelerationJoystick->setValue(mAB->getCoverSlipUnit().getZMotor()->getAcceleration());
    }

    InitCloseBtn->Action = ShutDownA;
}

void __fastcall TMain::ShutDownAExecute(TObject *Sender)
{
    mAB->getJoyStick().disable();

	TMotorFrame1->assignMotor(NULL);
	TMotorFrame2->assignMotor(NULL);

    TXYZUnitFrame1->disable();
    TXYZUnitFrame2->disable();

    //The shutdown disconnects all devices
    mAB->shutDown();

	while(mAB->isActive())
    {
    	sleep(100);
    }

    InitCloseBtn->Action = initBotA;
}

void __fastcall TMain::stopAllAExecute(TObject *Sender)
{
	mAB->stopAll();
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
}

void __fastcall TMain::LiftCSBtnClick(TObject *Sender)
{
	APTMotor* zCS 	= mAB->getCoverSlipUnit().getZMotor();
	APTMotor* zW 	= mAB->getWhiskerUnit().getZMotor();

	if(!zCS || !zW)
    {
    	Log(lError) << "Can't carry out this move.. at least one motor is absent";
        return;
    }

    double vertVel 	= mMoveVelocityVerticalE->getValue();
    double acc 		= mMoveAccelerationE->getValue();

	//Update motors with current parameters and start the move
    zCS->setJogVelocity(vertVel);
    zCS->setJogAcceleration(acc);

    zW->setJogVelocity(vertVel);
    zW->setJogAcceleration(acc);

    //get current positions and carry out some moveTo's
    double zPos = zCS->getPosition();

	double newCSZPos = zPos + mVerticalMoveDistanceE->getValue();

    zPos = zW->getPosition();

	double newWZPos = zPos + mVerticalMoveDistanceE->getValue();

    Log(lInfo) << "Moving CS Vertical to: "	<<newCSZPos;
    Log(lInfo) << "Moving W Vertical to: "	<<newWZPos;

    if(newCSZPos >=25 || newWZPos >=25)
    {
    	Log(lError) << "New CoverSlip or Whisker Z position to big: "<<newWZPos;
        return;
    }

	//Initiate the move
    zCS->moveAbsolute(newCSZPos);
    zW->moveAbsolute(newWZPos);
}

//---------------------------------------------------------------------------
void __fastcall TMain::Button3Click(TObject *Sender)
{
	mAB->home();
}

//---------------------------------------------------------------------------
void __fastcall TMain::stowBtnClick(TObject *Sender)
{
	mAB->stow();
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
    	mAB->getCoverSlipAngleController().setAngle(mCSAngleE->getValue());
    }
    else if (e == mCameraAngleEdit)
    {
    	mAB->getCameraAngleController().setAngle(mCameraAngleEdit->getValue());
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::JSControlClick(TObject *Sender)
{
	//Setup Joystick control
    TSpeedButton* btn = dynamic_cast<TSpeedButton*>(Sender);
    if(btn->Caption == "Enable")
    {
		if(!mAB->enableJoyStick())
        {
        	MessageDlg("Failed enabling the JoyStick. \r Please see the LogFile for Errors. \r JoyStick support is disabled for the rest of this session.", mtWarning, TMsgDlgButtons() << mbOK, 0);
            mJSCSBtn->Enabled = false;
        }
    }
    else
    {
	 	mAB->disableJoyStick();
    }
    btn->Caption = (mAB->getJoyStick().isEnabled()) ? "Disable" : "Enable";

    //There is a 'bug' regarding speed settings
    //Programatically apply currently selected setting
	if(mJSSpeedFastBtn->Down)
    {
		mJSSpeedFastBtn->Click();
    }

	if(mJSSpeedMediumBtn->Down)
    {
		mJSSpeedMediumBtn->Click();
    }

	if(mJSSpeedSlowBtn->Down)
    {
		mJSSpeedSlowBtn->Click();
    }
}

void __fastcall TMain::JSSpeedBtnClick(TObject *Sender)
{
    TSpeedButton* btn = dynamic_cast<TSpeedButton*>(Sender);
	if(btn == mJSSpeedFastBtn) //Fast
    {
    	//Apply "FAST" JS setting
        mAB->applyJoyStickSetting("Fast");
    }
    else if (btn == mJSSpeedMediumBtn) //Medium
    {
        mAB->applyJoyStickSetting("Medium");
    }
    else if (btn == mJSSpeedSlowBtn) //Slow
    {
        mAB->applyJoyStickSetting("Slow");
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
			 mMaxZJogVelocityJoystick->getValue(), mZJogAccelerationJoystick->getValue(),
             mAngleControlVelE->getValue(), mAngleControllerAccE->getValue()
             );
}


//Save parameters
void __fastcall TMain::Button1Click(TObject *Sender)
{
	mAB->writeINIParameters();
}


