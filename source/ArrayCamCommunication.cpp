#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"


//---------------------------------------------------------------------------
//Callback from socket client class
void TMain::onArrayCamClientConnected()
{
    Log(lDebug) << "ArrayCamClient was connected..";

    //Send message to update UI
    enableDisableArrayCamClientControls(true);
	mASStartBtn->Caption = "Disconnect";
}

//---------------------------------------------------------------------------
void TMain::onArrayCamClientDisconnected()
{
    Log(lDebug) << "ArrayCam Client was disconnected..";
    enableDisableArrayCamClientControls(false);
	mASStartBtn->Caption = "Connect";
}

//---------------------------------------------------------------------------
void TMain::enableDisableArrayCamClientControls(bool enable)
{
	//Disable ArrayCam client related components..
	if(enable == true)
    {
	    mArrayCamConnectionStatusLED->Picture->Bitmap->LoadFromResourceName(NULL, L"GREEN_LED");
		mArrayCamStatusLED->Picture->Bitmap->LoadFromResourceName(NULL, L"GREEN_LED");
    }
    else
    {
		mArrayCamStatusLED->Picture->Bitmap->LoadFromResourceName(NULL, L"GRAY_LED");
	    mArrayCamConnectionStatusLED->Picture->Bitmap->LoadFromResourceName(NULL, L"GRAY_LED");
    }
}

//---------------------------------------------------------------------------
void TMain::onArrayCamMessageReceived(const string& msg)
{
	struct TLocalArgs
    {
        TLocalArgs(TMain& _f, const string& m) : f(_f), msg(m){}
        TMain& f;
        string msg;
        void __fastcall onMessage()
        {
            if(msg == "IS_RECORDING=false")
            {
                f.mArrayCamStatusLED->Picture->Bitmap->LoadFromResourceName(NULL, L"GREEN_LED");
            }
            else if(msg == "IS_RECORDING=true")
            {
                f.mArrayCamStatusLED->Picture->Bitmap->LoadFromResourceName(NULL, L"RED_LED");
            }
        }
    };

    TLocalArgs args(*this, msg);

    //This causes this function to be called in the UI thread
	TThread::Synchronize(NULL, &args.onMessage);
}

