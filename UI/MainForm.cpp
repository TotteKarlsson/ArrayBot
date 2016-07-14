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
#include "TSplashForm.h"
#include "TAboutArrayBotForm.h"
#include "TABProcessSequencerFrame.h"
#include "TXYZPositionsFrame.h"
#include "TRibbonLifterFrame.h"
#include "abXYZUnitFrame.h"
#include "TSequencerButtonsFrame.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntegerLabeledEdit"
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"
TMain *Main;

extern string           gLogFileLocation;
extern string           gLogFileName;
extern string           gAppDataFolder;
extern TSplashForm*  	gSplashForm;
extern bool             gAppIsStartingUp;
using namespace mtk;

//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
:
	TRegistryForm("Test", "MainForm", Owner),
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", gLogFileName), &logMsg),
    mIniFile(joinPath(gAppDataFolder, "ArrayBot.ini"), true, true),
    mLogLevel(lAny),
    mInitBotThread(),
	mABProcessSequencerFrame(NULL),
    mRibbonLifterFrame(NULL)
{
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

	//Setup UI properties
    mProperties.setSection("UI");
	mProperties.setIniFile(&mIniFile);
    mProperties.read();
	mProperties.add((BaseProperty*)  &mLogLevel.setup( 	                    "LOG_LEVEL",    	                lAny));

	//Load motors in a thread
    mInitBotThread.assingBot(mAB);
    mInitBotThread.onFinishedInit = this->onFinishedInitBot;

    //We will setup UI frames after the bot is initialized
	mInitBotThread.start();

	WaitForDeviceInitTimer->Enabled = true;
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
	setupWindowTitle();
	gAppIsStartingUp = false;

	TMemoLogger::mMemoIsEnabled = true;
	gSplashForm->mMainAppIsRunning = true;

	this->Visible = true;
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
	gLogger.setLogLevel(mLogLevel);

	if(mLogLevel == lInfo)
	{
		LogLevelCB->ItemIndex = 0;
	}
	else if(mLogLevel == lAny)
	{
		LogLevelCB->ItemIndex = 1;
	}

	TMemoLogger::mMemoIsEnabled = true;
    UIUpdateTimer->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TMain::WaitForDeviceInitTimerTimer(TObject *Sender)
{
	if(!mInitBotThread.isRunning()) //Not waiting for devices any more
    {
		WaitForDeviceInitTimer->Enabled = false;
        setupUIFrames();
    }
}

void __fastcall	TMain::setupUIFrames()
{
    //Init UI stuff here

    //Create frames showing motor positions
    TXYZPositionsFrame* f1 = new TXYZPositionsFrame(this, mAB->getCoverSlipUnit());
    f1->Parent = this->mTopMainPanel;
    f1->Align = alLeft;

    TXYZPositionsFrame* f2 = new TXYZPositionsFrame(this, mAB->getWhiskerUnit());
    f2->Parent = this->mTopMainPanel;
    f2->Align = alLeft;
    this->mTopMainPanel->Top = 0;


    //Over ride joysticks button events  (cycle speeds and XY motions)
    mAB->getJoyStick().setButtonEvents(5,  NULL, onJSButton5Click);
    mAB->getJoyStick().setButtonEvents(6,  NULL, onJSButton6Click);
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
    mJSCSBtn->Click();

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
    mXYZUnitFrame1->Parent = ScrollBox1;
    mXYZUnitFrame1->Align = alTop;

    mXYZUnitFrame2 = new TXYZUnitFrame(this);
    mXYZUnitFrame2->Parent = ScrollBox1;
    mXYZUnitFrame2->Align = alTop;

    mXYZUnitFrame1->assignUnit(&mAB->getCoverSlipUnit());
    mXYZUnitFrame2->assignUnit(&mAB->getWhiskerUnit());

    //Setup JoyStick
    //ArrayBotJoyStick stuff.....
    mMaxXYJogVelocityJoystick->setValue(mAB->getJoyStick().getX1Axis().getMaxVelocity());
    mXYJogAccelerationJoystick->setValue(mAB->getJoyStick().getX1Axis().getAcceleration());

    if(mAB->getCoverSlipUnit().getZMotor())
    {
        mMaxZJogVelocityJoystick->setValue(mAB->getCoverSlipUnit().getZMotor()->getVelocity());
        mZJogAccelerationJoystick->setValue(mAB->getCoverSlipUnit().getZMotor()->getAcceleration());
    }

    //Create MoveSequencer frame
    mABProcessSequencerFrame = new TABProcessSequencerFrame(*(mAB), gAppDataFolder, mMoveSequencesPage);
    mABProcessSequencerFrame->Parent = mMoveSequencesPage;
    mABProcessSequencerFrame->Align = alClient;
    mABProcessSequencerFrame->init();

	mSequencerButtons = new TSequencerButtonsFrame(*(mAB), mBottomPanel);
	mSequencerButtons->Parent = mBottomPanel;
    mSequencerButtons->Align = alClient;
	mSequencerButtons->update();


//    ProcessSequencer& psr = mAB->getProcessSequencer();
//    ProcessSequences& pss = psr.getSequences();
//    ProcessSequence*  ps = pss.getFirst();
//    while(ps)
//    {
//        TSpeedButton* btn = new TSpeedButton(this);
//        btn->Parent = mBottomPanel;
//        btn->Caption = vclstr(ps->getName());
//        btn->Align = alLeft;
//        btn->OnClick = runSequenceBtnClick;
//        btn->Font->Size = 14;
//        ps = pss.getNext();
//        btn->Width = mBottomPanel->Height;
//    }

    //Restore back to first sequence
//    ps = pss.getFirst();

    //Create the ribbon lifter frame
    mRibbonLifterFrame = new TRibbonLifterFrame((*mAB), mIniFile, this);
    mRibbonLifterFrame->Parent = RibbonLifterTabSheet;
    mRibbonLifterFrame->Align = alTop;
    mRibbonLifterFrame->OnClose = &FrameClosed;

    mRibbonLifterFrame->init();
}

void __fastcall TMain::runSequenceBtnClick(TObject *Sender)
{
	TSpeedButton* b = dynamic_cast<TSpeedButton*>(Sender);
    if(b)
    {
        ProcessSequencer& psr = mAB->getProcessSequencer();

        if(psr.selectSequence(stdstr(b->Caption)))
        {
      		mSequenceStatusTimer->Enabled = true;
            mAB->disableJoyStickAxes();
        	psr.start();
        }
    }
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

void __fastcall TMain::ShutDownAExecute(TObject *Sender)
{
    mAB->getJoyStick().disable();

    mXYZUnitFrame1->disable();
    mXYZUnitFrame2->disable();

    //The shutdown disconnects all devices
    mAB->shutDown();

	while(mAB->isActive())
    {
    	sleep(100);
    }

    ReInitBotBtn->Action = reInitBotA;
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
	//These are already referenced so no need for any updates
}

//---------------------------------------------------------------------------
void __fastcall TMain::JSControlClick(TObject *Sender)
{
	//Setup Joystick control
    TSpeedButton* btn = dynamic_cast<TSpeedButton*>(Sender);
    if(btn->Caption == "Enable JS")
    {
		if(!mAB->enableJoyStick())
        {
        	MessageDlg("Failed enabling the JoyStick. \r Please see the LogFile for Errors. \r JoyStick support is disabled for the rest of this session.", mtWarning, TMsgDlgButtons() << mbOK, 0);
            mJSCSBtn->Enabled = false;
        }
        mXYCtrlRG->ItemIndex = 0;
    }
    else
    {
	 	mAB->disableJoyStick();
    }
    btn->Caption = (mAB->getJoyStick().isEnabled()) ? "Disable JS" : "Enable JS";

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

	mAB->writeINIParameters();
    mIniFile.save();
}

//Save parameters
void __fastcall TMain::Button1Click(TObject *Sender)
{
	mAB->writeINIParameters();
    mIniFile.save();
}

//---------------------------------------------------------------------------
void __fastcall TMain::mXYCtrlRGClick(TObject *Sender)
{
	if(mXYCtrlRG->ItemIndex == 0)//Both X&Y
    {
        mAB->getJoyStick().getY1Axis().enable();
        mAB->getJoyStick().getY2Axis().enable();
        mAB->getJoyStick().getX1Axis().enable();
        mAB->getJoyStick().getX2Axis().enable();
    }
    else if(mXYCtrlRG->ItemIndex == 1)//Only X
    {
        mAB->getJoyStick().getX1Axis().enable();
        mAB->getJoyStick().getX2Axis().enable();
        mAB->getJoyStick().getY1Axis().disable();
        mAB->getJoyStick().getY2Axis().disable();
    }
    else if(mXYCtrlRG->ItemIndex == 2)//Only Z
    {
        mAB->getJoyStick().getY1Axis().enable();
        mAB->getJoyStick().getY2Axis().enable();
        mAB->getJoyStick().getX1Axis().disable();
        mAB->getJoyStick().getX2Axis().disable();
    }
    else
    {
        mAB->getJoyStick().getY1Axis().disable();
        mAB->getJoyStick().getY2Axis().disable();
        mAB->getJoyStick().getX1Axis().disable();
        mAB->getJoyStick().getX2Axis().disable();
    }
}

void TMain::onJSButton5Click()
{
	//Cycle xy setting
    if(mXYCtrlRG->ItemIndex < 3)
    {
    	mXYCtrlRG->ItemIndex++;
    }
    else
    {
	    mXYCtrlRG->ItemIndex = 0;
    }
}

void TMain::onJSButton6Click()
{
	//Check speed setting, go from slower to faster
	if(mJSSpeedSlowBtn->Down)
    {
	    mJSSpeedMediumBtn->Down = true;
		mJSSpeedMediumBtn->Click();
    }
	else if(mJSSpeedFastBtn->Down)
    {
	    mJSSpeedSlowBtn->Down = true;
		mJSSpeedSlowBtn->Click();
    }
	else if(mJSSpeedMediumBtn->Down)
    {
	    mJSSpeedFastBtn->Down = true;
		mJSSpeedFastBtn->Click();
    }
}

void TMain::onJSButton14Click()
{
    stopAllAExecute(NULL);
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

//---------------------------------------------------------------------------
void __fastcall TMain::mAboutBtnClick(TObject *Sender)
{
	//Show about frame
    TAboutArrayBotForm* af = new TAboutArrayBotForm(this);
    af->ShowModal();
    delete af;
}

void __fastcall	TMain::onFinishedInitBot()
{
	Log(lInfo) << "Synching arraybot with UI";
    ReInitBotBtn->Action = ShutDownA;
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

void __fastcall TMain::mSequenceStatusTimerTimer(TObject *Sender)
{
	if(mProcessSequencer && mProcessSequencer->isRunning())
    {

    }
    else
    {
		mSequenceStatusTimer->Enabled = false;
        mAB->enableJoyStickAxes();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::SwitchJSBtnClick(TObject *Sender)
{
	mAB->switchJoyStick();
}




