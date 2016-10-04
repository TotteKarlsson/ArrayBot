#ifndef TATDBImagesAndMoviesDataModuleH
#define TATDBImagesAndMoviesDataModuleH
#include <System.Classes.hpp>
#include "DbxDevartSQLite.hpp"
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <string>
//---------------------------------------------------------------------------
using std::string;

class TImagesAndMoviesDM : public TDataModule
{
    __published:	// IDE-managed Components
        TSQLDataSet *images;
        TSQLConnection *SQLConnection1;
        TSQLQuery *imageNote;
        TSQLQuery *notesQ;
        TDataSetProvider *DataSetProvider2;
        TDataSetProvider *DataSetProvider1;
        TDataSetProvider *imagesProvider;
        TClientDataSet *imagesCDS;
        TDataSource *imagesDS;
        TDataSource *image_note;
        TClientDataSet *imageNoteCDS;
        TClientDataSet *notesCDS;
        TDataSource *imageNotes;
	TIntegerField *imagesCDSid;
	TWideStringField *imagesCDSfile_name;
	TSQLTimeStampField *imagesCDSdate;
	TIntegerField *imageNoteCDSimage_id;
	TIntegerField *imageNoteCDSnote_ID;
	TIntegerField *notesCDSid;
	TWideMemoField *notesCDSnote;
	TSQLTimeStampField *notesCDScreated_on;
	TWideStringField *notesCDScreated_by;
	TIntegerField *imageNoteimage_id;
	TIntegerField *imageNotenote_ID;
	TIntegerField *imagesid;
	TWideStringField *imagesfile_name;
	TSQLTimeStampField *imagesdate;
	TIntegerField *notesQid;
	TWideMemoField *notesQnote;
	TSQLTimeStampField *notesQcreated_on;
	TWideStringField *notesQcreated_by;
        void __fastcall imagesCDSAfterScroll(TDataSet *DataSet);
        void __fastcall SQLConnection1AfterConnect(TObject *Sender);
	void __fastcall imagesCDSdateGetText(TField *Sender, UnicodeString &Text, bool DisplayText);
	void __fastcall notesCDScreated_onGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText);
	void __fastcall notesCDSAfterScroll(TDataSet *DataSet);


	private:	// User declarations

	public:		// User declarations
				__fastcall TImagesAndMoviesDM(TComponent* Owner);
		bool 	__fastcall Connect(const string& DatabaseFile);
};
//---------------------------------------------------------------------------
extern PACKAGE TImagesAndMoviesDM *ImagesAndMoviesDM;
//---------------------------------------------------------------------------
#endif
