#include <vcl.h>
#pragma hdrstop
#include "TPGDataModule.h"
#include "TRibbonNotesFrame.h"
#include "dslStringUtils.h"
#include "dslVCLUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TRibbonNotesFrame *RibbonNotesFrame;
using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TRibbonNotesFrame::TRibbonNotesFrame(TComponent* Owner)
	: TFrame(Owner)
{
}

void TRibbonNotesFrame::populate(const string& ribbonID)
{
	NotesForRibbonDS->ParamByName("ribbon_id")->AsString = ribbonID.c_str();

    NotesForRibbonDS->Active = true;
    NotesForRibbonCDS->Active = true;
    NotesForRibbonCDS->Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TRibbonNotesFrame::RibbonNotesNavigatorClick(TObject *Sender,
          TNavigateBtn Button)
{
	//Assign user in case notes are added..
    	TDBNavigator* n = dynamic_cast<TDBNavigator*>(Sender);

    if(n == RibbonNotesNavigator)
    {
        switch(Button)
        {
         	case TNavigateBtn::nbInsert:
            {
                int uID = pgDM->usersCDS->FieldByName("id")->AsInteger;
                String rID = NotesForRibbonDS->ParamByName("ribbon_id")->AsString;
                string note("Ribbon Note..");
                pgDM->addNoteForRibbon(stdstr(rID), uID, note);
                NotesForRibbonCDS->Refresh();
                NotesForRibbonCDS->Last();
            }
        }
    }
}


