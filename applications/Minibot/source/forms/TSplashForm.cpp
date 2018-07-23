#include <vcl.h>
#pragma hdrstop
#include "TSplashForm.h"
#include "dslVCLUtils.h"
#include "../abApplicationMessages.h"
#include "dslLogger.h"
#include "../UIUtilities.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TSplashForm::TSplashForm(const string& logFileName, TComponent* Owner)
:
	TForm(Owner),
	mCanClose(true),
	mMinimumTimeShowing(5*Poco::Timespan::SECONDS),
	mMainAppIsRunning(false),
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", logFileName), logMsg)
{
   	mLogFileReader.start(true);
}

__fastcall TSplashForm::~TSplashForm()
{
	closeTimer->Enabled = false;
}

void __fastcall TSplashForm::logMsg()
{
	string lmsg = mLogFileReader.getData();

	lmsg = stripToAlpha(lmsg);
	TAboutArrayBotFrame1->logLabel->Caption = lmsg.c_str();
    TAboutArrayBotFrame1->logLabel->Color = clRed;

//	mLogFileReader.purge();
    Application->ProcessMessages();
}

//---------------------------------------------------------------------------
void __fastcall TSplashForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    Log(lDebug)<<"In SplashForms FormClose";
    if(sendAppMessage(atSplashWasClosed) != true)
    {
        Log(lDebug)<<"Sending messge from Splash was unsuccesful";
    }
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

//---------------------------------------------------------------------------
void __fastcall TSplashForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if(isOnShowTime() || mLogFileReader.isRunning())
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
