#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
using namespace dsl;

//---------------------------------------------------------------------------
void __fastcall TMainForm::ShutDownTimerTimer(TObject *Sender)
{
	ShutDownTimer->Enabled = false;
    if(UIUpdateTimer->Enabled)
    {
        UIUpdateTimer->Enabled = false;
    }

    if(TWatchDogServerFrame1->canClose() == false)
    {
	    TWatchDogServerFrame1->shutDown();
    }

    if(mArduinoServer.isRunning())
    {
    	mArduinoServer.shutDown();
    }

    mArduinoServer.assignOnUpdateCallBack(NULL);

    if(pgDM && pgDM->SQLConnection1->Connected)
    {
    	pgDM->SQLConnection1->Connected = false;
	    pgDM->SQLConnection1->Close();
    }

    //This will save any ini parameters in the frame
    for(int i = 0; i < mFrames.size(); i++)
    {
    	delete mFrames[i];
    }

    mFrames.clear();

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
	CanClose = (mLogFileReader.isRunning()) ? false : true;

	//Check if active stuff is going on.. if so call the ShutDown in the
    //Timer fire
   	CanClose = (mFrames.size()
            	|| mArduinoServer.isRunning()
		        || (pgDM && pgDM->SQLConnection1->Connected)
                || (TWatchDogServerFrame1->canClose() == false)
                ) ? false : true;


	if(CanClose == false)
	{
		ShutDownTimer->Enabled = true;
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Log(lInfo) << "In FormClose";
	TPGConnectionFrame1->writeParameters();


    mBottomPanelVisible = BottomPanel->Visible ;
    mBottomPanelHeight = BottomPanel->Height;
	mProperties.write();

    mWatchDogServer.writeIniParameters();
	//Do thist last
    mIniFile.save();
}

