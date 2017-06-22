#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "TMemoLogger.h"
#include "TSplashForm.h"
#include "TXYZUnitFrame.h"
#include "TXYZPositionsFrame.h"
#include "arraybot/apt/atAPTMotor.h"


extern TSplashForm*  	gSplashForm;
extern bool             gAppIsStartingUp;

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

//---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject *Sender)
{
	enableDisableUI(false);

	this->Visible = true;
	setupWindowTitle();

    enableDisableArrayCamClientControls(false);

    //Init pagecontrols
	PageControl1->TabIndex = 0;
    PageControl2->TabIndex = 0;


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
    TApplicationSoundsFrame1->populate(mSoundProperties);

    UIUpdateTimer->Enabled = true;
	gAppIsStartingUp = false;
}

void __fastcall	TMain::setupUIFrames()
{
    //Create frames showing motor positions
    TXYZPositionsFrame* f1 = new TXYZPositionsFrame(this, mAB.getCoverSlipUnit());
    f1->Parent = this->mRightPanel;
    f1->Align = alBottom;

    TXYZPositionsFrame* f2 = new TXYZPositionsFrame(this, mAB.getWhiskerUnit());
    f2->Parent = this->mRightPanel;
    f2->Align = alBottom;

    this->mSequencesPanel->Top = 0;
    this->mSequencesPanel->Refresh();

	//Setup JoyStick;

    //Over ride joysticks button events  (cycle speeds and XY motions)
    mAB.getJoyStick().setButtonEvents(5,  NULL, onJSButton5Click);
    mAB.getJoyStick().setButtonEvents(6,  NULL, onJSButton6Click);

    //!Button 14 emergency stop
    mAB.getJoyStick().setButtonEvents(14, NULL, onJSButton14Click);

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
        mLiftCB->Items->AddObject(pm->mLabel.c_str(), (TObject*) pm);
        pm = pms.getNext();
    }

    mLiftCB->ItemIndex = 0;
    mLiftCB->OnChange(NULL);

	//Create and setup XYZ unit frames
    mXYZUnitFrame1 = new TXYZUnitFrame(this);
    mXYZUnitFrame1->assignUnit(&mAB.getCoverSlipUnit());
    mXYZUnitFrame1->Parent = ScrollBox1;
    mXYZUnitFrame1->Left = 10;

    mXYZUnitFrame2 = new TXYZUnitFrame(this);
    mXYZUnitFrame2->assignUnit(&mAB.getWhiskerUnit());
    mXYZUnitFrame2->Parent = ScrollBox1;
    mXYZUnitFrame2->Left = 10;
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
}

