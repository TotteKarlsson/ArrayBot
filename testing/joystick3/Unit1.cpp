#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{


}


//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
// some (locally) global variable

    // do this in some timer or whatever
    joy.refresh();

    // this just prints the joystick state on VCL Form->Canvas you can rewrite it to what you want:
    int x,y,dy;
    dy=20;
    x=10;
    y=10-dy;
    Canvas->FillRect(TRect(x-20,y,x+200,y+15*dy));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("x: %i",joy.joy_info.dwXpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("y: %i",joy.joy_info.dwYpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("z: %i",joy.joy_info.dwZpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("r: %i",joy.joy_info.dwRpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("u: %i",joy.joy_info.dwUpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("v: %i",joy.joy_info.dwVpos));
    Canvas->TextOut(x,y+=dy,AnsiString().sprintf("b: %i",joy.joy_info.dwButtons));
	Canvas->TextOut(x,y+=dy,AnsiString().sprintf("z: %i",joy.joy_info.dwPOV));
}

