#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	if(mLogFileReader.isRunning() || mCamera.IsInit() || mLightsArduinoClient.isConnected())
    {
        CanClose = false;
        mShutDownTimer->Enabled = true;
        return;
    }

    CanClose = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mShutDownTimerTimer(TObject *Sender)
{
    mShutDownTimer->Enabled = false;
	if(mLogFileReader.isRunning())
    {
		mLogFileReader.stop();
    }

    if(mCamera.IsInit())
    {
    	mCamera.exitCamera();
    }

    if(mLightsArduinoClient.isConnected())
    {
		mLightsArduinoClient.disConnect();
    }

    Close();
}

