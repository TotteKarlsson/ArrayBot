//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "abCore.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	initABCoreLib();

	HWND hWnd = this->Handle;
    mSound.Create("BUTTON_CLICK_1", hWnd);
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    mSound.Play(0, false);
}
//---------------------------------------------------------------------------
