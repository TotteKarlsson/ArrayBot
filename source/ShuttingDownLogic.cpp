#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "arraybot/apt/atAPTMotor.h"
#include "TSplashForm.h"
#include "TXYZUnitFrame.h"

using namespace dsl;

static HWND gOtherAppWindow = NULL;
extern TSplashForm*  gSplashForm;


__fastcall TMain::~TMain()
{
//	delete mSequencerButtons;

//    delete mABProcessSequencerFrame;
//	delete mXYZUnitFrame1;
//	delete mXYZUnitFrame2;
	mProperties.write();
	mSoundProperties.write();
    mIniFile.save();
}

//---------------------------------------------------------------------------
void __fastcall TMain::ShutDownTimerTimer(TObject *Sender)
{
	ShutDownTimer->Enabled = false;

    if(mTheWiggler.isRunning())
    {
    	mTheWiggler.stopWiggle();
    }

    if(UIUpdateTimer->Enabled)
    {
        UIUpdateTimer->Enabled = false;
    }

	if(mAB.getJoyStick().isEnabled())
    {
		mAB.getJoyStick().disable();
    }

    if(mArrayCamClient.isConnected())
    {
    	mArrayCamClient.disConnect();
    }

    if(gSplashForm && gSplashForm->isOnShowTime())
    {
	    gSplashForm->setShowTime(0);
        gSplashForm->Close();

    	Log(lDebug) << "Waiting for splash..";
    }

    //This will save any ini parameters in the frame
    if(mFrames.size())
    {
        for(int i = 0; i < mFrames.size(); i++)
        {
            delete mFrames[i];
        }

        mFrames.clear();
    }

	if(mAB.isActive())
    {
    	if(!mAB.isShuttingDown())
        {
	        mXYZUnitFrame1->disable();
    	    mXYZUnitFrame2->disable();
	    	mAB.shutDown();
        }
        else
        {
        	//Weird..
            mAB.shutDown();
        }
    }

	if(mLogFileReader.isRunning())
	{
		Log(lDebug) << "Shutting down log file reader";
		mLogFileReader.stop();
	}

	Close();
}

void __fastcall TMain::ShutDownAExecute(TObject *Sender)
{
    mAB.getJoyStick().disable();
    mXYZUnitFrame1->disable();
    mXYZUnitFrame2->disable();

    //The shutdown disconnects all devices
    mAB.shutDown();

	while(mAB.isActive())
    {
    	sleep(100);
    }

    ReInitBotBtn->Action = reInitBotA;
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	Log(lInfo) << "Closing down....";

	//Check if active stuff is going on.. if so call the ShutDown in the
    //Timer fire
	if(	   mAB.getJoyStick().isEnabled()
    	|| mAB.isActive()
        || UIUpdateTimer->Enabled
        || (gSplashForm && gSplashForm->isOnShowTime())
        || mArrayCamClient.isConnected()
        || mFrames.size()
        || mTheWiggler.isRunning()
        || mLogFileReader.isRunning()
      )
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
void __fastcall TMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	Log(lInfo) << "In FormClose";
}

