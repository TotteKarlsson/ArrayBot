//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "atCore.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner),
    mSound("")
{
	initABCoreLib();

	HWND hWnd = this->Handle;
    mSound.create("BUTTON_CLICK_1", hWnd);
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    mSound.play(0, false);
}
//---------------------------------------------------------------------------
