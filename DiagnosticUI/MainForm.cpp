#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "TMemoLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMain *Main;

//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
	: TForm(Owner)
{}

//---------------------------------------------------------------------------
void __fastcall TMain::Joystick1Move(TObject *Sender, TButtons Pressed, int X, int Y)
{
	MLog() << "Joystick moved";
}


