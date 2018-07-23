#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "TAboutATDBForm.h"
#include "TPGDataModule.h"
#pragma package(smart_init)
#include "TCoverSlipForm.h"
#include "TScanForm.h"
using Poco::DateTimeFormatter;

using namespace dsl;

extern HWND gOtherAppWindow;
extern string gAppName;

void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
//    else if(Key == VK_RETURN)
//    {
//    }
}

void __fastcall TMainForm::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
    mBCBuilder.build((char) Key);

    if(Key == '\r')
    {           //Check character buffer
        if(mBCBuilder.hasBarCode())
        {
		    Poco::Path p(MediaFolderE->getValue());
            TScanForm* f = new TScanForm(p, this);
            f->populate(mBCBuilder.getBarCode());
            this->Visible = false;
            f->ShowModal();
            this->Visible = true;
            delete f;
        }

		mBCBuilder.reset();
    }
    //Check barcode from reader

}



void __fastcall TMainForm::OpenAboutFormAExecute(TObject *Sender)
{
	TAboutATDBForm* f = new TAboutATDBForm(this);
    f->ShowModal();
    delete f;
}

void __fastcall TMainForm::ClearMemoAExecute(TObject *Sender)
{
    infoMemo->Clear();
}

int TMainForm::getCurrentUserID()
{
	int i = UsersCB->KeyValue;
	return  i;
}

void TMainForm::setupWindowTitle()
{
	string title = createWindowTitle(gAppName, Application);
	this->Caption = vclstr(title);
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




