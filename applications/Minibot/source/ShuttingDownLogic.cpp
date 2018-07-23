#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "TPGDataModule.h"
#include "THandWheelPositionForm.h"
#include "TXYZUnitFrame.h"

using namespace dsl;

static HWND gOtherAppWindow = NULL;
//extern TSplashForm*  gSplashForm;


__fastcall TMainForm::~TMainForm()
{
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ShutDownTimerTimer(TObject *Sender)
{
	ShutDownTimer->Enabled = false;

    if(UIUpdateTimer->Enabled)
    {
        UIUpdateTimer->Enabled = false;
    }

	if(mAB.getJoyStick().isEnabled())
    {
		mAB.getJoyStick().disable();
    }

	if(mAB.isActive())
    {
    	if(!mAB.isShuttingDown())
        {
	        mXYZUnitFrame1->disable();
	    	mAB.shutDown();
        }
        else
        {
        	//Weird..
            mAB.shutDown();
        }
    }

	if(mHandWheelPositionForm)
    {
    	mHandWheelPositionForm->setTimeToClose();
        mHandWheelPositionForm->Close();
        mHandWheelPositionForm = NULL;
    }

   	if(mZebra.isConnected())
    {
    	mZebra.disconnect();
    }

    if(mUC7.isConnected())
    {
	    mUC7.disConnect();
    }

    if(pgDM && pgDM->SQLConnection1 && pgDM->SQLConnection1->Connected)
    {
    	pgDM->SQLConnection1->Connected = false;
	    pgDM->SQLConnection1->Close();
    }

	if(mLogFileReader.isRunning())
	{
		Log(lDebug) << "Shutting down log file reader";
		mLogFileReader.stop();
	}

	Close();
}

void __fastcall TMainForm::ShutDownAExecute(TObject *Sender)
{
    mAB.getJoyStick().disable();
    mXYZUnitFrame1->disable();

    //The shutdown disconnects all devices
    mAB.shutDown();

	while(mAB.isActive())
    {
    	sleep(100);
    }

    ReInitBotBtn->Action = reInitBotA;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	Log(lInfo) << "Closing down....";

	//Check if active stuff is going on.. if so call the ShutDown in the
    //Timer fire
	if(
    	mAB.getJoyStick().isEnabled()       ||
    	mAB.isActive()                      ||
        UIUpdateTimer->Enabled              ||
        mLogFileReader.isRunning()          ||
        pgDM && pgDM->SQLConnection1 && pgDM->SQLConnection1->Connected     ||
        mZebra.isConnected()                ||
        mHandWheelPositionForm
      )
    {
  		CanClose = false;
		ShutDownTimer->Enabled = true;
        return;
    }

   	CanClose = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Log(lInfo) << "In FormClose";
	TPGConnectionFrame1->writeParameters();

	Log(lInfo) << "In FormClose";
	mUC7COMPort = mUC7ComportCB->ItemIndex + 1;

//	mZebraCOMPort = mZebraCOMPortCB->ItemIndex + 1;
//    mZebraBaudRate = mZebraBaudRateCB->Items->Strings[mZebraBaudRateCB->ItemIndex].ToInt();

//    mKnifeStageMaxPos.setValue(MaxStagePosFrame->getValue());
//    mKnifeStageJogStep.setValue(BackOffStepFrame->getValue());
//    mKnifeStageResumeDelta.setValue(ResumeDeltaDistanceFrame->getValue());

    mStopCutterMode = StopOptionsRG->ItemIndex;

	mGeneralProperties.write();
	mSoundProperties.write();
    mIniFile.save();
}

