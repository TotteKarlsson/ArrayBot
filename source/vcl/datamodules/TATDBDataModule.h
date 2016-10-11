#ifndef TATDBDataModuleH
#define TATDBDataModuleH
#include <System.Classes.hpp>
#include "DbxDevartSQLite.hpp"
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <SimpleDS.hpp>
#include <Data.DBXMySQL.hpp>
#include <string>

using std::string;
//!The TatDM class encapsulate data exchange with the ATDB database
//---------------------------------------------------------------------------
class TatdbDM : public TDataModule
{
__published:	// IDE-managed Components
	TSQLConnection *SQLConnection1;
	TDataSource *blocksDataSource;
	TClientDataSet *blocksCDS;
	TDataSetProvider *blocksProvider;
	TSQLDataSet *blocksDS;
	TSQLDataSet *usersDS;
	TDataSetProvider *usersProvider;
	TClientDataSet *usersCDS;
	TDataSource *usersDataSource;
	TDataSource *blockNotesDSource;
	TDataSetProvider *blockNotesProvider;
	TClientDataSet *blockNotesCDS;
	TSQLDataSet *noteDS;
	TDataSetProvider *notesProvider;
	TClientDataSet *notesCDS;
	TDataSource *notesDSource;
	TDataSetProvider *mRibbonProvider;
	TClientDataSet *mRibbonCDS;
	TDataSource *mRibbonDSource;
	TIntegerField *usersDSid;
	TStringField *usersDSuser_name;
	TSQLTimeStampField *usersDScreated;
	TIntegerField *usersCDSid;
	TStringField *usersCDSuser_name;
	TSQLTimeStampField *usersCDScreated;
	TIntegerField *blockNotesCDSid;
	TMemoField *blockNotesCDSnote;
	TSQLTimeStampField *blockNotesCDScreated_on;
	TIntegerField *blockNotesCDScreated_by;
	TIntegerField *notesCDSid;
	TMemoField *notesCDSnote;
	TSQLTimeStampField *notesCDScreated_on;
	TIntegerField *notesCDScreated_by;
	TDataSetProvider *ribbonNotesProvider;
	TClientDataSet *ribbonNotesCDS;
	TDataSource *ribbonNotesDSource;
	TSQLDataSet *ribbonsDS;
	TSQLDataSet *blockNotesDS;
	TIntegerField *blockNotesDSid;
	TMemoField *blockNotesDSnote;
	TSQLTimeStampField *blockNotesDScreated_on;
	TIntegerField *blockNotesDScreated_by;
	TSQLDataSet *ribbonNotesDS;
	TIntegerField *ribbonNotesDSid;
	TMemoField *ribbonNotesDSnote;
	TSQLTimeStampField *ribbonNotesDScreated_on;
	TIntegerField *ribbonNotesDScreated_by;
	TIntegerField *ribbonNotesCDSid;
	TMemoField *ribbonNotesCDSnote;
	TSQLTimeStampField *ribbonNotesCDScreated_on;
	TIntegerField *ribbonNotesCDScreated_by;
	TIntegerField *blocksDSid;
	TSQLTimeStampField *blocksDScreated;
	TIntegerField *blocksDScreated_by;
	TSQLTimeStampField *blocksDSmodified;
	TIntegerField *blocksDSstatus;
	TMemoField *blocksDSlabel;
	TIntegerField *blocksCDSid;
	TSQLTimeStampField *blocksCDScreated;
	TIntegerField *blocksCDScreated_by;
	TSQLTimeStampField *blocksCDSmodified;
	TIntegerField *blocksCDSstatus;
	TMemoField *blocksCDSlabel;
	TStringField *ribbonsDSid;
	TIntegerField *ribbonsDSstatus;
	TIntegerField *ribbonsDSblock_id;
	TIntegerField *ribbonsDScutting_order;
	TSmallintField *ribbonsDSnr_of_sections;
	TSQLTimeStampField *ribbonsDScreated;
	TSQLTimeStampField *ribbonsDSmodified;
	void __fastcall usersCDSAfterPost(TDataSet *DataSet);
	void __fastcall usersCDSAfterDelete(TDataSet *DataSet);
	void __fastcall usersCDSAfterScroll(TDataSet *DataSet);
	void __fastcall usersCDSAfterCancel(TDataSet *DataSet);
	void __fastcall blocksCDSAfterPost(TDataSet *DataSet);
	void __fastcall blocksCDSAfterDelete(TDataSet *DataSet);
	void __fastcall blocksCDSAfterScroll(TDataSet *DataSet);
	void __fastcall blockNotesCDSAfterPost(TDataSet *DataSet);
	void __fastcall blocksCDSBeforePost(TDataSet *DataSet);
	void __fastcall mRibbonCDSAfterPost(TDataSet *DataSet);
	void __fastcall mRibbonCDSBeforePost(TDataSet *DataSet);
	void __fastcall mRibbonCDSAfterDelete(TDataSet *DataSet);
	void __fastcall mRibbonCDSCalcFields(TDataSet *DataSet);
	void __fastcall SQLConnection1AfterConnect(TObject *Sender);
	void __fastcall abImageDSBeforeScroll(TDataSet *DataSet);
	void __fastcall SQLConnection1BeforeConnect(TObject *Sender);
	void __fastcall blockNotesCDSAfterDelete(TDataSet *DataSet);
	void __fastcall blockNotesCDSBeforeDelete(TDataSet *DataSet);
	void __fastcall blocksCDSlabelGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText);
	void __fastcall blockNotesCDSAfterScroll(TDataSet *DataSet);
	void __fastcall mRibbonCDSAfterScroll(TDataSet *DataSet);
	void __fastcall usersDataSourceDataChange(TObject *Sender, TField *Field);




	private:	// User declarations
    protected:
    	string		mDataBaseUser;
    	string		mDataBaseUserPassword;
       	string		mDataBase;
        string 		mDBIP;

	public:
				__fastcall TatdbDM(TComponent* Owner);

		bool 	__fastcall connect(const string& ip, const string& dbUser, const string& dbPassword, const string& db);
        void    __fastcall afterConnect();
        void    __fastcall afterDisConnect();

};

extern PACKAGE TatdbDM *atdbDM;

#endif
