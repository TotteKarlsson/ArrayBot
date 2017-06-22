#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "TMemoLogger.h"
#include "TSplashForm.h"

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
