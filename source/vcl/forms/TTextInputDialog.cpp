#include <vcl.h>
#pragma hdrstop
#include "TTextInputDialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"
TTextInputDialog *TextInputDialog;
//---------------------------------------------------------------------------
__fastcall TTextInputDialog::TTextInputDialog(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
