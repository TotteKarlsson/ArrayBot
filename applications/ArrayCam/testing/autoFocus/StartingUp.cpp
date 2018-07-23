#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "atVCLUtils.h"
#include "TNavitarPresetFrame.h"
#include "ArrayCamUtilities.h"
#include "arraybot/apt/atAPTMotor.h"
#include "arraybot/apt/atDeviceManager.h"

using namespace dsl;
using namespace at;

extern ArrayCamUtilities acu;

void TMainForm::setupProperties()
{
	//Setup UI/INI properties
    mGeneralProperties.setSection("GENERAL");
	mGeneralProperties.setIniFile(&mIniFile);

	mGeneralProperties.add((BaseProperty*)  &mLogLevel.setup( 	    	                    "LOG_LEVEL",    					lAny));
	mGeneralProperties.add((BaseProperty*)  &mMainContentPanelWidth.setup( 	                "MAIN_CONTENT_PANEL_WIDTH",   		700));

    //Camera Settings
	mGeneralProperties.add((BaseProperty*)  &mAutoGain.setup(			                    "AUTO_GAIN",    		            false));
	mGeneralProperties.add((BaseProperty*)  &mAutoExposure.setup( 		                    "AUTO_EXPOSURE",    	            false));
	mGeneralProperties.add((BaseProperty*)  &mAutoBlackLevel.setup(  	                    "AUTO_BLACK_LEVEL",    	            false));
	mGeneralProperties.add((BaseProperty*)  &mAutoWhiteBalance.setup( 	                    "AUTO_WHITE_BALANCE",  	            false));
	mGeneralProperties.add((BaseProperty*)  &mSoftwareGamma.setup( 	                        "SOFTWARE_GAMMA",  		            0));
	mGeneralProperties.add((BaseProperty*)  &mVerticalMirror.setup(	                        "VERTICAL_MIRROR",    	            false));
	mGeneralProperties.add((BaseProperty*)  &mHorizontalMirror.setup(	                    "HORIZONTAL_MIRROR",                false));
	mGeneralProperties.add((BaseProperty*)  &MediaFolderE->getProperty()->setup(            "MEDIA_FOLDER",   		            "C:\\Temp"	));
	mGeneralProperties.add((BaseProperty*)  &mReticleVisible.setup(					        "RETICLE_VISIBILITY",      	        false));

}

bool TMainForm::createMotorFrame(APTMotor* mtr)
{
	if(!mtr)
    {
    	return false;
    }

    TMotorFrame *f = new TMotorFrame(mtr->getName(), ScrollBox1);
   	f->assignMotor(mtr);
    f->Parent = ScrollBox1;
    f->Align = alTop;

	f->MotorStatusTimer->Enabled = true;
    return true;
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

    //Setup motor frame
    mDeviceManager.connectAllDevices();

    APTDevice* dev = mDeviceManager.getFirst();
    if(dev)
    {
    	dev->setName("test");
    }

	createMotorFrame(dynamic_cast<APTMotor*> (dev));
    while(mDeviceManager.getNext())
    {
		createMotorFrame(dynamic_cast<APTMotor*> (mDeviceManager.getCurrent()));
    }


    readRegistry();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
    acu.AppIsStartingUp = false;

//    enableDisableGroupBox(mImagerSettingsGB, false);
	mStartupTimer->Enabled = true;
	this->Caption = vclstr(createWindowTitle("TestAutoFocus", Application));
	FitToScreenAExecute(Sender);
    populateStyleMenu(ThemesMenu, ThemesMenuClick);
}

