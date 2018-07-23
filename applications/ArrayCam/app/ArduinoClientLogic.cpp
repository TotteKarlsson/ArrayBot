#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "TSettingsForm.h"
#include "dslLogger.h"
#include "ArrayCamUtilities.h"
//---------------------------------------------------------------------------
using namespace dsl;

extern ArrayCamUtilities acu;
//---------------------------------------------------------------------------
//Callback from socket client class
void TMainForm::onArduinoClientConnected()
{
    Log(lDebug) << "ArduinoClient was connected..";
	CheckArduinoServerConnectionTimer->Enabled = false;
    ArduinoServerStartStopButton->Caption = "Stop";

    //Send message to update UI
    mLightsArduinoClient.getBoardStatus();
    enableDisableArduinoClientControls(true);
}

//---------------------------------------------------------------------------
void TMainForm::onArduinoClientDisconnected()
{
    Log(lDebug) << "Arduino Client was disconnected..";

	//Don't worry if we are closing down..
    if(acu.AppIsClosing != true)
    {
	    ArduinoServerStartStopButton->Caption = "Start";
    	enableDisableArduinoClientControls(false);
        if(mCheckArduinoServerConnection)
        {
			CheckArduinoServerConnectionTimer->Enabled = true;
        }
    }
}

void __fastcall TMainForm::ArduinoServerStartStopButtonClick(TObject *Sender)
{
	if(ArduinoServerStartStopButton->Caption == "Start")
    {
    	mLightsArduinoClient.connect(mArduinoServerPortE->getValue());
        ArduinoServerStartStopButton->Caption == "Connecting";
        mCheckArduinoServerConnection = true;
    }
    else
    {
		//User closed connection manually - don't restore automatically
		mCheckArduinoServerConnection = false;
    	mLightsArduinoClient.disConnect();
    }
}

//---------------------------------------------------------------------------
void TMainForm::enableDisableArduinoClientControls(bool enable)
{
	mArduinoServerPortE->Enabled = !enable;
    LightIntensitiesGB->Enabled = enable;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CheckArduinoServerConnectionTimerTimer(TObject *Sender)
{
	Log(lDebug5) << "Trying to connect to Arduino server";
    if(!mConnectToArduinoServerThread.isRunning() && !mLightsArduinoClient.isConnected())
    {
    	mConnectToArduinoServerThread.start();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mAutoCheckConnectionCBClick(TObject *Sender)
{
	CheckArduinoServerConnectionTimer->Enabled = mAutoCheckConnectionCB->Checked;
}
