#pragma hdrstop
#include "TMainForm.h"
#include "mtkLogger.h"
#include "TMemoLogger.h"
//#include "TSplashForm.h"
#include "TATDBDataModule.h"
using namespace mtk;
//extern TSplashForm*  gSplashForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::~TMainForm()
{
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ShutDownTimerTimer(TObject *Sender)
{
	ShutDownTimer->Enabled = false;

	if(mLogFileReader.isRunning())
	{
		Log(lDebug) << "Shutting down log file reader";
		mLogFileReader.stop();
	}

    if(atdbDM->SQLConnection1->Connected)
    {
    	atdbDM->SQLConnection1->Connected = false;
    }

    Close();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	Log(lInfo) << "Closing down....";

	//Check if we can close.. abort all threads..
	if(mLogFileReader.isRunning() || atdbDM->SQLConnection1->Connected)
    {
		CanClose = false;
    }
    else
    {
    	CanClose = true;
    }

	if(CanClose == false)
	{
		ShutDownTimer->Enabled = true;
	}

}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Log(lInfo) << "In FormClose";
	mIniFileC->clear();
	Log(lInfo) << "In main forms destructor";

	//Save project history
	mBottomPanelHeight          = BottomPanel->Height;
	mGeneralProperties.write();

	//Write to file
	mIniFileC->save();

	//Registry settings
	mSplashProperties.write();

}

