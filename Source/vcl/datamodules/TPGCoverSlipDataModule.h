#ifndef TPGCoverSlipDataModuleH
#define TPGCoverSlipDataModuleH
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>

//---------------------------------------------------------------------------
class PACKAGE TcsPGDM : public TDataModule
{
    __published:	// IDE-managed Components
        TSQLDataSet *csDS;
        TSQLDataSet * csFreshBatchesDS;
        TDataSetProvider *csP;
        TClientDataSet *csCDS;
        TDataSource *csDSource;
        TSQLDataSet *csStatusDS;
        TDataSetProvider *csStatusP;
        TClientDataSet *csStatusCDS;
        TDataSource *csStatusDSource;
        TIntegerField *csStatusCDSid;
	TWideStringField *csStatusCDSstatus;
        TWideMemoField *csStatusCDSnote;
        TSQLDataSet *csTypeDS;
        TDataSetProvider *csTypeP;
        TClientDataSet *csTypeCDS;
        TDataSource *csTypeDSource;
        TIntegerField *csTypeCDSid;
	TWideStringField *csTypeCDStype;
        TWideMemoField *csTypeCDSnote;
        TIntegerField *csStatusDSid;
	TWideStringField *csStatusDSstatus;
        TWideMemoField *csStatusDSnote;
        TIntegerField *csTypeDSid;
	TWideStringField *csTypeDStype;
        TWideMemoField *csTypeDSnote;
        TIntegerField *csCDSid;
        TIntegerField *csCDSstatus;
        TIntegerField *csCDStype;
	TWideStringField *csCDSLStatus;
	TWideStringField *csCDSLType;
        TWideMemoField *csCDSnotes;
	TClientDataSet *csFreshBatchesCDS;
	TIntegerField *csFreshBatchesCDSid;
	TSQLTimeStampField *csFreshBatchesCDSdate_created;
	TIntegerField *csFreshBatchesCDScount;
	TIntegerField *csFreshBatchesCDStype;
	TWideStringField *csFreshBatchesCDSlot_number;
	TIntegerField *csCDSfreshCSBatch;
	TIntegerField *csCDScleanCSBatch;
	TIntegerField *csCDScarboncoatbatch;
	TWideStringField *csCDSfrom_lot;
	TIntegerField *csFreshBatchesCDSbox_number;
	TIntegerField *csDSid;
	TIntegerField *csDSstatus;
	TIntegerField *csDStype;
	TWideMemoField *csDSnotes;
	TIntegerField *csDSfreshCSBatch;
	TIntegerField *csDScleanCSBatch;
	TIntegerField *csDScarboncoatbatch;
	TWideStringField *csDSfrom_lot;
	TIntegerField *csDSsilanizedCSBatch;
	TSQLTimeStampField *csDSmodified;
	TIntegerField *csFreshBatchesDSid;
	TSQLTimeStampField *csFreshBatchesDSdate_created;
	TIntegerField *csFreshBatchesDScount;
	TIntegerField *csFreshBatchesDStype;
	TWideStringField *csFreshBatchesDSlot_number;
	TIntegerField *csFreshBatchesDSbox_number;
	TDataSource *ROnCoverSlipsSource;
	TClientDataSet *ROnCS_CDS;
	TDataSetProvider *RibbonsOnCoverslipsProvider;
	TSQLDataSet *ribbonsOnCoverSlipsDS;
	TWideStringField *ribbonsOnCoverSlipsDSid;
	TIntegerField *ribbonsOnCoverSlipsDSstatus;
	TIntegerField *ribbonsOnCoverSlipsDSblock_id;
	TIntegerField *ribbonsOnCoverSlipsDScutting_order;
	TSmallintField *ribbonsOnCoverSlipsDSnr_of_sections;
	TSQLTimeStampField *ribbonsOnCoverSlipsDScreated_on;
	TSQLTimeStampField *ribbonsOnCoverSlipsDSmodified;
	TIntegerField *ribbonsOnCoverSlipsDScreated_by;
	TIntegerField *ribbonsOnCoverSlipsDScoverslip_id;
	TWideStringField *ROnCS_CDSid;
	TIntegerField *ROnCS_CDSstatus;
	TIntegerField *ROnCS_CDSblock_id;
	TIntegerField *ROnCS_CDScutting_order;
	TSmallintField *ROnCS_CDSnr_of_sections;
	TSQLTimeStampField *ROnCS_CDScreated_on;
	TSQLTimeStampField *ROnCS_CDSmodified;
	TIntegerField *ROnCS_CDScreated_by;
	TIntegerField *ROnCS_CDScoverslip_id;
	TStringField *ROnCS_CDScreated_byL;
	TStringField *ROnCS_CDSstatusL;
        void __fastcall csDSBeforeOpen(TDataSet *DataSet);
        void __fastcall CDSAfterPost(TDataSet *DataSet);
        void __fastcall CDSAfterScroll(TDataSet *DataSet);
	void __fastcall CDSAfterDelete(TDataSet *DataSet);


        private:

        public:
                    __fastcall TcsPGDM(TComponent* Owner);
        	void    __fastcall afterConnect();
            void    __fastcall afterDisConnect();
};

extern PACKAGE TcsPGDM *csPGDM;
#endif
