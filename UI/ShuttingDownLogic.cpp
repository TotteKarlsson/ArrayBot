#pragma hdrstop
#include "MainForm.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "abAPTMotor.h"
#include "TSplashForm.h"
#include "TRibbonLifterFrame.h"
#include "TXYZUnitFrame.h"
#include "TAboutArrayBotForm.h"
using namespace mtk;

static HWND gOtherAppWindow = NULL;
extern TSplashForm*  gSplashForm;

//---------------------------------------------------------------------------
void __fastcall TMain::ShutDownTimerTimer(TObject *Sender)
{
	ShutDownTimer->Enabled = false;
    if(TRibbonLifterFrame::gIsFrameOpen)
    {
    	mRibbonLifterFrame->close();
    }

	if(mLogFileReader.isRunning())
	{
		Log(lDebug) << "Shutting down log file reader";
		mLogFileReader.stop();
	}

    if(UIUpdateTimer->Enabled)
    {
        UIUpdateTimer->Enabled = false;
    }

	if(mAB->getJoyStick().isEnabled())
    {
		mAB->getJoyStick().disable();
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
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	Log(lInfo) << "Closing down....";

	//Check if we can close.. abort all threads..
	CanClose = (mLogFileReader.isRunning()) ? false : true;

	//Check if active stuff is going on.. if so call the ShutDown in the
    //Timer fire
	if(		mAB->getJoyStick().isEnabled()
    	|| 	mAB->isActive()
        || 	UIUpdateTimer->Enabled
        || 	(gSplashForm && gSplashForm->isOnShowTime())
		|| 	TRibbonLifterFrame::gIsFrameOpen
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

