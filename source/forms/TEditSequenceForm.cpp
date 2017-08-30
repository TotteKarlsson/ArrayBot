#include <vcl.h>
#pragma hdrstop
#include "TEditSequenceForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma link "TIntegerLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "TPropertyCheckBox"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------\

TEditSequenceForm *EditSequenceForm;

__fastcall TEditSequenceForm::TEditSequenceForm(TComponent* Owner)
	: TForm(Owner)
{
}


