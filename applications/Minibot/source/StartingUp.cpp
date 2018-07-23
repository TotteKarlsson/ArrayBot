#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslTMemoLogger.h"
#include "forms/TSplashForm.h"
#include "TXYZUnitFrame.h"
#include "TXYZPositionsFrame.h"
#include "arraybot/apt/atAPTMotor.h"
#include "TSequencerButtonsFrame.h"
#include "frames/TABProcessSequencerFrame.h"
#include "UIUtilities.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "TPGDataModule.h"
using namespace dsl;
//---------------------------------------------------------------------------
extern TSplashForm*  	gSplashForm;
extern bool             gAppIsStartingUp;
extern string           gAppDataFolder;
extern string           gAppName;

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	this->readRegistry();
	enableDisableUI(false);

	this->Visible = true;
	setupWindowTitle();

    //Populate misc frames
	TSoundsFrame1->populate();
    TApplicationSoundsFrame1->populate(mSoundProperties);


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

	TMemoLogger::mMemoIsEnabled = true;
    UIUpdateTimer->Enabled = true;

    //Init pagecontrols
	MainPC->TabIndex = 0;
	gAppIsStartingUp = false;
    this->SetFocus();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
	//Setup DB callbacks
    if(pgDM && pgDM->SQLConnection1)
    {
    	pgDM->SQLConnection1->AfterConnect 		= afterDBServerConnect;
	    pgDM->SQLConnection1->AfterDisconnect 	= afterDBServerDisconnect;
    }

	BarcodeLbl->Caption = "";

    //Set UC7 stop mode
    StopOptionsRG->ItemIndex = mStopCutterMode;
    enableDisableUC7UI(false);
    BarcodeLbl->Caption = "";
    enableDisableGroupBox(mImagerSettingsGB, false);
	populateStyleRG(ThemesRG);
	mStartupTimer->Enabled = true;
}

void TMainForm::setupProperties()
{
	//Setup UI/INI properties
    mGeneralProperties.setSection("GENERAL");
	mGeneralProperties.setIniFile(&mIniFile);

	mGeneralProperties.add((BaseProperty*)  &mLogLevel.setup( 	    	                    "LOG_LEVEL",    					lAny));
	mGeneralProperties.add((BaseProperty*)  &mDBUserID.setup( 	                    	    "ATDB_USER_ID",                    	0));

	mGeneralProperties.add((BaseProperty*)  &mBlockID.setup( 	                   		    "BLOCK_ID",                  		0));
	mGeneralProperties.add((BaseProperty*)  &mKnifeID.setup( 	                   		    "KNIFE_ID",                  		0));
	mGeneralProperties.add((BaseProperty*)  &mLocalDBName.setup(		                    "LOCAL_DB",   			            "umlocal.db"));


    //UC7
   	mGeneralProperties.add((BaseProperty*)  &mUC7COMPort.setup( 	                        "UC7_COM_PORT",    	   				0));
	mGeneralProperties.add((BaseProperty*)  &mCountToE->getProperty()->setup(       	    "COUNT_TO",                     	5));
	mGeneralProperties.add((BaseProperty*)  &mZeroCutsE->getProperty()->setup(      	    "NUMBER_OF_ZERO_CUTS",           	2));
	mGeneralProperties.add((BaseProperty*)  &mStopCutterMode.setup(    					    "STOP_CUTTER_MODE",					1));

	mGeneralProperties.add((BaseProperty*)  &mStageMoveDelayE->getProperty()->setup(	    "KNIFE_STAGE_MOVE_DELAY",          	10));
	mGeneralProperties.add((BaseProperty*)  &mPresetFeedRateE->getProperty()->setup(	    "PRESET_FEED_RATE",               	100));
	mGeneralProperties.add((BaseProperty*)  &mKnifeStageJogStep.setup(	    				"KNIFE_STAGE_JOG_SIZE",          	100));
	mGeneralProperties.add((BaseProperty*)  &mKnifeStageResumeDelta.setup(	    			"KNIFE_STAGE_RESUME_DELTA",        	0));

	mGeneralProperties.add((BaseProperty*)  &mKnifeStageMaxPos.setup(						"KNIFE_STAGE_MAX_POSITION",        	0));
	mGeneralProperties.add((BaseProperty*)  &PresetReturnSpeedE->getProperty()->setup(	    "PRESET_RETURN_SPEED",             	10));
	mGeneralProperties.add((BaseProperty*)  &SlowReturnSpeedE->getProperty()->setup(	    "SLOW_RETURN_SPEED",             	10));
	mGeneralProperties.add((BaseProperty*)  &UltraSlowReturnSpeedE->getProperty()->setup(   "ULTRA_SLOW_RETURN_SPEED",             	10));

    //Zebra
	mGeneralProperties.add((BaseProperty*)  &mZebraCOMPort.setup( 	                    	"ZEBRA_COM_PORT",                   0));
	mGeneralProperties.add((BaseProperty*)  &mZebraBaudRate.setup( 	                		"ZEBRA_BAUD_RATE",                  9600));

    mSoundProperties.setSection("SOUNDS");
	mSoundProperties.setIniFile(&mIniFile);
	mSoundProperties.add((BaseProperty*)  &mKnifeBeforeCuttingSound.setup( 	           		"KNIFE_BEFORE_CUTTING_SOUND",       ApplicationSound("BUTTON_CLICK_1")));
	mSoundProperties.add((BaseProperty*)  &mKnifeCuttingSound.setup( 	               		"KNIFE_CUTTING_SOUND",              ApplicationSound("BUTTON_CLICK_1")));
	mSoundProperties.add((BaseProperty*)  &mKnifeAfterCuttingSound.setup( 	           		"KNIFE_AFTER_CUTTING_SOUND",        ApplicationSound("BUTTON_CLICK_1")));
	mSoundProperties.add((BaseProperty*)  &mArmRetractingSound.setup( 	           			"ARM_RETRACTING_SOUND",       		ApplicationSound("BUTTON_CLICK_1")));
	mSoundProperties.add((BaseProperty*)  &mBeforeKnifeBackOffSound.setup( 	           		"BEFORE_KNIFE_BACKOFF_SOUND",       ApplicationSound("SHORT_BEEP_1")));

}

void __fastcall	TMainForm::setupUIFrames()
{
    //Create MoveSequencer frame
    mABProcessSequencerFrame = new TABProcessSequencerFrame(mProcessSequencer, gAppDataFolder, SequencesTS);

    mABProcessSequencerFrame->Parent = SequencesTS;
    mABProcessSequencerFrame->Align = alClient;
    mABProcessSequencerFrame->init();

	//Create and setup XYZ unit frames
    mXYZUnitFrame1 = new TXYZUnitFrame(this);
    mXYZUnitFrame1->assignUnit(&mAB.getCoverSlipUnit());
    mXYZUnitFrame1->Parent = ScrollBox1;
    mXYZUnitFrame1->Left = 10;

    TAboutArrayBotFrame_21->AppNameLabel->Caption = vclstr(gAppName);
}

void __fastcall	TMainForm::onFinishedInitBot()
{
	Log(lInfo) << "Synching ArrayBot UI";
    ReInitBotBtn->Action = ShutDownA;

    //Get the motor and jog it
    APTMotor* m = mAB.getMotorWithName("COVERSLIP UNIT_Z");
    if(!m)
    {
    	Log(lError) << "Failed getting Coverslip UnitZ motor";
        return;
    }
    MotorPositionFrame1->assignMotor(m);
}


