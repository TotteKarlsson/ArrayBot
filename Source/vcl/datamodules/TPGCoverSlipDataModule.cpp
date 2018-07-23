#pragma hdrstop
#include "TPGCoverSlipDataModule.h"
#include "dslLogger.h"
#include "TPGDataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma resource "*.dfm"
TcsPGDM *csPGDM;
using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TcsPGDM::TcsPGDM(TComponent* Owner)
	: TDataModule(Owner)
{
	if(pgDM)
    {
        csDS->SQLConnection 		    = pgDM->SQLConnection1;
        csStatusDS->SQLConnection 	    = pgDM->SQLConnection1;
        csTypeDS->SQLConnection 	    = pgDM->SQLConnection1;
        csFreshBatchesDS->SQLConnection = pgDM->SQLConnection1;
    }
}

void __fastcall TcsPGDM::afterConnect()
{
	Log(lInfo) << "Initializing coverslip datamodule";
    csCDS->Active 				= true;
    csStatusCDS->Active 		= true;
    csTypeCDS->Active 			= true;
    ROnCS_CDS->Active  			= true;
    csFreshBatchesCDS->Active 	= true;
}

void __fastcall TcsPGDM::afterDisConnect()
{}

//---------------------------------------------------------------------------
void __fastcall TcsPGDM::csDSBeforeOpen(TDataSet *DataSet)
{
//	Log(lInfo) <<"Opening coverslip dataset";
}

//---------------------------------------------------------------------------
void __fastcall TcsPGDM::CDSAfterPost(TDataSet *DataSet)
{
	TClientDataSet* cds = dynamic_cast<TClientDataSet*>(DataSet);

    if(!cds)
    {
    	return;
    }

	cds->ApplyUpdates(0);
    cds->Refresh();
}

void __fastcall TcsPGDM::CDSAfterDelete(TDataSet *DataSet)
{
	TClientDataSet* cds = dynamic_cast<TClientDataSet*>(DataSet);

    if(!cds)
    {
    	return;
    }

	cds->ApplyUpdates(0);
    cds->Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TcsPGDM::CDSAfterScroll(TDataSet *DataSet)
{
 	if(DataSet == csCDS)
    {
        if(ROnCS_CDS->Active)
        {
			ROnCS_CDS->Refresh();
        }
    }
}


