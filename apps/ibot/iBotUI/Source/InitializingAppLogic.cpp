#pragma hdrstop
#include "TMainForm.h"
//#include "TSplashForm.h"
#include "TMemoLogger.h"
#include "mtkVCLUtils.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "mtkLogger.h"
#include "mtkIniSection.h"
#include "ibUtilities.h"
#include "Poco/Timezone.h"

extern bool             gAppIsStartingUp;
extern bool             gIsDevelopmentRelease;
extern string           gCommonAppDataLocation;
extern string           gLogFileLocation;
extern string           gLogFileName;
extern string           gFullDateTimeFormat;
extern string           gDateFormat;
extern string           gTimeFormat;

//extern TSplashForm*     gSplashForm;
extern string           gTimeFormat;

using namespace mtk;
using Poco::DateTime;
using Poco::DateTimeFormatter;

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    StartupTimer->Enabled = true;
    TMemoLogger::mMemoIsEnabled = false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
    if(mIsStyleMenuPopulated == false)
    {
        PopulateStyleMenu();
        mIsStyleMenuPopulated = true;
	}

	//transfer INI values
	BottomPanel->Height     = mBottomPanelHeight + 1;
	SB->Top = MainForm->Top + MainForm->Height + 10;
	SB->SizeGrip = true;
    gAppIsStartingUp = false;
}

void TMainForm::setupIniFile()
{
	string fldr = getSpecialFolder(CSIDL_LOCAL_APPDATA);
	fldr =  joinPath(fldr, "iBot");

	if(!folderExists(fldr))
	{
		CreateDir(fldr.c_str());
	}

	mIniFileC->init(fldr);

	//For convenience and for option form, populate appProperties container
	mAppProperties.append(&mGeneralProperties);
	mAppProperties.append(&mSplashProperties);
}

bool TMainForm::setupAndReadIniParameters()
{
	mIniFileC->load();
	mGeneralProperties.setIniFile(mIniFileC->getIniFile());

	//Setup parameters
	mGeneralProperties.setSection("GENERAL");
	mGeneralProperties.add((BaseProperty*)  &mBottomPanelHeight.setup( 	            "HEIGHT_OF_BOTTOM_PANEL",    	    205));
	mGeneralProperties.add((BaseProperty*)  &mMainTabIndex.setup( 	                "MAIN_TAB_INDEX",           	    0));
	mGeneralProperties.add((BaseProperty*)  &mLogLevel.setup( 	                    "LOG_LEVEL",    	                lAny));

	//Read from file. Create if file do not exist
	mGeneralProperties.read();
	mSplashProperties.add((BaseProperty*)  &mShowSplashOnStartup.setup(             "ShowOnStartup",                    true));

	if(mSplashProperties.doesSectionExist())
	{
		mSplashProperties.read();
	}

	return true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::StartupTimerTimer(TObject *Sender)
{
	StartupTimer->Enabled = false;


//    if(gSplashForm)
//    {
//		gSplashForm->mMainAppIsRunning = true;
//
//		this->Visible = true;
//		while(gSplashForm->isOnShowTime() == true)
//		{
//			//In order to show whats going on on the splash screen
//			Application->ProcessMessages();
//			if(gSplashForm->Visible == false)
//			{
//				break;
//			}
//		}
//
//		gSplashForm->Close();
//    }
//	gLogger.setLogLevel(mLogLevel);

	if(mLogLevel == lInfo)
	{
		LogLevelCB->ItemIndex = 0;
		StringList logs = getLinesInFile(joinPath(gLogFileLocation, gLogFileName));

		StringList msgs;
		msgs.append("WARNING");
		msgs.append("ERROR");
		msgs.append("INFO");

		//Only add lines to logwindow with lInfo and "higher"
		for(int i = 0; i < logs.size(); i++)
		{
			if(contains(msgs, logs[i]))
			{
				infoMemo->Lines->Add(vclstr(logs[i]));
			}
		}
	}
	else if(mLogLevel == lAny)
	{
		LogLevelCB->ItemIndex = 1;
		StringList logs = getLinesInFile(joinPath(gLogFileLocation, gLogFileName));

		//Only add lines to log window with lInfo and "igher"
		for(int i = 0; i < logs.size(); i++)
		{
			infoMemo->Lines->Add(vclstr(logs[i]));
		}
	}

	mLogFileReader.start(true);
}

void TMainForm::setupWindowTitle()
{
	string title = createWindowTitle("iBot", Application);
	this->Caption = vclstr(title);
}
