#include <vcl.h>
#pragma hdrstop
#include "TYesNoForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TYesNoForm *YesNoForm;

//---------------------------------------------------------------------------
__fastcall TYesNoForm::TYesNoForm(TComponent* Owner)
	: TForm(Owner)
{
}

