#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
//---------------------------------------------------------------------------

extern bool gAppIsClosing;
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	gAppIsClosing = true;
	if(mLogFileReader.isRunning() || mCamera.IsInit() || mLightsArduinoClient.isConnected() || mSensorsArduinoClient.isConnected())
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

    if(mSensorsArduinoClient.isConnected())
    {
		mSensorsArduinoClient.disConnect();
    }

    Close();
}

