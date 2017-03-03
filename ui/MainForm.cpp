#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "TMemoLogger.h"
#include "mtkStringList.h"
#include "atUtilities.h"
#include "apt/atAPTMotor.h"
#include "apt/atTCubeDCServo.h"
#include "mtkVCLUtils.h"
#include "mtkLogger.h"
#include <bitset>
#include "mtkMathUtils.h"
#include "atExceptions.h"
#include "TSplashForm.h"
#include "sound/atSounds.h"
#include "atCore.h"

#include "frames/TABProcessSequencerFrame.h"
#include "frames/TXYZPositionsFrame.h"
#include "frames/TXYZUnitFrame.h"
#include "frames/TSequencerButtonsFrame.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntegerLabeledEdit"
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "mtkFloatLabel"
#pragma link "TAboutArrayBotFrame"
#pragma link "TAboutArrayBot_2Frame"
#pragma link "TPropertyCheckBox"

#pragma link "cspin"
#pragma resource "*.dfm"
TMain *Main;

extern string           gLogFileLocation;
extern string           gLogFileName;
extern string           gAppDataFolder;
extern TSplashForm*  	gSplashForm;
extern bool             gAppIsStartingUp;
extern string 			gApplicationRegistryRoot;

using namespace mtk;

//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
:
	TRegistryForm(gApplicationRegistryRoot, "MainForm", Owner),
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", gLogFileName), &logMsg),
    mIniFile(joinPath(gAppDataFolder, "ArrayBot.ini"), true, true),
    mLogLevel(lAny),
    mInitBotThread(),
	mABProcessSequencerFrame(NULL),
    mRibbonLifterFrame(NULL),
    mTheWiggler(NULL, NULL)
{
    //Init the DLL -> give intra messages their ID's
	initABCoreLib();

	TMemoLogger::mMemoIsEnabled = false;
   	mLogFileReader.start(true);

    try
    {
		mAB = new ArrayBot(mIniFile, gAppDataFolder);
        mProcessSequencer = &(mAB->getProcessSequencer());
    }
    catch(const ABException& e)
    {
		MessageDlg(e.Message().c_str(), mtWarning, TMsgDlgButtons() << mbOK, 0);
    }

    if(mAB)
    {
	   	mAB->setArduinoClient(&mPufferArduinoClient);
    }

	//Setup UI properties
    mProperties.setSection("UI");
	mProperties.setIniFile(&mIniFile);

	mProperties.add((BaseProperty*)  &mLogLevel.setup( 	                    		"LOG_LEVEL",    	                lAny));
	mProperties.add((BaseProperty*)  &mArduinoServerPortE->getProperty()->setup(	"SERVER_PORT",    	 				50000));
	mProperties.add((BaseProperty*)  &mWigglerAmplitudeStepE->getProperty()->setup(	"WIGGLER_AMPLITUDE",    	 		0.5));
	mProperties.add((BaseProperty*)  &mWigglerAmplitudeE->getProperty()->setup(		"WIGGLER_AMPLITUDE_STEP",    		0.1));

    mProperties.read();

	mArduinoServerPortE->update();
	mWigglerAmplitudeE->update();
	mWigglerAmplitudeStepE->update();

	//Load motors in a thread
    mInitBotThread.assingBot(mAB);
    mInitBotThread.onFinishedInit = this->onFinishedInitBot;

    //We will setup UI frames after the bot is initialized
	mInitBotThread.start();

	WaitForDeviceInitTimer->Enabled = true;

    mTheWiggler.mMaxVelocity.setReference(&mWigglerVelocityE->getReference());
    mTheWiggler.mAmplitude.setReference(&mWigglerAmplitudeE->getReference());
    mTheWiggler.mMaxAcceleration.setReference(&mWigglerAccelerationE->getReference());

	mPufferArduinoClient.assignOnMessageReceivedCallBack(onArduinoMessageReceived);
    mPufferArduinoClient.onConnected 		= onArduinoClientConnected;
	mPufferArduinoClient.onDisconnected 	= onArduinoClientDisconnected;
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
	enableDisableUI(false);

	this->Visible = true;
	setupWindowTitle();

	gAppIsStartingUp = false;
    enableDisableArduinoClientControls(false);

    if(this->BorderStyle == bsNone)
    {
    	this->WindowState = wsMaximized;
    }

	TMemoLogger::mMemoIsEnabled = true;
    if(gSplashForm)
    {
		gSplashForm->mMainAppIsRunning = true;

        while(gSplashForm->isOnShowTime() == true || mInitBotThread.isAlive())
        {
            Application->ProcessMessages();
            //In order to show whats going on on the splash screen
            if(gSplashForm->Visible == false)
            {
                break;
            }
        }
		gSplashForm->Close();
    }

    setupUIFrames();

	gLogger.setLogLevel(mLogLevel);

	enableDisableUI(true);

	if(mLogLevel == lInfo)
	{
		LogLevelCB->ItemIndex = 0;
	}
	else if(mLogLevel == lAny)
	{
		LogLevelCB->ItemIndex = 1;
	}

	//Try to connect to the arduino server..
	mPufferArduinoClient.connect(50000);

	TMemoLogger::mMemoIsEnabled = true;
    UIUpdateTimer->Enabled = true;
}

void TMain::enableDisableUI(bool e)
{
	PageControl1->Visible = e;

	enableDisablePanel(mRightPanel, e);
	enableDisablePanel(mSequencesPanel, e);
    enableDisableGroupBox(JSGB, e);
    enableDisableGroupBox(mRibbonCreationGB, e);
}

void __fastcall TMain::WndProc(TMessage& Message)
{
    if (Message.Msg == getABCoreMessageID("MOTOR_WARNING_MESSAGE") && getABCoreMessageID("MOTOR_WARNING_MESSAGE") != 0)
    {
    	MotorMessageData* msg = reinterpret_cast<MotorMessageData*>(Message.WParam);
       	APTMotor* mtr = mAB->getMotorWithSerial(msg->mSerial);

        if(!mtr)
        {
        	//real bad....
        }

		//Handle the warning..
        if(msg->mCurrentPosition >= msg->mPositionLimits.getValue().getMax())
        {
            if(mtr)
            {
            	if(mtr->getLastCommand() != mcStopHard)
                {
            		mtr->stop();
	                playABSound(absMotorWarning);
    	            Log(lInfo) << "Stopped motor: "<<mtr->getName();
                }
            }
        }

        if(mtr->isInDangerZone())
        {
        	playABSound(absMotorWarning);
        }


        //Message is now consumed.. delete it
        delete msg;
    }
    else
    {
        TForm::WndProc(Message);
    }
}

//Callback from socket client class
void TMain::onArduinoClientConnected()
{
    Log(lDebug) << "ArduinoClient was connected..";

    //Send message to update UI
    mPufferArduinoClient.getServerStatus();
    enableDisableArduinoClientControls(true);
}

void TMain::onArduinoClientDisconnected()
{
    Log(lDebug) << "Arduino Client was disconnected..";
    enableDisableArduinoClientControls(false);
}

void TMain::enableDisableArduinoClientControls(bool enable)
{
	//Disable client related components..
//    enableDisablePanel(mBottomPanel, enable);
//    enableDisableGroupBox(mPufferGB, enable);
}

//---------------------------------------------------------------------------
void __fastcall TMain::WaitForDeviceInitTimerTimer(TObject *Sender)
{
	if(!mInitBotThread.isRunning()) //Not waiting for devices any more
    {
		WaitForDeviceInitTimer->Enabled = false;
    }
}

void __fastcall	TMain::setupUIFrames()
{
    //Create frames showing motor positions
    TXYZPositionsFrame* f1 = new TXYZPositionsFrame(this, mAB->getCoverSlipUnit());
    f1->Parent = this->mRightPanel;
    f1->Align = alBottom;

    TXYZPositionsFrame* f2 = new TXYZPositionsFrame(this, mAB->getWhiskerUnit());
    f2->Parent = this->mRightPanel;
    f2->Align = alBottom;

    this->mSequencesPanel->Top = 0;
    this->mSequencesPanel->Refresh();

	//Setup JoyStick;

    //Over ride joysticks button events  (cycle speeds and XY motions)
    mAB->getJoyStick().setButtonEvents(5,  NULL, onJSButton5Click);
    mAB->getJoyStick().setButtonEvents(6,  NULL, onJSButton6Click);

    //!Button 14 emergency stop
    mAB->getJoyStick().setButtonEvents(14, NULL, onJSButton14Click);

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
    //mJSCSBtn->Click();
	mAB->enableJoyStick();

    //XY velocity parameters
    mMaxXYJogVelocityJoystick->setValue(mAB->getJoyStick().getX1Axis().getMaxVelocity());
    mXYJogAccelerationJoystick->setValue(mAB->getJoyStick().getX1Axis().getAcceleration());

    if(mAB->getCoverSlipUnit().getZMotor())
    {
        mMaxZJogVelocityJoystick->setValue(mAB->getCoverSlipUnit().getZMotor()->getVelocity());
        mZJogAccelerationJoystick->setValue(mAB->getCoverSlipUnit().getZMotor()->getAcceleration());
    }

    //Lift Settings CB
    PairedMoves& pms = mAB->getLiftMoves();
    PairedMove* pm = pms.getFirst();
    while(pm)
    {
        string key = pm->mLabel;
        mLiftCB->Items->AddObject(pm->mLabel.c_str(), (TObject*) pm);
        pm = pms.getNext();
    }

    mLiftCB->ItemIndex = 0;
    mLiftCB->OnChange(NULL);

	//Create and setup XYZ unit frames
    mXYZUnitFrame1 = new TXYZUnitFrame(this);
    mXYZUnitFrame1->assignUnit(&mAB->getCoverSlipUnit());
    mXYZUnitFrame1->Parent = ScrollBox1;
    mXYZUnitFrame1->Left = 10;

    mXYZUnitFrame2 = new TXYZUnitFrame(this);
    mXYZUnitFrame2->assignUnit(&mAB->getWhiskerUnit());
    mXYZUnitFrame2->Parent = ScrollBox1;
    mXYZUnitFrame2->Left = 10;
    mXYZUnitFrame2->Top = mXYZUnitFrame1->Top + mXYZUnitFrame1->Height;

    //Create MoveSequencer frame
    mABProcessSequencerFrame = new TABProcessSequencerFrame(*(mAB), gAppDataFolder, mMoveSequencesPage);
    mABProcessSequencerFrame->Parent = mMoveSequencesPage;
    mABProcessSequencerFrame->Align = alClient;
    mABProcessSequencerFrame->init();

	mSequencerButtons = new TSequencerButtonsFrame(*(mAB), mSequencesPanel);
	mSequencerButtons->Parent = mSequencesPanel;
    mSequencerButtons->Align = alClient;
	mSequencerButtons->update();
}

void __fastcall TMain::reInitBotAExecute(TObject *Sender)
{
	mAB->initialize();

	mXYZUnitFrame1->assignUnit(&mAB->getCoverSlipUnit());
	mXYZUnitFrame2->assignUnit(&mAB->getWhiskerUnit());

    //ArrayBotJoyStick stuff.....
    mMaxXYJogVelocityJoystick->setValue(mAB->getJoyStick().getX1Axis().getMaxVelocity());
    mXYJogAccelerationJoystick->setValue(mAB->getJoyStick().getX1Axis().getAcceleration());

    if(mAB->getCoverSlipUnit().getZMotor())
    {
    	mMaxZJogVelocityJoystick->setValue(mAB->getCoverSlipUnit().getZMotor()->getVelocity());
    	mZJogAccelerationJoystick->setValue(mAB->getCoverSlipUnit().getZMotor()->getAcceleration());
    }

    ReInitBotBtn->Action = ShutDownA;
}

void __fastcall TMain::stopAllAExecute(TObject *Sender)
{
	mAB->stopAll();
    mTheWiggler.stopWiggle();
}

//---------------------------------------------------------------------------
void __fastcall TMain::mLiftTimerTimer(TObject *Sender)
{
	if(mAB->isActive())
    {
    	LiftBtn->Action = abortLiftA;
    }
    else
    {
    	LiftBtn->Action = liftA;
		mLiftTimer->Enabled = false;

    	//Re-enable the joystick.
		mAB->enableJoyStick();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::abortLiftAExecute(TObject *Sender)
{
	mAB->stopAll();
    Log(lInfo) << "The lift was aborted";

    //Re-enable the joystick.
	mAB->enableJoyStick();
}

PairedMove* TMain::getCurrentPairedMove()
{
	if(mLiftCB->ItemIndex > -1)
    {
    	return (PairedMove*) mLiftCB->Items->Objects[mLiftCB->ItemIndex];
    }
    return NULL;
}

//---------------------------------------------------------------------------
void __fastcall TMain::liftAExecute(TObject *Sender)
{
	PairedMove* pm = getCurrentPairedMove();

    pm->assignMotor1(mAB->getCoverSlipUnit().getZMotor());
    pm->assignMotor2(mAB->getWhiskerUnit().getZMotor());
    if(!pm)
    {
    	Log(lError) << "Can't carry out this move.. at least one motor is absent";
        return;
    }

    if(!pm->check())
    {
		Log(lError) << pm->getCheckMessage();
        MessageDlg(pm->getCheckMessage().c_str(), mtError, TMsgDlgButtons() << mbOK, 0);
        return;
    }

    //Re-enable the joystick after finish.
	mAB->disableJoyStick();
    pm->execute();
    mLiftTimer->Enabled = true;
   	LiftBtn->Action = abortLiftA;
}

//---------------------------------------------------------------------------
void __fastcall TMain::mLiftCBChange(TObject *Sender)
{
	//Update edits
    //Assign editbox references to Lifting parameters
	PairedMove* pm = getCurrentPairedMove();
	mMoveVelocityVerticalE->setReference(pm->mVelocity);
	mMoveAccelerationE->setReference(pm->mAcceleration);
}

//---------------------------------------------------------------------------
void __fastcall TMain::LogLevelCBChange(TObject *Sender)
{
    if(LogLevelCB->ItemIndex == 0)
    {
        mLogLevel = lInfo;
    }
    else if(LogLevelCB->ItemIndex == 1)
    {
        mLogLevel = lAny;
    }

    gLogger.setLogLevel(mLogLevel);
}

void __fastcall	TMain::onFinishedInitBot()
{
	Log(lInfo) << "Synching ArrayBot UI";
    ReInitBotBtn->Action = ShutDownA;

    //Setup the wiggler
    mTheWiggler.setAmplitude(mWigglerAmplitudeE->getValue());
    mTheWiggler.setMaxVelocity(mWigglerVelocityE->getValue());
    mTheWiggler.setMaxAcceleration(mWigglerAccelerationE->getValue());
    mTheWiggler.assignMotors(mAB->getWhiskerUnit().getXMotor(), mAB->getWhiskerUnit().getYMotor());

}

//---------------------------------------------------------------------------
void __fastcall TMain::AppInBox(mlxStructMessage &msg)
{
    if(msg.lparam == NULL)
    {
        return;
    }

    try
    {
        ApplicationMessageEnum aMsg = msg.lparam->mMessageEnum;

        switch(aMsg)
        {
            case abSplashWasClosed:
                Log(lDebug2) << "Splash form sent message that it was closed";
                gSplashForm = NULL;
            break;

            case abSequencerUpdate:
                Log(lDebug2) << "Update sequencer shortcuts";
                mSequencerButtons->update();
            break;
            default:
            break ;
        }
	}
	catch(...)
	{
		Log(lError) << "Received an unhandled windows message!";
	}
}

//---------------------------------------------------------------------------
void __fastcall TMain::UIUpdateTimerTimer(TObject *Sender)
{
  	//TODO: Clean up joystick mess..

	//Check if Joystick is working and update radiogroup if not
	if(mJoyStickRG->ItemIndex != mAB->getJoyStick().getID())
    {
    	int indx = mAB->getJoyStick().getID();
        if(indx != -1)
        {
			mJoyStickRG->ItemIndex = indx;
        }
    }

	int indx = mJoyStickRG->ItemIndex;

    //Check validity
    if(!mAB->getJoyStick().isValid())
    {
        mJSStatusL->Caption = "Current joystick could not be found!";
        mJSCSBtn->Enabled = false;
    }
    else
    {
        mJSStatusL->Caption = "";
        mJSCSBtn->Enabled = true;
       	mJSCSBtn->Caption = (mAB->getJoyStick().isEnabled()) ? "Disable JS" : "Enable JS";
    }

   	mASStartBtn->Caption 			= mPufferArduinoClient.isConnected()	? "Stop" : "Start";
	mArduinoServerPortE->Enabled 	= !mPufferArduinoClient.isConnected();
}

//---------------------------------------------------------------------------
void __fastcall TMain::mUnitControlRGClick(TObject *Sender)
{
	if(mUnitControlRG->ItemIndex == 0)//Both W and CS
    {
        mAB->enableCoverSlipUnit();
        mAB->enableWhiskerUnit();
    }
    else if(mUnitControlRG->ItemIndex == 1)//Only CS
    {
        mAB->enableCoverSlipUnit();
        mAB->disableWhiskerUnit();
    }
    else if(mUnitControlRG->ItemIndex == 2)//Only Z
    {
        mAB->disableCoverSlipUnit();
        mAB->enableWhiskerUnit();
    }
    else
    {
        mAB->disableCoverSlipUnit();
        mAB->disableWhiskerUnit();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::PageControl1Change(TObject *Sender)
{
	//Check what tab got selected
	if(PageControl1->TabIndex == pcMoveSequences)
    {
    	//Reload the currently selected sequence
		mABProcessSequencerFrame->mSequencesCBChange(Sender);
    }

    else if(PageControl1->TabIndex == pcMain)
    {
        mSequencesPanel->Parent = mFrontPage;
    }
    else if(PageControl1->TabIndex == pcMotors)
    {
    	//
    }

	else if(PageControl1->TabIndex == pcAbout)
    {
		TAboutArrayBotFrame_21->populate();
    }
}

void __fastcall TMain::mRightPanelDblClick(TObject *Sender)
{
	this->BorderStyle = (this->BorderStyle == bsNone) ? bsSizeable : bsNone;
}

void TMain::onArduinoMessageReceived(const string& msg)
{
	struct TLocalArgs
    {
        string msg;
        void __fastcall onPufferArduinoMessage()
        {
        }
    };

    TLocalArgs args;
    args.msg = msg;

    //This causes this function to be called in the UI thread
	TThread::Synchronize(NULL, &args.onPufferArduinoMessage);
}

//---------------------------------------------------------------------------
void __fastcall TMain::mASStartBtnClick(TObject *Sender)
{
	if(mASStartBtn->Caption == "Start")
    {
    	mPufferArduinoClient.connect(mArduinoServerPortE->getValue());
        mASStartBtn->Caption == "Connecting";
    }
    else
    {
    	mPufferArduinoClient.disConnect();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMain::mWiggleBtnClick(TObject *Sender)
{
	//Start/Stop wiggle timer
    if(!mTheWiggler.isRunning())
    {
        mAB->disableJoyStickAxes();
        Log(lInfo) << "Wiggler Center Position: "<<mTheWiggler.getCenterPosition();
        mTheWiggler.startWiggle();
		mWiggleBtn->Caption = "Stop Wiggle";
    }
    else
    {
        mTheWiggler.stopWiggle();
	    mAB->getWhiskerUnit().getXMotor()->stop();
        mAB->enableJoyStickAxes();
    	mWiggleBtn->Caption = "Start Wiggle";
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::mWiggleSpinButtonDownClick(TObject *Sender)
{
	mWigglerAmplitudeE->setValue(mWigglerAmplitudeE->getValue() - mWigglerAmplitudeStepE->getValue());
    if(mWigglerAmplitudeE->getValue() < 0)
    {
		mWigglerAmplitudeE->setValue(0.0);
    }

    mWigglerAmplitudeE->update();
}

//---------------------------------------------------------------------------
void __fastcall TMain::mWiggleSpinButtonUpClick(TObject *Sender)
{
	mWigglerAmplitudeE->setValue(mWigglerAmplitudeE->getValue() + mWigglerAmplitudeStepE->getValue());
    mWigglerAmplitudeE->update();
}

//---------------------------------------------------------------------------
void __fastcall TMain::mPullRibbonBtnClick(TObject *Sender)
{

    int ii = mPullCB->ItemIndex;
	if(mPullCB->ItemIndex == -1)
    {
    	return;
    }

	double step = mPullCB->Items->Strings[ii].ToDouble();

    TArrayBotButton* b = dynamic_cast<TArrayBotButton*>(Sender);

    if(b == mPullRibbonBtn)
    {
    	mTheWiggler.pull(step);
    }
    else
    {
    	mTheWiggler.relax(step);
    }
}



