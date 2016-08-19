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
mLogFileReader(joinPath(".", gLogFileName), logMsgMethod),
mJoyStickID(1),
mJS(mJoyStickID)
{
    //Associate functions with events
    mJS.setButtonEvents(1, onButton1Down,  onButton1Up    );
    mJS.setButtonEvents(2, onButton2Down,  onButton2Up    );
    mJS.setButtonEvents(3, onButton3Down,  onButton3Up    );
    mJS.setButtonEvents(4, onButton4Down,  onButton4Up    );
    mJS.setButtonEvents(5, onButton5Down,  onButton5Up    );
    mJS.setButtonEvents(6, onButton6Down,  onButton6Up    );
    mJS.setButtonEvents(7, onButton7Down,  onButton7Up    );
    mJS.setButtonEvents(8, onButton8Down,  onButton8Up    );
    mJS.setButtonEvents(9, onButton9Down,  onButton9Up    );
    mJS.setButtonEvents(10,onButton10Down, onButton10Up	  );
    mJS.setButtonEvents(11,onButton11Down, onButton11Up	  );
    mJS.setButtonEvents(12,onButton12Down, onButton12Up	  );
    mJS.setButtonEvents(13,onButton13Down, onButton13Up	  );
    mJS.setButtonEvents(14,onButton14Down, onButton14Up	  );

    mJS.setPOVButtonEvents(1,onPOVButton1Down, onPOVButton1Up	  );
    mJS.setPOVButtonEvents(2,onPOVButton2Down, onPOVButton2Up	  );
    mJS.setPOVButtonEvents(3,onPOVButton3Down, onPOVButton3Up	  );
    mJS.setPOVButtonEvents(4,onPOVButton4Down, onPOVButton4Up	  );

//	mJS.setAxisEvent(1, onX1AxisMove);
//	mJS.setAxisEvent(2, onY1AxisMove);
//
//	mJS.setAxisEvent(3, onX2AxisMove);
//	mJS.setAxisEvent(4, onY2AxisMove);

	//Start JS poll
    mJS.enable();
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
    // this just prints the joystick state on VCL Form->Canvas you can rewrite it to what you want:
    int dy= 20;
    int x= 10;
    int y= 10-dy;
    Canvas->FillRect(TRect(x-20,y,x+200,y+15*dy));

    Canvas->TextOut(x, y+=dy, AnsiString().sprintf("x: %i",		mJS.getX1Pos()));
    Canvas->TextOut(x, y+=dy, AnsiString().sprintf("y: %i",		mJS.getY1Pos()));
    Canvas->TextOut(x, y+=dy, AnsiString().sprintf("z: %i",		mJS.getZ1Pos()));

    Canvas->TextOut(x, y+=dy, AnsiString().sprintf("r: %i",		mJS.getX2Pos()));
    Canvas->TextOut(x, y+=dy, AnsiString().sprintf("u: %i",		mJS.getY2Pos()));
    Canvas->TextOut(x, y+=dy, AnsiString().sprintf("v: %i",		mJS.getZ2Pos()));
    Canvas->TextOut(x, y+=dy, AnsiString().sprintf("b: %i",		mJS.getButtonBits()));
	Canvas->TextOut(x, y+=dy, AnsiString().sprintf("POV: %i",	mJS.getPOVBits()));
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

    if(mJS.isEnabled())
    {
    	CanClose = false;
    }

	if(CanClose == false)
	{
		ShutDownTimer->Enabled = true;
	}
}

//---------------------------------------------------------------------------
void __fastcall TMain::ShutDownTimerTimer(TObject *Sender)
{
	ShutDownTimer->Enabled = false;
	if(mLogFileReader.isRunning())
	{
		Log(lDebug) << "Shutting down log file reader";
		mLogFileReader.stop();
	}

    if(mJS.isEnabled())
    {
    	mJS.disable();
    }

	Close();
}

void TMain::onX1AxisMove(int pos)
{
	Log(lInfo) << "X1 Axis is moving: "<<pos;
}

void TMain::onY1AxisMove(int pos)
{
	Log(lInfo) << "Y1 Axis is moving: "<<pos;
}

void TMain::onX2AxisMove(int pos)
{
	Log(lInfo) << "X2 Axis is moving: "<<pos;
}

void TMain::onY2AxisMove(int pos)
{
	Log(lInfo) << "Y2 Axis is moving: "<<pos;
}

void TMain::onButton1Up()
{
	Button1->Caption ="UP";
}

void TMain::onButton1Down()
{
	Button1->Caption ="DOWN";
}

void TMain::onButton2Up()
{
	Button2->Caption ="UP";
}

void TMain::onButton2Down()
{
	Button2->Caption ="DOWN";
}

void TMain::onButton3Up()
{
	Button3->Caption ="UP";
}

void TMain::onButton3Down()
{
	Button3->Caption ="DOWN";
}

void TMain::onButton4Up()
{
	Button4->Caption ="UP";
}

void TMain::onButton4Down()
{
	Button4->Caption ="DOWN";
}

void TMain::onButton5Up()
{
	Button5->Caption ="UP";
}

void TMain::onButton5Down()
{
	Button5->Caption ="DOWN";
}

void TMain::onButton6Up()
{
	Button6->Caption ="UP";
}

void TMain::onButton6Down()
{
	Button6->Caption ="DOWN";
}

void TMain::onButton7Up()
{
	Button7->Caption ="UP";
}

void TMain::onButton7Down()
{
	Button7->Caption ="DOWN";
}

void TMain::onButton8Up()
{
	Button8->Caption ="UP";
}

void TMain::onButton8Down()
{
	Button8->Caption ="DOWN";
}

void TMain::onButton9Up()
{
	Button9->Caption ="UP";
}

void TMain::onButton9Down()
{
	Button9->Caption ="DOWN";
}

void TMain::onButton10Up()
{
	Button10->Caption ="UP";
}

void TMain::onButton10Down()
{
	Button10->Caption ="DOWN";
}

void TMain::onButton11Up()
{
	Button11->Caption ="UP";
}

void TMain::onButton11Down()
{
	Button11->Caption ="DOWN";
}

void TMain::onButton12Up()
{
	Button12->Caption ="UP";
}

void TMain::onButton12Down()
{
	Button12->Caption ="DOWN";
}

void TMain::onButton13Up()
{
	Button13->Caption ="UP";
}

void TMain::onButton13Down()
{
	Button13->Caption ="DOWN";
}

void TMain::onButton14Up()
{
	Button14->Caption ="UP";
}

void TMain::onButton14Down()
{
	Button14->Caption ="DOWN";
}

void TMain::onPOVButton1Up()
{
	POVButton1->Caption ="UP";
}

void TMain::onPOVButton1Down()
{
	POVButton1->Caption ="DOWN";
}

void TMain::onPOVButton2Up()
{
	POVButton2->Caption ="UP";
}

void TMain::onPOVButton2Down()
{
	POVButton2->Caption ="DOWN";
}

void TMain::onPOVButton3Up()
{
	POVButton3->Caption ="UP";
}

void TMain::onPOVButton3Down()
{
	POVButton3->Caption ="DOWN";
}

void TMain::onPOVButton4Up()
{
	POVButton4->Caption ="UP";
}

void TMain::onPOVButton4Down()
{
	POVButton4->Caption ="DOWN";
}

//---------------------------------------------------------------------------
void __fastcall TMain::Button15Click(TObject *Sender)
{
	mJoyStickID = (mJoyStickID == 1) ? 2 : 1;
    mJS.enableJoyStickWithID(mJoyStickID);
}


