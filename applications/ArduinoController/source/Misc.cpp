#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "TAboutArduinoControllerForm.h"
#include "dslLogger.h"
using namespace dsl;

static HWND gOtherAppWindow = NULL;

void __fastcall	TMainForm::OnException()
{
	Log(lInfo) << "Exception TMainForm::OnException()";
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ApplicationEvents1Exception(TObject *Sender, Exception *E)
{
	Log(lInfo) << "Application Exception...."<<stdstr(E->Message);
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
            default:
            break ;
        }
	}
	catch(...)
	{
		Log(lError) << "Received an unhandled windows message!";
	}
}

void __fastcall TMainForm::LogLevelCBChange(TObject *Sender)
{
	if(LogLevelCB->ItemIndex == -1)
    {
    	return;
    }

    string lvl = stdstr(LogLevelCB->Items->Strings[LogLevelCB->ItemIndex]);

    mLogLevel = toLogLevel(lvl);
    gLogger.setLogLevel(mLogLevel);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
	this->Height = this->Height - 1;
	this->Height = this->Height + 1;
}

//This one is called from the reader thread
void __fastcall TMainForm::logMsg()
{
	string& msg = mLogFileReader.getData();

    if(infoMemo->Lines->Count > 1000)
    {
		infoMemo->Clear();
    }

    if(msg.size())
    {
    	infoMemo->Lines->Insert(0, vclstr(msg));
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
    	Close();
    }
}

void TMainForm::setupWindowTitle()
{
	string title = createWindowTitle("ArduinoController", Application);
	this->Caption = vclstr(title);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mAboutBtnClick(TObject *Sender)
{
	//Show about frame
    TAboutArduinoControllerForm* af = new TAboutArduinoControllerForm(this);
    af->ShowModal();
    delete af;
}

BOOL CALLBACK FindOtherWindow(HWND hwnd, LPARAM lParam)
{
	int length = ::GetWindowTextLength( hwnd );
	if(!length )
	    return TRUE;

	TCHAR* buffer;
    buffer = new TCHAR[length + 1];
	GetWindowText(hwnd, buffer, length + 1);

    string s(stdstr(buffer));
	if(startsWith("ArduinoController", s))
	{
		// do something with hwnd here
		gOtherAppWindow = hwnd;
        SetFocus(hwnd);
        delete buffer;

        //Stop enumerating..
		return FALSE;
	}

	return TRUE;
}

void __fastcall TMainForm::MiscBtnClick(TObject *Sender)
{
	TBitBtn* b = dynamic_cast<TBitBtn*>(Sender);
    if(b == mClearLogMemoBtn)
    {
		infoMemo->Clear();
    }
    else if(b == mHideBottomPanelBtn)
    {
		BottomPanel->Visible = false;
	    mShowBottomPanelBtn->Visible = true;
        this->Height -= BottomPanel->Height;
    }
}

void __fastcall TMainForm::mShowBottomPanelBtnClick(TObject *Sender)
{
    this->Height += BottomPanel->Height;
	BottomPanel->Visible = true;
    mShowBottomPanelBtn->Visible = false;
    Splitter1->Top = BottomPanel->Top - 1;
}


