#include <vcl.h>
#pragma hdrstop
#include "TCoverSlipScanFrame.h"
#include "TPGCoverSlipDataModule.h"
#include "TPGDataModule.h"
#include "dslVCLUtils.h"
#include "atQueryBuilder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "TMoviesFrame"
#pragma link "TRibbonNotesFrame"
#pragma resource "*.dfm"
TCoverSlipScanFrame *CoverSlipScanFrame;

using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TCoverSlipScanFrame::TCoverSlipScanFrame(TComponent* Owner)
	: TFrame(Owner)
{
}

void TCoverSlipScanFrame::populate(int csID, const Poco::Path& p)
{
	mCSID = csID;
    CSIDE->setValue(mCSID);
    if(pgDM && pgDM->isConnected())
    {
        enableDisableGroupBox(GroupBox1, true);
    }
    else
    {
        enableDisableGroupBox(GroupBox1, false);
        return;
    }

	SQLDataSet1->Active    		= false;
    ClientDataSet1->Active 		= false;

	SQLDataSet1->Params->ParamByName("csID")->AsInteger = csID;

    //Execute Query
    SQLDataSet1->Open();

    if(SQLDataSet1->Fields->Count)
    {
        SQLDataSet1->Active = true;
        ClientDataSet1->Active = true;
        ClientDataSet1->Refresh();
    }

    if(!ClientDataSet1->FieldByName("block_id")->IsNull && !ClientDataSet1->FieldByName("ribbon_id")->IsNull)
    {
        //Get blockID and ribbonID
        int blockID = ClientDataSet1->FieldByName("block_id")->AsInteger;
        String ribbonID = ClientDataSet1->FieldByName("ribbon_id")->AsString;
        MoviesFrame1->populate(blockID, stdstr(ribbonID), p);
	    //Populate notes frame
    	TRibbonNotesFrame1->populate(stdstr(ClientDataSet1->FieldByName("ribbon_id")->AsString));
    }
}


