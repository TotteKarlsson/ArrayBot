#ifndef TATDBImagesAndMoviesDataModuleH
#define TATDBImagesAndMoviesDataModuleH
#include <System.Classes.hpp>
#include "DbxDevartSQLite.hpp"
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <Data.DBXMySQL.hpp>
#include <string>
#include "Poco/Mutex.h"
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
	TIntegerField *imageNoteCDSimage_id;
	TIntegerField *imageNoteCDSnote_ID;
	TIntegerField *imageNoteimage_id;
	TIntegerField *imageNotenote_ID;
	TSQLDataSet *sensors;
	TDataSetProvider *DataSetProvider3;
	TClientDataSet *sensorsCDS;
	TDataSource *sensorsDS;
	TIntegerField *sensorsid;
	TIntegerField *sensorsdevice_id;
	TSQLTimeStampField *sensorsdate;
	TFloatField *sensorstemperature;
	TFloatField *sensorshumidity;
	TIntegerField *sensorsCDSdevice_id;
	TSQLTimeStampField *sensorsCDSdate;
	TFloatField *sensorsCDStemperature;
	TFloatField *sensorsCDShumidity;
	TIntegerField *imagesid;
	TStringField *imagesfile_name;
	TSQLTimeStampField *imagesdate;
	TIntegerField *imagesCDSid;
	TStringField *imagesCDSfile_name;
	TSQLTimeStampField *imagesCDSdate;
	TIntegerField *notesQid;
	TMemoField *notesQnote;
	TSQLTimeStampField *notesQcreated_on;
	TIntegerField *notesQcreated_by;
	TIntegerField *notesCDSid;
	TMemoField *notesCDSnote;
	TSQLTimeStampField *notesCDScreated_on;
	TIntegerField *notesCDScreated_by;
        void __fastcall imagesCDSAfterScroll(TDataSet *DataSet);
        void __fastcall SQLConnection1AfterConnect(TObject *Sender);
	void __fastcall imagesCDSdateGetText(TField *Sender, UnicodeString &Text, bool DisplayText);
	void __fastcall notesCDScreated_onGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText);
	void __fastcall notesCDSAfterScroll(TDataSet *DataSet);


	private:	// User declarations

	public:		// User declarations
				__fastcall TImagesAndMoviesDM(TComponent* Owner);
		bool 	__fastcall Connect(const string& DatabaseName);
};
//---------------------------------------------------------------------------
extern PACKAGE TImagesAndMoviesDM *ImagesAndMoviesDM;
//---------------------------------------------------------------------------
#endif
