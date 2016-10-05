#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "abDBUtils.h"
#include "abVCLUtils.h"
using namespace mtk;
using namespace ab;
extern bool   gAppIsStartingUp;
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    //Camera stuff
	mDisplayHandle 	= this->mCameraStreamPanel->Handle;
	mCameraStartLiveBtnClick(Sender);

	mCameraStreamPanel->Width = 1280;
	mCameraStreamPanel->Height = 1024;
	mCameraStreamPanel->Top = 0;
	mCameraStreamPanel->Left = 0;
	mFitToScreenButtonClick(Sender);

    enableDisableClientControls(false);

	//Setup sounds
	mGetReadyForZeroCutSound.create(this->Handle);
	mSetZeroCutSound.create(this->Handle);
	mRestoreFromZeroCutSound.create(this->Handle);

    //Setup LogLevel CB
    string logLevel = mtk::toString(gLogger.getLogLevel());

    //Find item in CB with this loglevel
    int index = LogLevelCB->Items->IndexOf(vclstr(logLevel));

    if(index > -1)
    {
		LogLevelCB->ItemIndex = index;
    }

	//Connect to the arduino server..
	mLightsArduinoClient.connect(50000);
   	mSensorsArduinoClient.connect(50000);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
	string dBase(mLocalDBName);
	//Our low level db connection
	//Connect to local database
	try
    {
        if(!mClientDBSession.isConnected())
        {
            mClientDBSession.connect();
        }

        if(mClientDBSession.isConnected())
        {
            Log(lInfo) << "Connected to local database.";
        }
        else
        {
            Log(lError) << "Failed to connect to database server...";
        }
    }
    catch(...)
    {
    	handleMySQLException();
    }

    //UI DB connection
    if (ImagesAndMoviesDM->Connect(dBase))
    {
       // Connection successfull
        Log(lInfo) << "DataModule connected to the database: "<<dBase;
        populateUsersCB(mUsersCB, mClientDBSession);
    }
    else
    {
        Log(lInfo) << "Datamodule failed to connect to database: "<<dBase;
    }

    gAppIsStartingUp = false;
}

