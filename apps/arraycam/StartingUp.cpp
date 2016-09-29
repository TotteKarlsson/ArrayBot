#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"

using namespace mtk;

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	mDisplayHandle 	= this->mCameraStreamPanel->Handle;
	mCameraStartLiveBtnClick(Sender);

	mCameraStreamPanel->Width = 1280;
	mCameraStreamPanel->Height = 1024;
	mCameraStreamPanel->Top = 0;
	mCameraStreamPanel->Left = 0;
	mFitToScreenButtonClick(Sender);
	updateVideoFileLB();
	updateShotsLB();

    enableDisableClientControls(false);

	//Try to connect to the arduino server..
	mLightsArduinoClient.connect(50000);

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

	try
    {
        if(!mClientDBSession.isConnected())
        {
            mClientDBSession.connect();
        }

        if(mClientDBSession.isConnected())
        {
            Log(lInfo) << "Connected to local SQLITE database.";
        }
        else
        {
            Log(lError) << "Failed to connect to database server...";
        }
    }
    catch(...)
    {
    	handleSQLiteException();
    }
}

