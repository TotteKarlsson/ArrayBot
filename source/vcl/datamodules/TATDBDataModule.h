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
	TSQLDataSet *specimenDS;
	TDataSetProvider *specimenProvider;
	TClientDataSet *specimenCDS;
	TDataSource *specimenDSrc;
	TStringField *specimenCDSspeciment_id;
	TStringField *specimenCDSLspecie;
	TStringField *specimenCDSadditional_identifier;
	TStringField *specimenCDSage;
	TIntegerField *specimenCDSlims_number;
	TDateField *specimenCDSdeath_date;
	TSmallintField *specimenCDSpreprocess_treatment;
	TSmallintField *specimenCDSfixative;
	TSmallintField *specimenCDSfixation_method;
	TStringField *specimenCDSbrain_region_dissection;
	TShortintField *specimenCDSpostfix_protocol;
	TDateField *specimenCDSdate_received;
	TDateField *specimenCDSdate_embedded;
	TShortintField *specimenCDScryoprotection_protocol;
	TShortintField *specimenCDSfreezing_protocol;
	TShortintField *specimenCDSsubstitution_protocol;
	TShortintField *specimenCDSinfiltration_protocol;
	TShortintField *specimenCDSembedding_protocol;
	TStringField *specimenCDSLpreproctreat;
	TStringField *blocksCDSlabel;
	TSimpleDataSet *fixativeTBL;
	TStringField *specimenCDSLFixative;
	TSimpleDataSet *speciesDS;
	TSimpleDataSet *preprocesstreatmentDS;
	TSimpleDataSet *fixationMethodDS;
	TStringField *specimenCDSLfixationMethod;
	TSimpleDataSet *postfix;
	TStringField *specimenCDSLpostfix;
	TSimpleDataSet *cryoprotectionDS;
	TStringField *specimenCDSLcryoprotection;
	TSimpleDataSet *freezeprotocolDS;
	TStringField *specimenCDSLfreezeProtocol;
	TSimpleDataSet *substitutionProtocol;
	TStringField *specimenCDSLsubstitutionProtocol;
	TSimpleDataSet *infiltrationProtocolDS;
	TStringField *specimenCDSLinfiltration;
	TSimpleDataSet *embeddingProtocolDS;
	TStringField *specimenCDSLembedding;
	TSimpleDataSet *blockstatusDS;
	TIntegerField *blocksCDSprocess_id;
	TIntegerField *specimenCDSprocess_id;
	TSimpleDataSet *processIDDS;
	TIntegerField *blocksCDSLprocess_id;
	TSmallintField *blocksCDSstatus;
	TIntegerField *specimenDSprocess_id;
	TStringField *specimenDSspecimen_id;
	TSmallintField *specimenDSspecie;
	TStringField *specimenDSadditional_identifier;
	TStringField *specimenDSage;
	TIntegerField *specimenDSlims_number;
	TDateField *specimenDSdeath_date;
	TSmallintField *specimenDSpreprocess_treatment;
	TSmallintField *specimenDSfixative;
	TSmallintField *specimenDSfixation_method;
	TStringField *specimenDSbrain_region_dissection;
	TSmallintField *specimenDSpostfix_protocol;
	TDateField *specimenDSdate_received;
	TDateField *specimenDSdate_embedded;
	TSmallintField *specimenDScryoprotection_protocol;
	TSmallintField *specimenDSfreezing_protocol;
	TSmallintField *specimenDSsubstitution_protocol;
	TSmallintField *specimenDSinfiltration_protocol;
	TSmallintField *specimenDSembedding_protocol;
	TStringField *blocksCDSLBlockStatus;
	TSmallintField *blocksCDSserial;
	TStringField *blocksCDSCBlockLabel;
	TSQLDataSet *documentsDS;
	TDataSetProvider *documentsProvider;
	TClientDataSet *documentsCDS;
	TDataSource *documentsDSource;
	TIntegerField *documentsDSid;
	TBlobField *documentsDSdocument;
	TStringField *documentsDStype;
	TStringField *documentsDSdocument_name;
	TIntegerField *documentsCDSid;
	TStringField *documentsCDSdocument_name;
	TBlobField *documentsCDSdocument;
	TStringField *documentsCDStype;
	TSmallintField *substitutionProtocolid;
	TStringField *substitutionProtocolprotocol;
	TIntegerField *substitutionProtocoldocument_id;
	TStringField *substitutionProtocolLDocument;
	TIntegerField *blocksDSid;
	TIntegerField *blocksDSprocess_id;
	TSQLTimeStampField *blocksDScreated;
	TIntegerField *blocksDScreated_by;
	TSQLTimeStampField *blocksDSmodified;
	TSmallintField *blocksDSstatus;
	TStringField *blocksDSlabel;
	TSmallintField *blocksDSserial;
	void __fastcall cdsAfterPost(TDataSet *DataSet);
	void __fastcall cdsAfterDelete(TDataSet *DataSet);
	void __fastcall cdsAfterScroll(TDataSet *DataSet);
	void __fastcall cdsBeforePost(TDataSet *DataSet);
	void __fastcall mRibbonCDSCalcFields(TDataSet *DataSet);
	void __fastcall SQLConnection1AfterConnect(TObject *Sender);

	void __fastcall SQLConnection1BeforeConnect(TObject *Sender);
	void __fastcall cdsAfterRefresh(TDataSet *DataSet);
 	void __fastcall fixativeTBLAfterPost(TDataSet *DataSet);
	void __fastcall blocksCDSCalcFields(TDataSet *DataSet);
	void __fastcall blocksCDSblockLabelGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText);
	void __fastcall TimeStampGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText);
	void __fastcall cdsBeforeRefresh(TDataSet *DataSet);
	void __fastcall specimenCDSBeforeClose(TDataSet *DataSet);

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
