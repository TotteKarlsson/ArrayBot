#ifndef TPGImagesAndMoviesDataModuleH
#define TPGImagesAndMoviesDataModuleH
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include "DbxDevartPostgreSQL.hpp"
#include <string>
#include "Poco/Mutex.h"
//---------------------------------------------------------------------------
using std::string;
class PACKAGE TPGImagesAndMoviesDM : public TDataModule
{
    __published:
	TClientDataSet *MoviesByBlockIDCDS;
	TDataSource *MoviesDataSource;
	TDataSetProvider *DataSetProvider1;
	TSQLDataSet *MoviesByBlockIDDS;
	TWideStringField *MoviesByBlockIDDSid;
	TSQLTimeStampField *MoviesByBlockIDDScreated;
	TWideStringField *MoviesByBlockIDDSfileextension;
	TIntegerField *MoviesByBlockIDDScreated_by;
	TIntegerField *MoviesByBlockIDDScoverslip_id;
	TIntegerField *MoviesByBlockIDDSblock_id;
	TWideStringField *MoviesByBlockIDCDSid;
	TSQLTimeStampField *MoviesByBlockIDCDScreated;
	TWideStringField *MoviesByBlockIDCDSfileextension;
	TIntegerField *MoviesByBlockIDCDScreated_by;
	TIntegerField *MoviesByBlockIDCDScoverslip_id;
	TIntegerField *MoviesByBlockIDCDSblock_id;
	void __fastcall MoviesByBlockIDCDSAfterScroll(TDataSet *DataSet);
	void __fastcall MoviesByBlockIDDSBeforeOpen(TDataSet *DataSet);
	void __fastcall MoviesByBlockIDCDSAfterRefresh(TDataSet *DataSet);



	private:

	public:
				__fastcall TPGImagesAndMoviesDM(TComponent* Owner);
		void				afterConnect();

};

extern PACKAGE TPGImagesAndMoviesDM *PGImagesAndMoviesDM;
#endif
