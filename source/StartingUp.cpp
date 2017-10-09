#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "TMemoLogger.h"
#include "TSplashForm.h"
#include "TXYZUnitFrame.h"
#include "TXYZPositionsFrame.h"
#include "arraybot/apt/atAPTMotor.h"
#include "TSequencerButtonsFrame.h"
#include "frames/TABProcessSequencerFrame.h"
#include "UIUtilities.h"
#include "mtkVCLUtils.h"
//---------------------------------------------------------------------------
extern TSplashForm*  	gSplashForm;
extern bool             gAppIsStartingUp;
extern string           gAppDataFolder;


//---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject *Sender)
{
	this->ReadRegistry();
	enableDisableUI(false);

	this->Visible = true;
	setupWindowTitle();

    enableDisableArrayCamClientControls(false);

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

	gLogger.setLogLevel(mLogLevel);

	if(mLogLevel == lInfo)
	{
		LogLevelCB->ItemIndex = 0;
	}
	else if(mLogLevel == lAny)
	{
		LogLevelCB->ItemIndex = 1;
	}

	//Try to connect to the arraycam app server..
	mArrayCamClient.connect(50001);

	TMemoLogger::mMemoIsEnabled = true;

    //Populate misc frames
	TSoundsFrame1->populate();
    ApplicationSoundsFrame1->populate(mSoundProperties);

    UIUpdateTimer->Enabled = true;

    //Init pagecontrols
	MainPC->TabIndex = 0;
    PageControl2->TabIndex = 0;

	gAppIsStartingUp = false;
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormShow(TObject *Sender)
{

}

void TMain::setupProperties()
{
	//Setup UI properties
    mProperties.setSection("UI");
	mProperties.setIniFile(&mIniFile);

	mProperties.add((BaseProperty*)  &mLogLevel.setup( 	                    		"LOG_LEVEL",    	                lAny));
	mProperties.add((BaseProperty*)  &mArrayCamServerPortE->getProperty()->setup(	"ARRAY_CAM_SERVER_PORT",     		50001));
	mProperties.add((BaseProperty*)  &mWigglerAmplitudeStepE->getProperty()->setup(	"WIGGLER_AMPLITUDE",    	 		0.5));
	mProperties.add((BaseProperty*)  &mWigglerAmplitudeE->getProperty()->setup(		"WIGGLER_AMPLITUDE_STEP",    		0.1));
	mProperties.add((BaseProperty*)  &mPullRelaxVelocityE->getProperty()->setup(	"WIGGLER_PULL_RELAX_VELOCITY",   	0.5));
	mProperties.add((BaseProperty*)  &mPullRelaxAccE->getProperty()->setup(			"WIGGLER_PULL_RELAX_ACCELERATION",  0.1));

    mSoundProperties.setSection("SOUNDS");
	mSoundProperties.setIniFile(&mIniFile);
	mSoundProperties.add((BaseProperty*)  &mEnableSlowSpeedSound.setup( 	      	"ENABLE_SLOW_SPEED_SOUND",       ApplicationSound("BUTTON_CLICK_1")));
	mSoundProperties.add((BaseProperty*)  &mEnableMediumSpeedSound.setup( 	      	"ENABLE_MEDIUM_SPEED_SOUND",     ApplicationSound("BUTTON_CLICK_1")));
	mSoundProperties.add((BaseProperty*)  &mEnableFastSpeedSound.setup( 	      	"ENABLE_FAST_SPEED_SOUND",       ApplicationSound("BUTTON_CLICK_1")));
	mSoundProperties.add((BaseProperty*)  &mMainPageControlChangeSound.setup( 	   	"MAIN_PC_CHANGE_SOUND", 	     ApplicationSound("BUTTON_CLICK_1")));
}

void __fastcall	TMain::setupUIFrames()
{
    //Create MoveSequencer frame
    mABProcessSequencerFrame = new TABProcessSequencerFrame(mProcessSequencer, gAppDataFolder, mMoveSequencesPage);
    mABProcessSequencerFrame->Parent = mMoveSequencesPage;
    mABProcessSequencerFrame->Align = alClient;
    mABProcessSequencerFrame->init();

    //The sequencer buttons frame holds shortcut buttons for preprogrammed sequences
    //setupShortCutButtonsAndFrames();

    //Create frames showing motor positions
    TXYZPositionsFrame* f1 = new TXYZPositionsFrame(this, mAB.getCoverSlipUnit());
    f1->Parent = this->mRightPanel;
    f1->Align = alTop;

    TXYZPositionsFrame* f2 = new TXYZPositionsFrame(this, mAB.getWhiskerUnit());
    f2->Parent = this->mRightPanel;
    f2->Align = alTop;

	//Setup JoyStick;

    //Over ride joysticks button events  (cycle speeds and XY motions)
    //5 and 7, control the zoom
    mAB.getJoyStick().setButtonEvents(5,  onJSButton5Down, NULL);
    mAB.getJoyStick().setButtonEvents(7,  onJSButton7Down, NULL);

    //Cycle speeds
    mAB.getJoyStick().setButtonEvents(6,  onJSButton6Click, NULL);

    //!Button 14: emergency stop
    mAB.getJoyStick().setButtonEvents(14, onJSButton14Click, NULL);

    //JoyStick Settings CB
    JoyStickSettings& js = mAB.getJoyStickSettings();
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
	mAB.enableJoyStick();

    //XY velocity parameters
    mMaxXYJogVelocityJoystick->setValue(mAB.getJoyStick().getX1Axis().getMaxVelocity());
    mXYJogAccelerationJoystick->setValue(mAB.getJoyStick().getX1Axis().getAcceleration());

    if(mAB.getCoverSlipUnit().getZMotor())
    {
        mMaxZJogVelocityJoystick->setValue(mAB.getCoverSlipUnit().getZMotor()->getVelocity());
        mZJogAccelerationJoystick->setValue(mAB.getCoverSlipUnit().getZMotor()->getAcceleration());
    }

    //Lift Settings CB
    PairedMoves& pms = mAB.getLiftMoves();
    PairedMove* pm = pms.getFirst();
    while(pm)
    {
        string key = pm->mLabel;
        LiftCB1->Items->AddObject(pm->mLabel.c_str(), (TObject*) pm);
        LiftCB2->Items->AddObject(pm->mLabel.c_str(), (TObject*) pm);
        pm = pms.getNext();
    }

    LiftCB2->ItemIndex = 0;
    LiftCB2->OnChange(NULL);

	//Create and setup XYZ unit frames
    mXYZUnitFrame1 = new TXYZUnitFrame(this);
    mXYZUnitFrame1->assignUnit(&mAB.getCoverSlipUnit());
    mXYZUnitFrame1->Parent = ScrollBox1;

    mXYZUnitFrame2 = new TXYZUnitFrame(this);
    mXYZUnitFrame2->assignUnit(&mAB.getWhiskerUnit());
    mXYZUnitFrame2->Parent = ScrollBox1;
    mXYZUnitFrame2->Top = mXYZUnitFrame1->Top + mXYZUnitFrame1->Height;
}

void __fastcall	TMain::onFinishedInitBot()
{
	Log(lInfo) << "Synching ArrayBot UI";
    ReInitBotBtn->Action = ShutDownA;

    //Setup the wiggler
    mTheWiggler.setAmplitude(mWigglerAmplitudeE->getValue());
    mTheWiggler.setMaxVelocity(mWigglerVelocityE->getValue());
    mTheWiggler.setMaxAcceleration(mWigglerAccelerationE->getValue());
    mTheWiggler.assignMotors(mAB.getWhiskerUnit().getXMotor(), mAB.getWhiskerUnit().getYMotor());
	setupShortCutButtonsAndFrames();

}

void __fastcall	TMain::setupShortCutButtonsAndFrames()
{
    CategoryPanelGroup1->ExpandAll();
    mSequencerButtons1 = new TSequencerButtonsFrame(mProcessSequencer, "Cutting", MiddlePanel);
    mSequencerButtons1->Parent = CategoryPanel1;
    CategoryPanel1->InsertComponent(mSequencerButtons1);
    mSequencerButtons1->Align = alClient;
    CategoryPanel1->Caption = vclstr(mSequencerButtons1->getCategory());

    mSequencerButtons2 = new TSequencerButtonsFrame(mProcessSequencer, "UC7", MiddlePanel);
    mSequencerButtons2->Parent = CategoryPanel2;
    CategoryPanel2->InsertComponent(mSequencerButtons2);
    mSequencerButtons2->Align = alClient;
    CategoryPanel2->Caption = vclstr(mSequencerButtons2->getCategory());

    mSequencerButtons3 = new TSequencerButtonsFrame(mProcessSequencer, "Camera", MiddlePanel);
    mSequencerButtons3->Parent = CategoryPanel3;
    CategoryPanel3->InsertComponent(mSequencerButtons3);
    mSequencerButtons3->Align = alClient;
    CategoryPanel3->Caption = vclstr(mSequencerButtons3->getCategory());

    mSequencerButtons4 = new TSequencerButtonsFrame(mProcessSequencer, "Setup", MiddlePanel);
    mSequencerButtons4->Parent = CategoryPanel4;
    CategoryPanel4->InsertComponent(mSequencerButtons4);
    mSequencerButtons4->Align = alClient;
    CategoryPanel4->Caption = vclstr(mSequencerButtons4->getCategory());

    mSequencerButtons5 = new TSequencerButtonsFrame(mProcessSequencer, "Testing", MiddlePanel);
    mSequencerButtons5->Parent = CategoryPanel5;
    CategoryPanel5->InsertComponent(mSequencerButtons5);
    mSequencerButtons5->Align = alClient;
    CategoryPanel5->Caption = vclstr(mSequencerButtons5->getCategory());

    mSequenceButtonsFrames.push_back(mSequencerButtons1);
    mSequenceButtonsFrames.push_back(mSequencerButtons2);
    mSequenceButtonsFrames.push_back(mSequencerButtons3);
    mSequenceButtonsFrames.push_back(mSequencerButtons4);
    mSequenceButtonsFrames.push_back(mSequencerButtons5);

	mSequenceCategoryPanels.push_back(CategoryPanel1);
	mSequenceCategoryPanels.push_back(CategoryPanel2);
	mSequenceCategoryPanels.push_back(CategoryPanel3);
	mSequenceCategoryPanels.push_back(CategoryPanel4);
	mSequenceCategoryPanels.push_back(CategoryPanel5);
}

