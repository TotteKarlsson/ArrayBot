//---------------------------------------------------------------------------

#ifndef TATDBImagesAndMoviesDataModuleH
#define TATDBImagesAndMoviesDataModuleH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "DbxDevartSQLite.hpp"
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
//---------------------------------------------------------------------------
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
	void __fastcall imagesCDSAfterScroll(TDataSet *DataSet);


private:	// User declarations
public:		// User declarations
	__fastcall TImagesAndMoviesDM(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TImagesAndMoviesDM *ImagesAndMoviesDM;
//---------------------------------------------------------------------------
#endif
