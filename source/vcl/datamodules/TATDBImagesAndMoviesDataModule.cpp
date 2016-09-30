#pragma hdrstop
#include "TATDBImagesAndMoviesDataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma link "DbxDevartSQLite"
#pragma resource "*.dfm"
TImagesAndMoviesDM *ImagesAndMoviesDM;
extern bool gAppIsStartingUp;
//---------------------------------------------------------------------------
__fastcall TImagesAndMoviesDM::TImagesAndMoviesDM(TComponent* Owner)
	: TDataModule(Owner)
{}

//---------------------------------------------------------------------------
void __fastcall TImagesAndMoviesDM::imagesCDSAfterScroll(TDataSet *DataSet)
{
	if(gAppIsStartingUp == false)
	{
        imageNoteCDS->CancelUpdates();
		notesCDS->CancelUpdates();
		//Update customers orders
		TField* field = imagesCDS->FieldByName("id");
		imageNote->Active = false;
        notesQ->Active = false;
		if(field)
		{
			String val = field->AsString;
			imageNote->SQL->Text = "SELECT * from abImage_note where image_id ='" + val + "'";
            notesQ->SQL->Text = "SELECT * FROM note WHERE id IN (SELECT note_id FROM abImage_note WHERE image_id = '" + val + "')";
			imageNoteCDS->Refresh();
            notesCDS->Refresh();
		}
		imageNote->Active = true;
        notesQ->Active = true;
    }
}

