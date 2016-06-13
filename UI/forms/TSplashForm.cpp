#include <vcl.h>
#pragma hdrstop
#include "TSplashForm.h"
#include "mtkVCLUtils.h"
#include "abApplicationMessages.h"
#include "mtkLogger.h"
#include "abUIUtilities.h"
#include "mtkApplicationLicenseController.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace mtk;

extern string gApplicationRegistryRoot;
extern string gLogFileLocation;
extern string gLogFileName;
//---------------------------------------------------------------------------
__fastcall TSplashForm::TSplashForm(TComponent* Owner)
:
	TForm(Owner),
	mCanClose(true),
	mMinimumTimeShowing(5*Poco::Timespan::SECONDS),
	mMainAppIsRunning(false),
	logMsgMethod(&logMsg),
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", gLogFileName), logMsgMethod)
{
   	mLogFileReader.start(true);
}

__fastcall TSplashForm::~TSplashForm()
{
	closeTimer->Enabled = false;
}

bool startsWith(const string& prefix, const string& theStr)
{
	if (theStr.find(prefix) == 0)
	{
		return true;
	}
	return false;
}

void __fastcall TSplashForm::logMsg()
{
	string lmsg = mLogFileReader.getData();

    if(::startsWith("INFO", lmsg))
    {
   		TAboutArrayBotFrame1->logLabel->Caption = lmsg.c_str();
    }
	mLogFileReader.purge();
    Application->ProcessMessages();
//    sleep(100);
}


//---------------------------------------------------------------------------
void __fastcall TSplashForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    //Send message to application that the splash form is closing
    HWND hWnd = Application->MainForm->Handle;
    if(sendAppMessage(amSplashWasClosed) != true)
    {
        Log(lDebug)<<"Sending UWM_SPLASH_IS_CLOSING was unsuccesful";
    }

	Action = caFree;
}

void TSplashForm::setShowTime(int ms)
{
    mMinimumTimeShowing = (ms*Poco::Timespan::SECONDS);
}


void __fastcall TSplashForm::CreateParams(TCreateParams& Params)
{
  TForm::CreateParams(Params);
  Params.Style &= ~WS_CAPTION;
}

void __fastcall TSplashForm::onWritingLogMessage()
{
//    TAboutArrayBotFrame1->logLabel->Caption = vclstr(mLogMessages.pop());

}

//---------------------------------------------------------------------------
void __fastcall TSplashForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if(isOnShowTime())
    {
    	CanClose = false;
    }
//    else if(mMessageProcessor.isRunning())
//    {
//        CanClose = false;
//    }
    else if(mLogFileReader.isRunning())
    {
        CanClose = false;
    }
    else
    {
    	CanClose = true;
    }

    if(CanClose == false)
    {
    	closeTimer->Enabled = true;
    }

}

//---------------------------------------------------------------------------
void __fastcall TSplashForm::closeTimerTimer(TObject *Sender)
{
	closeTimer->Enabled = false;
//    if(mMessageProcessor.isRunning())
//    {
//    	mMessageProcessor.stop();
//    }
    if(mLogFileReader.isRunning())
    {
    	mLogFileReader.stop();
    }

    Close();
}

//---------------------------------------------------------------------------
void __fastcall TSplashForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
    if(Key == VK_ESCAPE)
    {
        mShownForAMinimumTime = true;
        this->Visible = false;
    }
}

void __fastcall TSplashForm::FormShow(TObject *Sender)
{
    mShowTimer.start();
    TAboutArrayBotFrame1->populate();
//    if(!mMessageProcessor.isRunning())
//    {
//        //We may hide/show the form
//        mMessageProcessor.start(true);
//    }

//    if(!mAFrame)
//    {
//        mAFrame = new TAboutArrayBotFrame(this);
//        mAFrame->Visible = false;
//        mAFrame->Color = this->Color;
//        mAFrame->populate();
//        mAFrame->Parent =  this;
//        mAFrame->AutoSize = true;
//        mAFrame->Align = alClient;
//        mAFrame->Visible = true;
//        logLabel->Parent = mAFrame;
//    }
}

bool TSplashForm::isOnShowTime()
{
    Poco::Timespan span = mShowTimer.getElapsedTime();
    bool isIt = span < mMinimumTimeShowing ;
    return isIt;
}

void __fastcall TSplashForm::Image2Click(TObject *Sender)
{
    setShowTime(0);
    this->Visible = false;
    Close();
}





