#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "apt/atAPTMotor.h"
#include "TSplashForm.h"
#include "frames/TXYZUnitFrame.h"

using namespace mtk;

static HWND gOtherAppWindow = NULL;
extern TSplashForm*  gSplashForm;

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

	if(mAB->getJoyStick().isEnabled())
    {
		mAB->getJoyStick().disable();
    }

    if(mArrayCamClient.isConnected())
    {
    	mArrayCamClient.disConnect();
    }

//    if(mPufferArduinoClient.isConnected())
//    {
//    	mPufferArduinoClient.disConnect();
//    }

    //This will save any ini parameters in the frame
    if(mFrames.size())
    {
        for(int i = 0; i < mFrames.size(); i++)
        {
            delete mFrames[i];
        }

        mFrames.clear();
    }

	if(mAB->isActive())
    {
    	if(!mAB->isShuttingDown())
        {
	        mXYZUnitFrame1->disable();
    	    mXYZUnitFrame2->disable();
	    	mAB->shutDown();
        }
        else
        {
        	//Weird..
            mAB->shutDown();
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
    mAB->getJoyStick().disable();
    mXYZUnitFrame1->disable();
    mXYZUnitFrame2->disable();

    //The shutdown disconnects all devices
    mAB->shutDown();

	while(mAB->isActive())
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
	if(		mAB->getJoyStick().isEnabled()
    	|| 	mAB->isActive()
        || 	UIUpdateTimer->Enabled
        || 	(gSplashForm && gSplashForm->isOnShowTime())
        || mArrayCamClient.isConnected()
//        ||  mPufferArduinoClient.isConnected()
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

