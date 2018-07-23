#pragma hdrstop
#include "TMainForm.h"
#include "dslTMemoLogger.h"
#include "dslVCLUtils.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "dslLogger.h"
#include "dslIniSection.h"
#include "Core/atDBUtilities.h"
#include "Poco/Timezone.h"
#include "TPGDataModule.h"
#include "database/atDBUtils.h"
#include "TPGCoverSlipDataModule.h"

extern bool             gAppIsStartingUp;
extern bool             gIsDevelopmentRelease;
extern string           gCommonAppDataLocation;
extern string           gLogFileLocation;
extern string           gLogFileName;
extern string           gFullDateTimeFormat;
extern string           gDateFormat;
extern string           gTimeFormat;
extern string           gApplicationStyle;

//extern TSplashForm*     gSplashForm;
extern string           gTimeFormat;

using namespace dsl;
using namespace at;
using Poco::DateTime;
using Poco::DateTimeFormatter;

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    TMemoLogger::mMemoIsEnabled = false;
	setupWindowTitle();
	if(mLogLevel == lInfo)
	{
		LogLevelCB->ItemIndex = 0;
		StringList logs = getLinesInFile(joinPath(gLogFileLocation, gLogFileName));

		StringList msgs;
		msgs.append("WARNING");
		msgs.append("ERROR");
		msgs.append("INFO");

		//Only add lines to logwindow with lInfo and "higher"
		for(uint i = 0; i < logs.size(); i++)
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

    if(pgDM)
    {
		pgDM->SQLConnection1->AfterConnect 		= afterDBServerConnect;
	    pgDM->SQLConnection1->AfterDisconnect 	= afterDBServerDisconnect;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
   	Log(lInfo) << "In FormShow";
   	Log(lInfo) << "Form visibility: "<<dsl::toString(this->Visible);
	gAppIsStartingUp = false;

	//transfer INI values
	BottomPanel->Height     = mBottomPanelHeight + 1;
	SB->Top = MainForm->Top + MainForm->Height + 10;
	SB->SizeGrip = true;
    populateStyleMenu(ThemesMenu, ThemesMenuClick);

	//Read grid column settings from files in AppData/Grids folder
//	Log(lInfo) << "Reading column states";
//
//	for(int i = 0; i < mDBGrids.size(); i++)
//    {
//    	if(mDBGrids[i] != NULL)
//        {
//            string fName = joinPathU(gCommonAppDataLocation, "Grids", mDBGrids[i]->Name);
//            if(fileExists(fName.c_str()))
//            {
//		    	mDBGrids[i]->Columns->LoadFromFile(fName.c_str());
//            }
//        }
//    }


   	TPGConnectionFrame1->init(mIniFileC->getFile(), "POSTGRESDB_CONNECTION");

    try
    {
	    TPGConnectionFrame1->ConnectA->Execute();
    }
    catch (const TDBXError &e)
	{
    	Log(lInfo) << "There was a database connection issue: "<<stdstr(e.Message);
	}

	//Filter Specimen data
	SpecieRGClick(Sender);
}

void TMainForm::setupIniFile()
{
	string fldr =  joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "atDB");

	if(!folderExists(fldr))
	{
		CreateDir(fldr.c_str());
	}

	mIniFileC->init(fldr);

	//For convenience and for option form, populate appProperties container
	mAppProperties.append(mGeneralProperties);
   	mAppProperties.append(mCoverslipPrintingProperties);
	mAppProperties.append(mSplashProperties);
}

bool TMainForm::setupAndReadIniParameters()
{
	mIniFileC->load();
	mGeneralProperties->setIniFile(mIniFileC->getIniFile());

	//Setup parameters
	mGeneralProperties->setSection("GENERAL");
	mGeneralProperties->add((BaseProperty*)  &mBottomPanelHeight.setup( 	            "HEIGHT_OF_BOTTOM_PANEL",    	    205));
	mGeneralProperties->add((BaseProperty*)  &mMainTabIndex.setup( 	                "MAIN_TAB_INDEX",           	    0));
	mGeneralProperties->add((BaseProperty*)  &mLogLevel.setup( 	                    "LOG_LEVEL",    	                lAny));
	mGeneralProperties->add((BaseProperty*)  &mTableUnlockPassword.setup( 	        "TABLE_UNLOCK_PASSWORD",            "atdb123"));

	mGeneralProperties->add((BaseProperty*)  &mDBUserID.setup( 	                    "ATDB_USER_ID",                    	0));
//	mGeneralProperties->add((BaseProperty*)  &mServerIPE->getProperty()->setup( 	    "MYSQL_SERVER_IP",              	"127.0.0.1"));
//	mGeneralProperties->add((BaseProperty*)  &mDBUserE->getProperty()->setup( 	    "ATDB_USER_NAME",                   "none"));
//	mGeneralProperties->add((BaseProperty*)  &mPasswordE->getProperty()->setup( 	    "ATDB_USER_PASSWORD",               "none"));
//	mGeneralProperties->add((BaseProperty*)  &mDatabaseE->getProperty()->setup( 	    "ATDB_DB_NAME",    			        "none"));
//	mGeneralProperties->add((BaseProperty*)  &mDustAssayImageFolderE->getProperty()->setup(
//    																				"DUSTASSAY_IMAGER_FOLDER",          "c:\\"));

	mGeneralProperties->add((BaseProperty*)  &MediaFolderE->getProperty()->setup(    "MEDIA_FOLDER",   		            "C:\\Temp"	));
	mGeneralProperties->add((BaseProperty*)  &mDustAssayResultImageHeight.setup( 	"RESULT_IMAGE_HEIGHT",     	        100));
	mGeneralProperties->add((BaseProperty*)  &mDustAssayBackGroundImageWidth.setup( 	"BACKGROUND_IMAGE_WIDTH",  	        100));
	mGeneralProperties->add((BaseProperty*)  &BatchesGBHeight.setup( 				"BATCHES_GB_HEIGHT",  	        	250));

	//Read from file. Create if file do not exist
	mGeneralProperties->read();

	//Update
//    mDBUserE->update();
//    mPasswordE->update();
//    mDatabaseE->update();
//	mServerIPE->update();
//	mDustAssayImageFolderE->update();
    MediaFolderE->update();

    //Coverslip properties
   	mCoverslipPrintingProperties->setIniFile(mIniFileC->getIniFile());
	mCoverslipPrintingProperties->setSection("COVERSLIPLABEL_PRINTING");

    mCoverslipPrintingProperties->read();
    BatchesGB->Height = BatchesGBHeight;

	//Setup UI elements
	mSplashProperties->add((BaseProperty*)  &mShowSplashOnStartup.setup(             "ShowOnStartup",                    true));

	if(mSplashProperties->doesSectionExist())
	{
		mSplashProperties->read();
	}

	return true;
}
