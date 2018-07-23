#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AXVLC_OCX"
#pragma link "THDMIStreamerFrame"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"

using namespace dsl;

TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner),
    mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "Temp", "Test.log"), &logMsg)
{}

__fastcall TMainForm::~TMainForm()
{

}
//---------------------------------------------------------------------------
//This one is called from the reader thread
void __fastcall TMainForm::logMsg()
{
	if(infoMemo->Lines->Count > 1000)
    {
	    infoMemo->Clear();
    }

    infoMemo->Lines->Insert(0, (vclstr(mLogFileReader.getData())));
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::BitBtn1Click(TObject *Sender)
{
    VLCPlugin21->playlist->clear();
// 	VLCPlugin21->playlist->add(L"file:///c:\\pDisk\\Temp\\Hello2.ts");
 	VLCPlugin21->playlist->add(L"stream://\\\\\\.\\pipe\\DeckLink.ts");
	VLCPlugin21->playlist->play();
    int itemCount = VLCPlugin21->playlist->itemCount;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::VLCPlugin21MediaPlayerEncounteredError(TObject *Sender)
{
	Log(lError) << "There was a problem..";
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::VLCPlugin21MediaPlayerPlaying(TObject *Sender)
{
	Log(lError) << "Playing..";
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::VLCPlugin21MediaPlayerLengthChanged(TObject *Sender,
          long cache)
{
	ProgressBar1->Max = cache;
}

void __fastcall TMainForm::VLCPlugin21MediaPlayerTimeChanged(TObject *Sender, long cache)

{
	ProgressBar1->Position = cache;
}

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
   	mLogFileReader.start(true);
    mLogFileReader.assignOnMessageCallBack(&logMsg);
    gLogger.setLogLevel(LogLevel::lDebug5);
	dsl::gLogger.logToFile(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "Temp", "Test.log"));
	Log(lInfo) << "Logger was setup";

    dsl::gLogger.setLogLevel(lDebug5);
	LogOutput::mShowLogLevel = true;
	LogOutput::mShowLogTime = true;
	LogOutput::mUseLogTabs 	= true;

	VLCPlugin21->ControlInterface->Toolbar = false;
}

void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{

	if(
        mLogFileReader.isRunning() ||
        THDMIStreamerFrame1->isStreamerAlive()
        )
    {
        ShutDownTimer->Enabled = true;
        CanClose = false;
        return;
    }

    CanClose = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ShutDownTimerTimer(TObject *Sender)
{
    ShutDownTimer->Enabled = false;

	//Check for frames to delete
	if(mLogFileReader.isRunning())
    {
    	mLogFileReader.stop();
    }

    if(THDMIStreamerFrame1->isStreamerAlive())
    {
		THDMIStreamerFrame1->shutDownStreamer();
    }

    Close();
}

