#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)//,
//    mJoyStick()
{


}


//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
// some (locally) global variable

    // do this in some timer or whatever
    mJS.refresh();

    // this just prints the joystick state on VCL Form->Canvas you can rewrite it to what you want:
    int x,y,dy;
    dy=20;
    x=10;
    y=10-dy;
    Canvas->FillRect(TRect(x-20,y,x+200,y+15*dy));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("x: %i",mJS.mJoyInfo.dwXpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("y: %i",mJS.mJoyInfo.dwYpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("z: %i",mJS.mJoyInfo.dwZpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("r: %i",mJS.mJoyInfo.dwRpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("u: %i",mJS.mJoyInfo.dwUpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("v: %i",mJS.mJoyInfo.dwVpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("b: %i",mJS.mJoyInfo.dwButtons));
	Canvas->TextOut(x,y+=dy,AnsiString().sprintf("z: %i",mJS.mJoyInfo.dwPOV));
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
    	Close();
    }
}


