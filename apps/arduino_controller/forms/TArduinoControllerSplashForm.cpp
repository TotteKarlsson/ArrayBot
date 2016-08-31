#include <vcl.h>
#pragma hdrstop
#include "TArduinoControllerSplashForm.h"
#include "mtkVCLUtils.h"
#include "abApplicationMessages.h"
#include "mtkLogger.h"
#include "UIUtilities.h"
#include "mtkApplicationLicenseController.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace mtk;

extern string gApplicationRegistryRoot;
extern string gLogFileLocation;
extern string gLogFileName;
extern string gAppDataFolder;
//---------------------------------------------------------------------------

__fastcall TArduinoControllerSplashForm::TArduinoControllerSplashForm(TComponent* Owner)
:
	TForm(Owner),
	mCanClose(true),
	mMinimumTimeShowing(3*Poco::Timespan::SECONDS),
	mMainAppIsRunning(false),
	mLogFileReader(joinPath(gAppDataFolder, gLogFileName), logMsg)
{
   	mLogFileReader.start(true);
}

__fastcall TArduinoControllerSplashForm::~TArduinoControllerSplashForm()
{
	closeTimer->Enabled = false;
}

void __fastcall TArduinoControllerSplashForm::logMsg()
{
	string lmsg = mLogFileReader.getData();

    if(::contains("INFO", lmsg))
    {
   		TAboutArduinoServerFrame1->logLabel->Caption = lmsg.c_str();
    }
	mLogFileReader.purge();
    Application->ProcessMessages();
}

//---------------------------------------------------------------------------
void __fastcall TArduinoControllerSplashForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    //Send message to application that the splash form is closing
    if(sendAppMessage(abSplashWasClosed) != true)
    {
        Log(lDebug)<<"Sending UWM_SPLASH_IS_CLOSING was unsuccesful";
    }

	Action = caFree;
}

void TArduinoControllerSplashForm::setShowTime(int ms)
{
    mMinimumTimeShowing = (ms*Poco::Timespan::SECONDS);
}

void __fastcall TArduinoControllerSplashForm::CreateParams(TCreateParams& Params)
{
  TForm::CreateParams(Params);
  Params.Style &= ~WS_CAPTION;
}

//---------------------------------------------------------------------------
void __fastcall TArduinoControllerSplashForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if(isOnShowTime())
    {
    	CanClose = false;
    }
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
void __fastcall TArduinoControllerSplashForm::closeTimerTimer(TObject *Sender)
{
	closeTimer->Enabled = false;
    if(mLogFileReader.isRunning())
    {
    	mLogFileReader.stop();
    }

    Close();
}

//---------------------------------------------------------------------------
void __fastcall TArduinoControllerSplashForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
    if(Key == VK_ESCAPE)
    {
        mShownForAMinimumTime = true;
        this->Visible = false;
    }
}

void __fastcall TArduinoControllerSplashForm::FormShow(TObject *Sender)
{
    mShowTimer.start();
    TAboutArduinoServerFrame1->populate();
}

bool TArduinoControllerSplashForm::isOnShowTime()
{
    Poco::Timespan span = mShowTimer.getElapsedTime();
    bool isIt = span < mMinimumTimeShowing ;
    return isIt;
}

void __fastcall TArduinoControllerSplashForm::Image2Click(TObject *Sender)
{
    setShowTime(0);
    this->Visible = false;
    Close();
}






