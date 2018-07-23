#ifndef TATDBImagesAndMoviesDataModuleH
#define TATDBImagesAndMoviesDataModuleH
#include <System.Classes.hpp>
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
class PACKAGE TImagesAndMoviesDM : public TDataModule
{
    __published:
	TClientDataSet *MoviesByBlockIDCDS;
	TStringField *MoviesByBlockIDCDSid;
	TSQLTimeStampField *MoviesByBlockIDCDScreated;
	TStringField *MoviesByBlockIDCDSfileextension;
	TIntegerField *MoviesByBlockIDCDScreated_by;
	TIntegerField *MoviesByBlockIDCDScoverslip_id;
	TIntegerField *MoviesByBlockIDCDSblock_id;
	TDataSource *MoviesDataSource;
	TDataSetProvider *DataSetProvider1;
	TSQLDataSet *MoviesByBlockIDDS;
	TStringField *MoviesByBlockIDDSid;
	TSQLTimeStampField *MoviesByBlockIDDScreated;
	TStringField *MoviesByBlockIDDSfileextension;
	TIntegerField *MoviesByBlockIDDScreated_by;
	TIntegerField *MoviesByBlockIDDScoverslip_id;
	TIntegerField *MoviesByBlockIDDSblock_id;
	void __fastcall MoviesByBlockIDCDSAfterScroll(TDataSet *DataSet);
	void __fastcall MoviesByBlockIDDSBeforeOpen(TDataSet *DataSet);
	void __fastcall MoviesByBlockIDCDSAfterRefresh(TDataSet *DataSet);



	private:

	public:
				__fastcall TImagesAndMoviesDM(TComponent* Owner);
		void				afterConnect();

};

extern PACKAGE TImagesAndMoviesDM *ImagesAndMoviesDM;
#endif
