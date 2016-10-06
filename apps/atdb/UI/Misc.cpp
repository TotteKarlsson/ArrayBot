#pragma hdrstop
#include "TMainForm.h"
#include "mtkVCLUtils.h"
#include "mtkLogger.h"
//#include "TSplashForm.h"
#pragma package(smart_init)
using Poco::DateTimeFormatter;

using namespace mtk;

extern HWND gOtherAppWindow;
//extern TSplashForm*  gSplashForm;
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}

void __fastcall TMainForm::ClearMemoAExecute(TObject *Sender)
{
    infoMemo->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::LogLevelCBChange(TObject *Sender)
{
    if(LogLevelCB->ItemIndex == 0)
    {
        mLogLevel = lInfo;
    }
    else if(LogLevelCB->ItemIndex == 1)
    {
        mLogLevel = lAny;
    }

    gLogger.setLogLevel(mLogLevel);
}


BOOL CALLBACK FindOtherWindow(HWND hwnd, LPARAM lParam)
{
	static TCHAR buffer[50];
	GetWindowText(hwnd, buffer, 50);

	if(_tcsstr(buffer, "atDB"))
	{
		// do something with hwnd here
		gOtherAppWindow = hwnd;
		return FALSE;
	}

	return TRUE;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::AppInBox(mlxStructMessage &msg)
{
    if(msg.lparam == NULL)
    {
        return;
    }

    try
    {
        ApplicationMessageEnum aMsg = msg.lparam->mMessageEnum;

        switch(aMsg)
        {
            case amSplashWasClosed:
                Log(lDebug2) << "Splash form sent message that it was closed";
//                gSplashForm = NULL;
            break;

            default:
            break ;
        }
	}
	catch(...)
	{
		Log(lError) << "Received an unhandled windows message!";
	}
}




