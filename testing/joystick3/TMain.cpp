#include <vcl.h>
#pragma hdrstop
#include "TMain.h"
#include "TMemoLogger.h"
#include "mtkUtils.h"
#include "mtkVCLUtils.h"
#include "mtkLogger.h"

using namespace mtk;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMain *Main;
extern string gLogFileName;
//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
:
TForm(Owner),
logMsgMethod(&logMsg),
mLogFileReader(joinPath(".", gLogFileName), logMsgMethod)
{


}

//This one is called from the reader thread
void __fastcall TMain::logMsg()
{
    infoMemo->Lines->Add(vclstr(mLogFileReader.getData()));
    mLogFileReader.purge();
}

//---------------------------------------------------------------------------
void __fastcall TMain::Timer1Timer(TObject *Sender)
{
// some (locally) global variable

    // do this in some timer or whatever
    mJS.refresh();

    // this just prints the joystick state on VCL Form->Canvas you can rewrite it to what you want:
    int dy= 20;
    int x= 10;
    int y= 10-dy;
    Canvas->FillRect(TRect(x-20,y,x+200,y+15*dy));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("x: %i",mJS.mJoyInfo.dwXpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("y: %i",mJS.mJoyInfo.dwYpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("z: %i",mJS.mJoyInfo.dwZpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("r: %i",mJS.mJoyInfo.dwRpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("u: %i",mJS.mJoyInfo.dwUpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("v: %i",mJS.mJoyInfo.dwVpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("b: %i",mJS.mJoyInfo.dwButtons));
	Canvas->TextOut(x,y+=dy,AnsiString().sprintf("z: %i",mJS.mJoyInfo.dwPOV));


	 mJS.OnButton1Down 	= onButton1Down;
	 mJS.OnButton1Up 	= onButton1Up;
}

void  TMain::onButton1Down()
{
	Button1->Caption ="DOWN";
}

void  TMain::onButton1Up()
{
	Button1->Caption ="UP";
}


//---------------------------------------------------------------------------
void __fastcall TMain::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
    	Close();
    }
}


void __fastcall TMain::FormShow(TObject *Sender)
{
	TMemoLogger::mMemoIsEnabled = true;
    mLogFileReader.start();
}


void __fastcall TMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	if(mLogFileReader.isRunning())
    {
    	CanClose = false;
    }

	if(CanClose == false)
	{
		ShutDownTimer->Enabled = true;
	}

}


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TMain::ShutDownTimerTimer(TObject *Sender)
{
	ShutDownTimer->Enabled = false;
	if(mLogFileReader.isRunning())
	{
		Log(lDebug) << "Shutting down log file reader";
		mLogFileReader.stop();
	}

	Close();
}


