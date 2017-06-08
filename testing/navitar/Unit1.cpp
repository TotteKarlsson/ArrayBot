#include <vcl.h>
#pragma hdrstop
#include "mtkUtils.h"
#include "mtkVCLUtils.h"
#include "Unit1.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TForm1 *Form1;

extern string gLogFileName;
extern string gApplicationRegistryRoot;
extern string gLogFileLocation;
extern string gLogFileName;
extern string gAppDataFolder;
extern bool   gAppIsStartingUp;

using namespace mtk;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner),
    mLogFileReader(gLogFileName, &logMsg)
{
   	mLogFileReader.start(true);
}

//This one is called from the reader thread
void __fastcall TForm1::logMsg()
{
    mInfoMemo->Lines->Insert(0, (vclstr(mLogFileReader.getData())));
    mLogFileReader.purge();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
    	Close();
    }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	if(mLogFileReader.isRunning())
    {
        CanClose = false;
        mShutDownTimer->Enabled = true;
        return;
    }

    CanClose = true;

}

//---------------------------------------------------------------------------
void __fastcall TForm1::mShutDownTimerTimer(TObject *Sender)
{
    mShutDownTimer->Enabled = false;
	if(mLogFileReader.isRunning())
    {
		mLogFileReader.stop();
    }


    Close();
}



