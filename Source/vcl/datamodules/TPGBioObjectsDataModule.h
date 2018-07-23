#ifndef TPGBioObjectsDataModuleH
#define TPGBioObjectsDataModuleH
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <SimpleDS.hpp>
#include <System.Classes.hpp>
#include "DbxDevartPostgreSQL.hpp"
#include "database/atDBCredentials.h"
#include "dslStringList.h"

using dsl::StringList;
using std::string;

//!The TpgDM class encapsulate data exchange with the ATDB database
//---------------------------------------------------------------------------
class PACKAGE TpgBioObjectsDM : public TDataModule
{
__published:	// IDE-managed Components
	TSQLConnection *SQLConnection1;
	TDataSetProvider *bioObjectCollectionProvider;
	TClientDataSet *bioObjectCollectionCDS;
	TSQLDataSet *bioObjectCollectionDS;
	TDataSetProvider *data_setProvider;
	TClientDataSet *data_setCDS;
	TSQLDataSet *data_setDS;
	TDataSetProvider *volumeProvider;
	TClientDataSet *volumeCDS;
	TSQLDataSet *volumeDS;
	TDataSource *data_setDataSource;
	TDataSource *volumeDataSource;
	TDataSource *bioObjectCollectionDataSource;
	TWideStringField *bioObjectCollectionCDSname;
	TIntegerField *bioObjectCollectionCDSvolume_id;
	TWideStringField *bioObjectCollectionCDStype;
	TIntegerField *bioObjectCollectionCDSid;
	TWideStringField *bioObjectCollectionCDSsynapse_collection_type;
	TIntegerField *bioObjectCollectionCDSlink_id;
	TWideStringField *bioObjectCollectionDSname;
	TIntegerField *bioObjectCollectionDSvolume_id;
	TWideStringField *bioObjectCollectionDStype;
	TIntegerField *bioObjectCollectionDSid;
	TWideStringField *bioObjectCollectionDSsynapse_collection_type;
	TIntegerField *bioObjectCollectionDSlink_id;
	TSQLDataSet *bioobjectDS;
	TDataSetProvider *bioObjectProvider;
	TClientDataSet *bioObjectCDS;
	TDataSource *bioobjectDataSource;
	TIntegerField *bioObjectCDSobject_collection_id;
	TWideStringField *bioObjectCDStype;
	TIntegerField *bioObjectCDSid;
	TWideStringField *bioObjectCDSoid;
	TWideMemoField *bioObjectCDSareas;
	void __fastcall cdsAfterPost(TDataSet *DataSet);
	void __fastcall cdsAfterDelete(TDataSet *DataSet);
	void __fastcall cdsAfterScroll(TDataSet *DataSet);
	void __fastcall cdsBeforePost(TDataSet *DataSet);
	void __fastcall SQLConnection1AfterConnect(TObject *Sender);

	void __fastcall SQLConnection1BeforeConnect(TObject *Sender);
	void __fastcall cdsAfterRefresh(TDataSet *DataSet);
	void __fastcall cdsBeforeRefresh(TDataSet *DataSet);
	void __fastcall SQLConnection1AfterDisconnect(TObject *Sender);
	void __fastcall cdsbeforeDelete(TDataSet *DataSet);
	void __fastcall bioObjectCollectionCDSAfterRefresh(TDataSet *DataSet);
	void __fastcall bioObjectCDSBeforeRefresh(TDataSet *DataSet);
	void __fastcall bioObjectCDSBeforeScroll(TDataSet *DataSet);
	void __fastcall bioObjectCDSBeforeGetRecords(TObject *Sender, OleVariant &OwnerData);




	private:

    protected:
	    DBCredentials					mCredentials;

	public:
				__fastcall           	TpgBioObjectsDM(TComponent* Owner);
				__fastcall           	~TpgBioObjectsDM();
        void    __fastcall           	afterConnect();
        void    __fastcall           	afterDisConnect();
        bool							isConnected();

        StringList 						getTableNames();
};

extern PACKAGE TpgBioObjectsDM *pgBioObjectsDM;

#endif
