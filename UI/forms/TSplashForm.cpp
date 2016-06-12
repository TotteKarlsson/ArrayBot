#include <vcl.h>
#pragma hdrstop
#include "TSplashForm.h"
#include "mtkVCLUtils.h"
#include "amlApplicationMessages.h"
#include "mtkLogger.h"
#include "amlUtilities.h"
#include "mtkApplicationLicenseController.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SKGenerator"
#pragma resource "*.dfm"
//TSplashForm *SplashForm;

using namespace mtk;

extern string gApplicationRegistryRoot;

//---------------------------------------------------------------------------
__fastcall TSplashForm::TSplashForm(TComponent* Owner)
:
TForm(Owner),
mCanClose(true),
mMinimumTimeShowing(3*Poco::Timespan::SECONDS),
mMessageProcessor(this, mLogMessages),
mMainAppIsRunning(false)
{
    mMessageProcessor.FOnWritingMessage = onWritingLogMessage;
}

__fastcall TSplashForm::~TSplashForm()
{
	closeTimer->Enabled = false;
    mMessageProcessor.stop();
    mShowTimer.stop();
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

void TSplashForm::addLogMessage(const string& msg)
{
    mLogMessages.post(msg);
}

void __fastcall TSplashForm::CreateParams(TCreateParams& Params)
{
  TForm::CreateParams(Params);
  Params.Style &= ~WS_CAPTION;
}

void __fastcall TSplashForm::onWritingLogMessage()
{
    logLabel->Caption = vclstr(mLogMessages.pop());
}

//---------------------------------------------------------------------------
void __fastcall TSplashForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    CanClose =  !isOnShowTime();

    if(mMessageProcessor.isRunning())
    {
        CanClose = false;
        closeTimer->Enabled = true;
    }

    if(mMainAppIsRunning && mLogMessages.getNrOfMessages() == 0)
    {
        mMessageProcessor.stop();
    }
}

//---------------------------------------------------------------------------
void __fastcall TSplashForm::closeTimerTimer(TObject *Sender)
{
	closeTimer->Enabled = false;
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

    if(!mMessageProcessor.isRunning())
    {
        //We may hide/show the form
        mMessageProcessor.start(true);
    }

    if(!mAFrame)
    {
        mtk::ApplicationLicenseController    mLC(gApplicationRegistryRoot);
//--        mLC.
        mAFrame = new TAboutAmalyticoFrame(mLC, RegistrationFile1, this);
        mAFrame->Visible = false;
        mAFrame->Color = this->Color;
        mAFrame->populate();
        mAFrame->Parent =  this;
        mAFrame->AutoSize = true;
        mAFrame->Align = alClient;
        mAFrame->Visible = true;
        mAFrame->UnlockBtn ->Visible = false;
        logLabel->Parent = mAFrame;
    }
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

//---------------------------------------------------------------------------
void __fastcall TSplashForm::FormHide(TObject *Sender)
{
//    mMessageProcessor.pause();
}


