#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "dslTMemoLogger.h"
//#include "TSplashForm.h"

using namespace dsl;
//extern TSplashForm*  gSplashForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::~TMainForm()
{
	mIniFileC->clear();
	Log(lInfo) << "In main forms destructor";

	//Save project history
	mBottomPanelHeight          = BottomPanel->Height;
//	mGeneralProperties.write();

	//Write to file
	mIniFileC->save();

	//Registry settings
	mSplashProperties.write();
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

    Close();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	Log(lInfo) << "Closing down....";

	//Check if we can close.. abort all threads..
	if(mLogFileReader.isRunning())
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
}

