#include "MainForm.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "abAPTMotor.h"
#include "TSplashForm.h"
#include "TAboutArrayBotForm.h"
using namespace mtk;

static HWND gOtherAppWindow = NULL;
extern TSplashForm*  gSplashForm;
//---------------------------------------------------------------------------
void __fastcall TMain::ShutDownTimerTimer(TObject *Sender)
{
	ShutDownTimer->Enabled = false;
	if(mLogFileReader.isRunning())
	{
		Log(lDebug) << "Shutting down log file reader";
		mLogFileReader.stop();
	}

    if(UIUpdateTimer->Enabled)
    {
        UIUpdateTimer->Enabled = false;
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
    //Timer fire    if(
   	if(gSplashForm && gSplashForm->isOnShowTime())
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

void __fastcall	TMain::OnException()
{
	Log(lInfo) << "Exception TMain::OnException()";
}

//---------------------------------------------------------------------------
void __fastcall TMain::ApplicationEvents1Exception(TObject *Sender, Exception *E)
{
	Log(lInfo) << "Application Exception...."<<stdstr(E->Message);
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormShow(TObject *Sender)
{
	this->Height = this->Height - 1;
	this->Height = this->Height + 1;
}

//This one is called from the reader thread
void __fastcall TMain::logMsg()
{
    infoMemo->Lines->Insert(0, (vclstr(mLogFileReader.getData())));
    mLogFileReader.purge();
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
    	Close();
    }
}

void TMain::setupWindowTitle()
{
	string title = createWindowTitle("ArrayBot", Application);
	this->Caption = vclstr(title);
}

//---------------------------------------------------------------------------
void __fastcall TMain::mAboutBtnClick(TObject *Sender)
{
	//Show about frame
    TAboutArrayBotForm* af = new TAboutArrayBotForm(this);
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
	if(startsWith(s, "ArrayBot"))
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
