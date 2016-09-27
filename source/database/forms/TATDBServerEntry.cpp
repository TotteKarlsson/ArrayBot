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


