//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TPufferArduinoBoard.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "mtkSTDStringEdit"
#pragma link "TArduinoBoardFrame"
#pragma link "TIntegerLabeledEdit"
#pragma resource "*.dfm"
TArduinoBoardFrame1 *ArduinoBoardFrame1;
//---------------------------------------------------------------------------
__fastcall TArduinoBoardFrame1::TArduinoBoardFrame1(TComponent* Owner)
	: TArduinoBoardFrame(Owner)
{
}
//---------------------------------------------------------------------------
