#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "database/atDBUtils.h"
#include "atVCLUtils.h"
#include "TPGDataModule.h"
#include "TNavitarPresetFrame.h"
#include "ArrayCamUtilities.h"
using namespace dsl;
using namespace at;

extern ArrayCamUtilities acu;

void TMainForm::setupProperties()
{
	//Setup UI/INI properties
    mGeneralProperties->setSection("GENERAL");
	mGeneralProperties->setIniFile(&mIniFile);

	mGeneralProperties->add((BaseProperty*)  &mLogLevel.setup( 	    	                    "LOG_LEVEL",    					lAny));
	mGeneralProperties->add((BaseProperty*)  &mMainContentPanelWidth.setup( 	            "MAIN_CONTENT_PANEL_WIDTH",   		700));
	mGeneralProperties->add((BaseProperty*)  &mPairLEDs.setup(			                    "PAIR_LEDS",    		            true));
	mGeneralProperties->add((BaseProperty*)  &mDBUserID.setup( 	                    	    "ATDB_USER_ID",                    	0));

	mGeneralProperties->add((BaseProperty*)  &mBlockID.setup( 	                   		    "BLOCK_ID",                  		0));
	mGeneralProperties->add((BaseProperty*)  &mKnifeID.setup( 	                   		    "KNIFE_ID",                  		0));
	mGeneralProperties->add((BaseProperty*)  &mLocalDBName.setup(		                    "LOCAL_DB",   			            "umlocal.db"));

    //Camera Settings
	mGeneralProperties->add((BaseProperty*)  &mAutoGain.setup(			                    "AUTO_GAIN",    		            false));
	mGeneralProperties->add((BaseProperty*)  &mAutoExposure.setup( 		                    "AUTO_EXPOSURE",    	            false));
	mGeneralProperties->add((BaseProperty*)  &mAutoBlackLevel.setup(  	                    "AUTO_BLACK_LEVEL",    	            false));
	mGeneralProperties->add((BaseProperty*)  &mAutoWhiteBalance.setup( 	                    "AUTO_WHITE_BALANCE",  	            false));
	mGeneralProperties->add((BaseProperty*)  &mSoftwareGamma.setup( 	                    "SOFTWARE_GAMMA",  		            0));
	mGeneralProperties->add((BaseProperty*)  &mVerticalMirror.setup(	                    "VERTICAL_MIRROR",    	            false));
	mGeneralProperties->add((BaseProperty*)  &mHorizontalMirror.setup(	                    "HORIZONTAL_MIRROR",                false));
	mGeneralProperties->add((BaseProperty*)  &MediaFolderE->getProperty()->setup(           "MEDIA_FOLDER",   		            "C:\\Temp"	));
	mGeneralProperties->add((BaseProperty*)  &mReticleVisible.setup(					    "RETICLE_VISIBILITY",      	        false));

    //UC7
   	mGeneralProperties->add((BaseProperty*)  &mUC7COMPort.setup( 	                        "UC7_COM_PORT",    	   				0));
	mGeneralProperties->add((BaseProperty*)  &mCountToE->getProperty()->setup(       	    "COUNT_TO",                     	5));
	mGeneralProperties->add((BaseProperty*)  &mZeroCutsE->getProperty()->setup(      	    "NUMBER_OF_ZERO_CUTS",           	2));
	mGeneralProperties->add((BaseProperty*)  &mStopCutterMode.setup(    					"STOP_CUTTER_MODE",					1));

	mGeneralProperties->add((BaseProperty*)  &mStageMoveDelayE->getProperty()->setup(	    "KNIFE_STAGE_MOVE_DELAY",          	10));
	mGeneralProperties->add((BaseProperty*)  &mPresetFeedRateE->getProperty()->setup(	    "PRESET_FEED_RATE",               	100));
	mGeneralProperties->add((BaseProperty*)  &mKnifeStageJogStep.setup(	    				"KNIFE_STAGE_JOG_SIZE",          	100));
	mGeneralProperties->add((BaseProperty*)  &mKnifeStageResumeDelta.setup(	    			"KNIFE_STAGE_RESUME_DELTA",        	0));
	mGeneralProperties->add((BaseProperty*)  &ArrayCamServerPortE->getProperty()->setup(	"ARRAYCAM_SERVER_PORT",          	50001));
	mGeneralProperties->add((BaseProperty*)  &mKnifeStageMaxPos.setup(						"KNIFE_STAGE_MAX_POSITION",        	0));
	mGeneralProperties->add((BaseProperty*)  &PresetReturnSpeedE->getProperty()->setup(	    "PRESET_RETURN_SPEED",             	10));
	mGeneralProperties->add((BaseProperty*)  &SlowReturnSpeedE->getProperty()->setup(	    "SLOW_RETURN_SPEED",             	10));
	mGeneralProperties->add((BaseProperty*)  &UltraSlowReturnSpeedE->getProperty()->setup(  "ULTRA_SLOW_RETURN_SPEED",             	10));

    //Zebra
	mGeneralProperties->add((BaseProperty*)  &mZebraCOMPort.setup( 	                    	"ZEBRA_COM_PORT",                   0));
	mGeneralProperties->add((BaseProperty*)  &mZebraBaudRate.setup( 	                	"ZEBRA_BAUD_RATE",                  9600));

    mSoundProperties->setSection("SOUNDS");
	mSoundProperties->setIniFile(&mIniFile);
	mSoundProperties->add((BaseProperty*)  &mKnifeBeforeCuttingSound.setup( 	           	"KNIFE_BEFORE_CUTTING_SOUND",       ApplicationSound("BUTTON_CLICK_1")));
	mSoundProperties->add((BaseProperty*)  &mKnifeCuttingSound.setup( 	               		"KNIFE_CUTTING_SOUND",              ApplicationSound("BUTTON_CLICK_1")));
	mSoundProperties->add((BaseProperty*)  &mKnifeAfterCuttingSound.setup( 	           		"KNIFE_AFTER_CUTTING_SOUND",        ApplicationSound("BUTTON_CLICK_1")));
	mSoundProperties->add((BaseProperty*)  &mArmRetractingSound.setup( 	           			"ARM_RETRACTING_SOUND",       		ApplicationSound("BUTTON_CLICK_1")));
	mSoundProperties->add((BaseProperty*)  &mBeforeKnifeBackOffSound.setup( 	           	"BEFORE_KNIFE_BACKOFF_SOUND",       ApplicationSound("SHORT_BEEP_1")));
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    //Camera stuff
	mCamera1DisplayHandle 	= this->mCamera1BackPanel->Handle;

    Log(lDebug) << "Init camera..";

    //Live
    if(!mCamera1.IsInit())
    {
    	mServiceCamera1.openCamera();
    }

	mCamera1BackPanel->Width 	= 1280;
	mCamera1BackPanel->Height 	= 1024;
	mCamera1BackPanel->Top 		= 0;
	mCamera1BackPanel->Left 	= 0;
    enableDisableArduinoClientControls(false);

	//Connect to the arduino server..
	CheckArduinoServerConnectionTimer->Enabled = true;

    //Setup the server
    mACServer.start(ArrayCamServerPortE->getValue());

    //Populate misc frames
	TSoundsFrame1->populate();
    TApplicationSoundsFrame1->populate(*(mSoundProperties.get()));

    readRegistry();
    MiscTimer->Enabled = true;
    THDMIStreamerFrame1->OutputFileFolderE->setValue(MediaFolderE->getValue());
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
	//Setup callbacks
    pgDM->SQLConnection1->AfterConnect 		= afterDBServerConnect;
    pgDM->SQLConnection1->AfterDisconnect 	= afterDBServerDisconnect;

	BarcodeLbl->Caption = "";
	RibbonIDLbl->Caption = "";

    acu.AppIsStartingUp = false;

    //Set UC7 stop mode
    StopOptionsRG->ItemIndex = mStopCutterMode;
    enableDisableUC7UI(false);
    enableDisableGroupBox(mImagerSettingsGB, false);
	this->Caption = vclstr(createWindowTitle("ArrayCam", Application));
	FitToScreenAExecute(Sender);

    BroadcastStatusTimer->Enabled = true;

    populateStyleMenu(ThemesMenu, ThemesMenuClick);
	mStartupTimer->Enabled = true;
}

