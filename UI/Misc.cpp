#include "MainForm.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "abAPTMotor.h"
#include "TSplashForm.h"
#include "TRibbonLifterFrame.h"
#include "abXYZUnitFrame.h"
#include "TAboutArrayBotForm.h"
using namespace mtk;

static HWND gOtherAppWindow = NULL;
extern TSplashForm*  gSplashForm;
//---------------------------------------------------------------------------
void __fastcall TMain::checkForDevicesExecute(TObject *Sender)
{
	if(!buildDeviceList())
    {
    	Log(lError) <<"Failed building device list";
        return;
    }

    for(int i = 0; i < 90; i++)
    {
		StringList serials = getSerialsForDeviceType((DeviceTypeID) i);
        for(u_int j = 0; j < serials.count(); j++)
        {
            Log(lInfo) <<"Found device of type '"<<::toString((DeviceTypeID) i)<<"' with serial: " <<serials[j];
        }
    }
}

void __fastcall TMain::FrameClosed(TObject *Sender)
{
	;
}

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
    //Timer fire    if(
	if(mAB->getJoyStick().isEnabled())
    {
    	CanClose = false;
    }
	else if(mAB->isActive())
    {
    	CanClose = false;
    }
    else if(UIUpdateTimer->Enabled)
    {
    	CanClose = false;
    }
   	else if(gSplashForm && gSplashForm->isOnShowTime())
	{
		CanClose = false;
	}
	else if(TRibbonLifterFrame::gIsFrameOpen)
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

void __fastcall TMain::BitBtn3Click(TObject *Sender)
{
	infoMemo->Clear();
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
