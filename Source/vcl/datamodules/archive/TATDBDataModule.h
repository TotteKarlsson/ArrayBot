#ifndef TATDBDataModuleH
#define TATDBDataModuleH
#include <System.Classes.hpp>
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
class PACKAGE TatdbDM : public TDataModule
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
	TSQLDataSet *slicesDS;
	TDataSetProvider *slicesProvider;
	TClientDataSet *slicesCDS;
	TDataSource *slicesDataSource;
	TStringField *blocksCDSlabel;
	TSimpleDataSet *fixativeTBL;
	TSimpleDataSet *speciesDS;
	TSimpleDataSet *preprocesstreatmentDS;
	TSimpleDataSet *fixationMethodDS;
	TSimpleDataSet *postfix;
	TSimpleDataSet *cryoprotectionDS;
	TSimpleDataSet *freezeprotocolDS;
	TSimpleDataSet *substitutionProtocol;
	TSimpleDataSet *infiltrationProtocolDS;
	TSimpleDataSet *embeddingProtocolDS;
	TSimpleDataSet *blockstatusDS;
	TSmallintField *blocksCDSstatus;
	TStringField *blocksCDSLBlockStatus;
	TSmallintField *blocksCDSserial;
	TStringField *blocksCDSCBlockLabel;
	TSmallintField *substitutionProtocolid;
	TStringField *substitutionProtocolprotocol;
	TIntegerField *substitutionProtocoldocument_id;
	TDateField *blocksCDSdate_embedded;
	TSmallintField *blocksCDScryoprotection_protocol;
	TSmallintField *blocksCDSfreezing_protocol;
	TSmallintField *blocksCDSsubstitution_protocol;
	TSmallintField *blocksCDSinfiltration_protocol;
	TSmallintField *blocksCDSembedding_protocol;
	TStringField *blocksCDSLCryoProtectionProtocol;
	TStringField *blocksCDSLFreezingProtocol;
	TStringField *blocksCDSLSubstitutionProtocol;
	TStringField *blocksCDSLInfiltrationProtocol;
	TStringField *blocksCDSLEmbeddingProtocol;
	TStringField *blocksCDSLUser;
	TIntegerField *ribbonsDScreated_by;
	TIntegerField *mRibbonCDScreated_by;
	TIntegerField *ribbonsDScoverslip_id;
	TIntegerField *mRibbonCDScoverslip_id;
	TDataSource *ROnCoverSlipsSource;
	TClientDataSet *ROnCS_CDS;
	TDataSetProvider *RibbonsOnCoverslipsProvider;
	TSQLDataSet *ribbonsOnCoverSlipsDS;
	TSQLDataSet *settingsDS;
	TDataSetProvider *settingsProvider;
	TClientDataSet *settingsCDS;
	TIntegerField *settingsCDSid;
	TMemoField *settingsCDSlabel_printer_command;
	TIntegerField *settingsDSid;
	TMemoField *settingsDSlabel_printer_command;
	TClientDataSet *specimenCDS;
	TSQLDataSet *specimenDS;
	TDataSetProvider *specimenProvider;
	TIntegerField *specimenCDSid;
	TStringField *specimenCDSanimal_id;
	TSQLTimeStampField *specimenCDSintake_date;
	TSmallintField *specimenCDSspecie;
	TIntegerField *specimenCDSentered_by;
	TIntegerField *specimenDSid;
	TStringField *specimenDSanimal_id;
	TSQLTimeStampField *specimenDSintake_date;
	TSmallintField *specimenDSspecie;
	TIntegerField *specimenDSentered_by;
	TStringField *specimenCDSLUser;
	TStringField *specimenCDSLSpecie;
	TSimpleDataSet *culturedTimePoints;
	TDataSource *specimenDataSource;
	TIntegerField *blocksDSid;
	TIntegerField *blocksDSslice_id;
	TSmallintField *blocksDSstatus;
	TIntegerField *blocksDSentered_by;
	TStringField *blocksDSlabel;
	TSmallintField *blocksDSserial;
	TDateField *blocksDSdate_embedded;
	TSmallintField *blocksDScryoprotection_protocol;
	TSmallintField *blocksDSfreezing_protocol;
	TSmallintField *blocksDSsubstitution_protocol;
	TSmallintField *blocksDSinfiltration_protocol;
	TSmallintField *blocksDSembedding_protocol;
	TStringField *specimenDSsummary;
	TStringField *specimenCDSsummary;
	TIntegerField *slicesDSid;
	TIntegerField *slicesDSspecimen_id;
	TStringField *slicesDSvirus;
	TStringField *slicesDSbrain_region_dissection;
	TIntegerField *slicesDSentered_by;
	TIntegerField *slicesDSculture_time;
	TIntegerField *slicesCDSid;
	TIntegerField *slicesCDSspecimen_id;
	TStringField *slicesCDSvirus;
	TStringField *slicesCDSbrain_region_dissection;
	TIntegerField *slicesCDSculture_time;
	TIntegerField *slicesCDSentered_by;
	TSmallintField *slicesDSpreprocess_treatment_protocol;
	TSmallintField *slicesDSfixative_protocol;
	TSmallintField *slicesDSfixation_protocol;
	TSmallintField *slicesDSpostfix_protocol;
	TSmallintField *slicesCDSpreprocess_treatment_protocol;
	TSmallintField *slicesCDSfixative_protocol;
	TSmallintField *slicesCDSfixation_protocol;
	TSmallintField *slicesCDSpostfix_protocol;
	TStringField *slicesCDSLPre;
	TStringField *slicesCDSfixative_protocolL;
	TStringField *slicesCDSpostfix_protocolL;
	TStringField *slicesCDSfixation_protocolL;
	TStringField *slicesCDSentered_byL;
	TStringField *slicesCDSculture_timeL;
	TIntegerField *blocksCDSslice_id;
	TIntegerField *blocksCDSentered_by;
	TSQLTimeStampField *blocksDSentered_on;
	TSQLTimeStampField *blocksCDSentered_on;
	TStringField *slicesDSvirus_dilution;
	TStringField *slicesCDSvirus_dilution;
	TSQLDataSet *blockIDsDS;
	TDataSetProvider *blockIdsProvider;
	TClientDataSet *blockIDSCDS;
	TIntegerField *IntegerField4;
	TDataSource *blockIDsDataSource;
	TIntegerField *blockIDsDSid;
	TSimpleDataSet *ribbonStatusDS;
	TStringField *mRibbonCDSstatusL;
	TStringField *mRibbonCDScreated_byL;
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
	void __fastcall slicesCDSBeforeClose(TDataSet *DataSet);
	void __fastcall slicesCDSAfterClose(TDataSet *DataSet);
	void __fastcall slicesCDSAfterOpen(TDataSet *DataSet);

	private:

    protected:
    	string		                    mDataBaseUser;
    	string		                    mDataBaseUserPassword;
       	string		                    mDataBase;
        string 		                    mDBIP;

	public:
				__fastcall           	TatdbDM(TComponent* Owner);
				__fastcall           	~TatdbDM();
		bool 	__fastcall           	connect(const string& ip, const string& dbUser, const string& dbPassword, const string& db);
        void    __fastcall           	afterConnect();
        void    __fastcall           	afterDisConnect();
        int		__fastcall				getCurrentBlockID();
        int 	__fastcall				getIDForSpecie(const string& specie);
		String __fastcall 				createBlockLabel();
        bool	__fastcall				insertBlockNote(int userID, int blockID, const string& note);
        bool	__fastcall				insertRibbonNote(int userID, const string& ribbonID, const string& note);
};

extern PACKAGE TatdbDM *atdbDM;

#endif
