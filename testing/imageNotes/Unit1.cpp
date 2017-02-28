#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DbxDevartSQLite"
#pragma resource "*.dfm"
TForm1 *Form1;

extern bool gAppIsStartingUp;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{}
//---------------------------------------------------------------------------

void __fastcall TForm1::imagesCDSAfterScroll(TDataSet *DataSet)
{
	if(gAppIsStartingUp == false)
	{
		//Update customers orders
		TField* field = imagesCDS->FieldByName("id");
		imageNote->Active = false;
        imageNotesQ->Active = false;
		if(field)
		{
			String val = field->AsString;
			imageNote->SQL->Text = "SELECT * from abImage_note where image_id ='" + val + "'";
            imageNotesQ->SQL->Text = " SELECT * FROM note WHERE id IN (SELECT note_id FROM abImage_note WHERE image_id = '" + val + "')";
			imageNoteCDS->Refresh();
            imageNotesCDS->Refresh();
		}
		imageNote->Active = true;
        imageNotesQ->Active = true;


//	 	SELECT * FROM note WHERE id IN (SELECT note_id FROM abImage_note WHERE image_id = ""


	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
	gAppIsStartingUp = false;
}
//---------------------------------------------------------------------------

