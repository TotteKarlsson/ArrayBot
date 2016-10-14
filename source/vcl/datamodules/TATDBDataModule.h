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
	TIntegerField *blocksCDSid;
	TSQLTimeStampField *blocksCDScreated;
	TIntegerField *blocksCDScreated_by;
	TSQLTimeStampField *blocksCDSmodified;
	TIntegerField *blocksCDSstatus;
	TStringField *ribbonsDSid;
	TIntegerField *ribbonsDSstatus;
	TIntegerField *ribbonsDSblock_id;
	TIntegerField *ribbonsDScutting_order;
	TSmallintField *ribbonsDSnr_of_sections;
	TSQLTimeStampField *ribbonsDScreated;
	TSQLTimeStampField *ribbonsDSmodified;
	TStringField *mRibbonCDSid;
	TIntegerField *mRibbonCDSstatus;
	TIntegerField *mRibbonCDSblock_id;
	TIntegerField *mRibbonCDScutting_order;
	TSmallintField *mRibbonCDSnr_of_sections;
	TSQLTimeStampField *mRibbonCDScreated;
	TSQLTimeStampField *mRibbonCDSmodified;
	TIntegerField *blocksDSid;
	TSQLTimeStampField *blocksDScreated;
	TIntegerField *blocksDScreated_by;
	TSQLTimeStampField *blocksDSmodified;
	TIntegerField *blocksDSstatus;
	TIntegerField *blocksDSfreeze_type;
	TIntegerField *blocksCDSfreeze_type;
	TSQLDataSet *specimentDS;
	TDataSetProvider *specimentProvider;
	TClientDataSet *specimentCDS;
	TDataSource *specimentDSrc;
	TIntegerField *specimentDSid;
	TStringField *specimentDSspeciment_id;
	TIntegerField *specimentDSspecies;
	TStringField *specimentDSadditional_identifier;
	TStringField *specimentDSage;
	TIntegerField *specimentDSlims_number;
	TDateField *specimentDSdeath_date;
	TSmallintField *specimentDSpreprocess_treatment;
	TSmallintField *specimentDSfixative;
	TSmallintField *specimentDSfixation_method;
	TStringField *specimentDSbrain_region_dissection;
	TShortintField *specimentDSpostfix_protocol;
	TDateField *specimentDSdate_received;
	TDateField *specimentDSdate_embedded;
	TShortintField *specimentDScryoprotection_protocol;
	TShortintField *specimentDSfreezing_protocol;
	TShortintField *specimentDSsubstitution_protocol;
	TShortintField *specimentDSinfiltration_protocol;
	TShortintField *specimentDSembedding_protocol;
	TIntegerField *specimentCDSid;
	TStringField *specimentCDSspeciment_id;
	TIntegerField *specimentCDSspecies;
	TStringField *specimentCDSLspecie;
	TStringField *specimentCDSadditional_identifier;
	TStringField *specimentCDSage;
	TIntegerField *specimentCDSlims_number;
	TDateField *specimentCDSdeath_date;
	TSmallintField *specimentCDSpreprocess_treatment;
	TSmallintField *specimentCDSfixative;
	TSmallintField *specimentCDSfixation_method;
	TStringField *specimentCDSbrain_region_dissection;
	TShortintField *specimentCDSpostfix_protocol;
	TDateField *specimentCDSdate_received;
	TDateField *specimentCDSdate_embedded;
	TShortintField *specimentCDScryoprotection_protocol;
	TShortintField *specimentCDSfreezing_protocol;
	TShortintField *specimentCDSsubstitution_protocol;
	TShortintField *specimentCDSinfiltration_protocol;
	TShortintField *specimentCDSembedding_protocol;
	TStringField *specimentCDSLpreproctreat;
	TStringField *blocksDSlabel;
	TStringField *blocksCDSlabel;
	TSimpleDataSet *fixativeTBL;
	TStringField *specimentCDSLFixative;
	TSimpleDataSet *speciesDS;
	TSimpleDataSet *preprocesstreatmentDS;
	TSimpleDataSet *fixationMethodDS;
	TStringField *specimentCDSLfixationMethod;
	TSimpleDataSet *postfix;
	TStringField *specimentCDSLpostfix;
	TSimpleDataSet *cryoprotectionDS;
	TStringField *specimentCDSLcryoprotection;
	TSimpleDataSet *freezeprotocolDS;
	TStringField *specimentCDSLfreezeProtocol;
	TSimpleDataSet *substitutionProtocol;
	TStringField *specimentCDSLsubstitutionProtocol;
	TSimpleDataSet *infiltrationProtocolDS;
	TStringField *specimentCDSLinfiltration;
	TSimpleDataSet *embeddingProtocolDS;
	TStringField *specimentCDSLembedding;
	TSimpleDataSet *blockstatusDS;
	TStringField *blocksCDSlBlockStatus;
	TStringField *blocksCDSLFreezeType;
	void __fastcall cdsAfterPost(TDataSet *DataSet);
	void __fastcall cdsAfterDelete(TDataSet *DataSet);
	void __fastcall cdsAfterScroll(TDataSet *DataSet);
	void __fastcall cdsBeforePost(TDataSet *DataSet);
	void __fastcall mRibbonCDSCalcFields(TDataSet *DataSet);
	void __fastcall SQLConnection1AfterConnect(TObject *Sender);
	void __fastcall abImageDSBeforeScroll(TDataSet *DataSet);
	void __fastcall SQLConnection1BeforeConnect(TObject *Sender);
	void __fastcall cdsAfterRefresh(TDataSet *DataSet);
	void __fastcall fixativeTBLAfterPost(TDataSet *DataSet);






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
