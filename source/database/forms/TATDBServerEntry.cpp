#include <vcl.h>
#pragma hdrstop
#include "TATDBServerEntry.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TATDBServerEntry *ATDBServerEntry;
//---------------------------------------------------------------------------

__fastcall TATDBServerEntry::TATDBServerEntry(ATDBServerSession& dbs, TComponent* Owner)
	: TForm(Owner),
    mServerSession(dbs)
{

}


//---------------------------------------------------------------------------
void __fastcall TATDBServerEntry::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key == vkEscape)
    {
    	Close();
    }

}


