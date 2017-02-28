#ifndef iBotDataModuleH
#define iBotDataModuleH
#include <System.Classes.hpp>
#include "DbxDevartSQLite.hpp"
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <SimpleDS.hpp>

//---------------------------------------------------------------------------
class TiBotDataModule : public TDataModule
{
__published:	// IDE-managed Components
	TSQLConnection *SQLConnection1;
	TSQLDataSet *mImageStainSessionDS;
	TDataSetProvider *mImageStainProvider;
	TClientDataSet *mImageStainSessionCDSet;
	TDataSource *mImageStainSessionsDataSource;
	TIntegerField *mImageStainSessionCDSetid;
	TWideMemoField *mImageStainSessionCDSetname;
	TIntegerField *mImageStainSessionCDSetimmunoProtocol;
	TIntegerField *mImageStainSessionDSid;
	TWideMemoField *mImageStainSessionDSname;
	TIntegerField *mImageStainSessionDSimmunoProtocol;
	void __fastcall mImageStainSessionCDSetAfterPost(TDataSet *DataSet);
	void __fastcall SQLConnection1AfterConnect(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TiBotDataModule(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TiBotDataModule *iBotDataModule;
//---------------------------------------------------------------------------
#endif
