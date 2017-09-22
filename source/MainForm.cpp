#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "TMemoLogger.h"
#include "TSplashForm.h"
#include "mtkStringList.h"
#include "core/atUtilities.h"
#include "arraybot/apt/atAPTMotor.h"
#include "arraybot/apt/atTCubeDCServo.h"
#include "mtkVCLUtils.h"
#include "mtkLogger.h"
#include <bitset>
#include "mtkMathUtils.h"
#include "core/atExceptions.h"
#include "sound/atSounds.h"
#include "core/atCore.h"
#include "frames/TABProcessSequencerFrame.h"
#include "frames/TXYZPositionsFrame.h"
#include "frames/TXYZUnitFrame.h"
#include "frames/TSequencerButtonsFrame.h"
#include "UIUtilities.h"
#include "arraybot/apt/atGeneralIPCMessageData.h"
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
#pragma link "TSoundsFrame"
#pragma link "TApplicationSoundsFrame"
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
	mLogFileReader(joinPath(gAppDataFolder, gLogFileName), &logMsg),
    mInitBotThread(),
    mIniFile(joinPath(gAppDataFolder, "ArrayBot.ini"), true, true),
    mLogLevel(lAny),
    mEnableSlowSpeedSound(ApplicationSound("")),
    mEnableMediumSpeedSound(ApplicationSound("")),
    mEnableFastSpeedSound(ApplicationSound("")),
	mMainPageControlChangeSound(ApplicationSound("")),
    mArrayCamClient(),
    mAB(mIniFile, gAppDataFolder),
    mProcessSequencer(mAB, mArrayCamClient, gAppDataFolder),
	mABProcessSequencerFrame(NULL),
    mSequencerButtons1(NULL),
    mSequencerButtons2(NULL),
    mSequencerButtons3(NULL),
    mSequencerButtons4(NULL),
    mSequencerButtons5(NULL),
    mTheWiggler(NULL, NULL)
{
    //Init the CoreLibDLL -> give intra messages their ID's
	initABCoreLib();

	TMemoLogger::mMemoIsEnabled = false;
   	mLogFileReader.start(true);

    setupProperties();

    mProperties.read();
    mSoundProperties.read();

    //Give all sounds a Handle
  	mEnableSlowSpeedSound.getReference().setHandle(this->Handle);
  	mEnableMediumSpeedSound.getReference().setHandle(this->Handle);
  	mEnableFastSpeedSound.getReference().setHandle(this->Handle);
	mMainPageControlChangeSound.getReference().setHandle(this->Handle);

	mArrayCamServerPortE->update();
	mWigglerAmplitudeE->update();
	mWigglerAmplitudeStepE->update();

	mPullRelaxVelocityE->update();
	mPullRelaxAccE->update();

	//Load motors in a thread
    mInitBotThread.assingBot(&mAB);
    mInitBotThread.onFinishedInit = this->onFinishedInitBot;

    //We will setup UI frames after the bot is initialized
	mInitBotThread.start();

	WaitForDeviceInitTimer->Enabled = true;

    mTheWiggler.mMaxVelocity.setReference(&mWigglerVelocityE->getReference());
    mTheWiggler.mAmplitude.setReference(&mWigglerAmplitudeE->getReference());
    mTheWiggler.mMaxAcceleration.setReference(&mWigglerAccelerationE->getReference());

    mTheWiggler.mPullRelaxVelocity.setReference(&mPullRelaxVelocityE->getReference());
    mTheWiggler.mPullRelaxAcceleration.setReference(&mPullRelaxAccE->getReference());

	mArrayCamClient.assignOnMessageReceivedCallBack(onArrayCamMessageReceived);
    mArrayCamClient.onConnected 				= onArrayCamClientConnected;
	mArrayCamClient.onDisconnected 				= onArrayCamClientDisconnected;
}

void TMain::enableDisableUI(bool e)
{
	MainPC->Visible = e;
	enableDisablePanel(mRightPanel, e);
	enableDisablePanel(MiddlePanel, e);
    enableDisableGroupBox(JSGB, e);
}

void __fastcall TMain::WndProc(TMessage& Message)
{
    if (Message.Msg == getABCoreMessageID("MOTOR_WARNING_MESSAGE") && getABCoreMessageID("MOTOR_WARNING_MESSAGE") != 0)
    {
    	MotorMessageData* msg = reinterpret_cast<MotorMessageData*>(Message.WParam);
       	APTMotor* mtr = mAB.getMotorWithSerial(msg->mSerial);

        if(!mtr)
        {
        	//real bad....
            Log(lError) << "Got Motor warning message, but motor not present!";
			return;
        }

		//Handle the warning..
        if(msg->mCurrentPosition >= msg->mPositionLimits.getValue().getMax())
        {
            if(mtr)
            {
            	if(mtr->getLastCommand() != mcStopHard)
                {
            		mtr->stop();
	                //playABSound(absMotorWarning);
    	            Log(lInfo) << "Stopped motor: "<<mtr->getName();
                }
            }
        }

        if(mtr->isInDangerZone())
        {
        	//playABSound(absMotorWarning);
        }

        delete msg;
    }
    else if(Message.Msg == getABCoreMessageID("INFO_MESSAGE_DIALOG") && getABCoreMessageID("INFO_MESSAGE_DIALOG") != 0)
    {
       	GeneralIPCMessageData* msg = reinterpret_cast<GeneralIPCMessageData*>(Message.WParam);
    	//We are to show a dialog box..
        MessageDlg(msg->mContent.c_str(), mtInformation, TMsgDlgButtons() << mbOK, 0);
        delete  msg;
    }
    else
    {
        TForm::WndProc(Message);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::WaitForDeviceInitTimerTimer(TObject *Sender)
{
	if(!mInitBotThread.isRunning()) //Not waiting for devices any more
    {
		WaitForDeviceInitTimer->Enabled = false;

        setupUIFrames();
        enableDisableUI(true);
       //Send a message to main ui to update sequence shortcuts
        if(sendAppMessage(abSequencerUpdate) != true)
        {
            Log(lDebug)<<"Sending sequencer update to UI was unsuccesful";
        }
    }
}

void __fastcall TMain::reInitBotAExecute(TObject *Sender)
{
	mAB.initialize();

    if(mXYZUnitFrame1)
    {
		mXYZUnitFrame1->assignUnit(&mAB.getCoverSlipUnit());
    }

    if(mXYZUnitFrame2)
    {
		mXYZUnitFrame2->assignUnit(&mAB.getWhiskerUnit());
    }

    //ArrayBotJoyStick stuff.....
    mMaxXYJogVelocityJoystick->setValue(mAB.getJoyStick().getX1Axis().getMaxVelocity());
    mXYJogAccelerationJoystick->setValue(mAB.getJoyStick().getX1Axis().getAcceleration());

    if(mAB.getCoverSlipUnit().getZMotor())
    {
    	mMaxZJogVelocityJoystick->setValue(mAB.getCoverSlipUnit().getZMotor()->getVelocity());
    	mZJogAccelerationJoystick->setValue(mAB.getCoverSlipUnit().getZMotor()->getAcceleration());
    }

    ReInitBotBtn->Action = ShutDownA;
}

void __fastcall TMain::stopAllAExecute(TObject *Sender)
{
	mAB.stopAll();
    mTheWiggler.stopWiggle();
}

//---------------------------------------------------------------------------
void __fastcall TMain::LiftTimerTimer(TObject *Sender)
{
	if(mAB.isActive())
    {
    	LiftBtn->Action = abortLiftA;
    }
    else
    {
    	LiftBtn->Action = liftA;
		LiftTimer->Enabled = false;

    	//Re-enable the joystick.
		mAB.enableJoyStick();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::abortLiftAExecute(TObject *Sender)
{
	mAB.stopAll();
    Log(lInfo) << "The lift was aborted";

    //Re-enable the joystick.
	mAB.enableJoyStick();
}

PairedMove* TMain::getCurrentPairedMove(TComboBox* cb)
{
	if(cb != NULL)
    {
        if(cb->ItemIndex > -1)
        {
            return (PairedMove*) cb->Items->Objects[cb->ItemIndex];
        }
    }
    return NULL;
}

//---------------------------------------------------------------------------
void __fastcall TMain::liftAExecute(TObject *Sender)
{
	PairedMove* pm = getCurrentPairedMove(LiftCB2);

    pm->assignMotor1(mAB.getCoverSlipUnit().getZMotor());
    pm->assignMotor2(mAB.getWhiskerUnit().getZMotor());
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
	mAB.disableJoyStick();
    pm->execute();
    LiftTimer->Enabled = true;
   	LiftBtn->Action = abortLiftA;
}

//---------------------------------------------------------------------------
void __fastcall TMain::LiftCBChange(TObject *Sender)
{
	TComboBox* cb = dynamic_cast<TComboBox*>(Sender);

    if(cb == LiftCB1)
    {
        //Update edits
        //Assign editbox references to Lifting parameters
        PairedMove* pm = getCurrentPairedMove(cb);
        if(pm)
        {
            mMoveVelocityVerticalE->setReference(pm->mVelocity);
            mMoveAccelerationE->setReference(pm->mAcceleration);
        }
    }
    else if(cb == LiftCB2)
    {

    }
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
                updateAllSequenceButtons();
            break;

            case abSequencerUpdate:
                Log(lDebug2) << "Update sequencer shortcuts";
                updateAllSequenceButtons();
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
	if(mJoyStickRG->ItemIndex != mAB.getJoyStick().getID())
    {
    	int indx = mAB.getJoyStick().getID();
        if(indx != -1)
        {
			mJoyStickRG->ItemIndex = indx;
        }
    }

	int indx = mJoyStickRG->ItemIndex;

    //Check validity
    if(!mAB.getJoyStick().isValid())
    {
        mJSStatusL->Caption = "Current joystick could not be found!";
        mJSCSBtn->Enabled = false;
    }
    else
    {
        mJSStatusL->Caption = "";
        mJSCSBtn->Enabled = true;
       	mJSCSBtn->Caption = (mAB.getJoyStick().isEnabled()) ? "Disable JS" : "Enable JS";
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::mUnitControlRGClick(TObject *Sender)
{
	if(mUnitControlRG->ItemIndex == 0)//Both W and CS
    {
        mAB.enableCoverSlipUnit();
        mAB.enableWhiskerUnit();
    }
    else if(mUnitControlRG->ItemIndex == 1)//Only CS
    {
        mAB.enableCoverSlipUnit();
        mAB.disableWhiskerUnit();
    }
    else if(mUnitControlRG->ItemIndex == 2)//Only Z
    {
        mAB.disableCoverSlipUnit();
        mAB.enableWhiskerUnit();
    }
    else
    {
        mAB.disableCoverSlipUnit();
        mAB.disableWhiskerUnit();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::MainPCChange(TObject *Sender)
{
	//Check what tab got selected
	if(MainPC->TabIndex == pcMoveSequences && mABProcessSequencerFrame != NULL)
    {
    	//Reload the currently selected sequence
		mABProcessSequencerFrame->mSequencesCBChange(Sender);
    }

    else if(MainPC->TabIndex == pcMain)
    {
        updateAllSequenceButtons();

    }
    else if(MainPC->TabIndex == pcMotors)
    {
		//Disable joystick
	 	mAB.disableJoyStick();

        //Disable motor status timers
        mXYZUnitFrame1->enable();
        mXYZUnitFrame2->enable();
    }

	else if(MainPC->TabIndex == pcAbout)
    {
		TAboutArrayBotFrame_21->populate();
    }

    if(MainPC->TabIndex != pcMotors)
    {
   	 	mAB.enableJoyStick();

        //Disable motor status timers
        mXYZUnitFrame1->disable();
        mXYZUnitFrame2->disable();
    }

    mMainPageControlChangeSound.getReference().play();
}

//---------------------------------------------------------------------------
void __fastcall TMain::mASStartBtnClick(TObject *Sender)
{
	if(mASStartBtn->Caption == "Connect")
    {
    	mArrayCamClient.connect(mArrayCamServerPortE->getValue());
        mASStartBtn->Caption == "Connecting";
    }
    else
    {
    	mArrayCamClient.disConnect();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::HomeAllDevicesAExecute(TObject *Sender)
{
	if(MessageDlg("ATTENTION: Make sure all motors have a free path to their home position before executing!", mtWarning, TMsgDlgButtons() << mbOK<<mbCancel, 0) == mrOk)
    {
		mAB.homeAll();
    }
}

void __fastcall TMain::updateAllSequenceButtons()
{
	for(int i = 0; i < mSequenceButtonsFrames.size(); i++)
    {
	    mSequenceButtonsFrames[i]->update();
    }

	updateForCategoryPanelGlitch();
}

void __fastcall TMain::CategoryPanelExpand(TObject *Sender)
{
	TCategoryPanel* p = dynamic_cast<TCategoryPanel*>(Sender);

	//Update frame content
    if(p)
    {
	    for(int i = 0; i < p->ComponentCount; i++)
        {
        	TComponent* c = CategoryPanel1->Components[i];
        	TSequencerButtonsFrame* f = dynamic_cast<TSequencerButtonsFrame*>(c);

            if(f)
            {
            	f->update();
            }
        }
    }

    //Update for categorypanel glitch
	updateForCategoryPanelGlitch();
}

void __fastcall TMain::updateForCategoryPanelGlitch()
{
    for(int i = 0; i < mSequenceCategoryPanels.size(); i++)
    {
    	TCategoryPanel* p = mSequenceCategoryPanels[i];
        if(p && !p->Collapsed)
        {
            p->Left = 1;
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::CategoryPanelCollapse(TObject *Sender)
{
	updateForCategoryPanelGlitch();
}

//---------------------------------------------------------------------------
void __fastcall TMain::CollapseAll1Click(TObject *Sender)
{
	CategoryPanelGroup1->CollapseAll();
}

//---------------------------------------------------------------------------
void __fastcall TMain::ExpandAll1Click(TObject *Sender)
{
	CategoryPanelGroup1->ExpandAll();
}


