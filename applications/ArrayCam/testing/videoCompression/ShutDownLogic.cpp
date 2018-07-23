#pragma hdrstop
#include "VCL.Dialogs.hpp"
#include "TMainForm.h"
#include "dslLogger.h"
#include "TFFMPEGOutputFrame.h"
using namespace dsl;

//---------------------------------------------------------------------------
void __fastcall TMainForm::ShutDownTimerTimer(TObject *Sender)
{
	ShutDownTimer->Enabled = false;
	//Check for frames to delete
    list<TFFMPEGOutputFrame*>::iterator i;
	for(i = mCompressionFrames.begin(); i != mCompressionFrames.end();)
    {
    	if((*i))
        {
			MessageDlg("Wait or stop ongoing jobs before closing..", mtWarning, TMsgDlgButtons() << mbOK, 0);
            return;
        }
    }

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
	CanClose = (
    			mLogFileReader.isRunning()
        		)
         ? false : true;

	//Check for frames to delete
    list<TFFMPEGOutputFrame*>::iterator i;
	for(i = mCompressionFrames.begin(); i != mCompressionFrames.end();)
    {
    	if((*i) && (*i)->isDone() == false )
        {
			 CanClose = false;
             break;
        }
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

