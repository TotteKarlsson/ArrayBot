#include <vcl.h>
#pragma hdrstop
#include "TRegisterNewRibbonForm.h"
#include "dslLogger.h"
#include "TPGCoverSlipDataModule.h"
#include "TPGDataModule.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TRegisterNewRibbonForm *RegisterNewRibbonForm;

using namespace dsl;
using std::vector;
//---------------------------------------------------------------------------
__fastcall TRegisterNewRibbonForm::TRegisterNewRibbonForm(TMainForm& mf)
	: TForm(&mf),
    mMainForm(mf),
    mBarCode(""),
    mRibbonID("")
{}

//---------------------------------------------------------------------------
void __fastcall TRegisterNewRibbonForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
    	Close();
    }
}

string TRegisterNewRibbonForm::getRibbonID()
{
	return mRibbonID;
}

void __fastcall TRegisterNewRibbonForm::FormShow(TObject *Sender)
{
    pgDM->ribbonsCDS->First();
    pgDM->ribbonsCDS->Insert();
    pgDM->ribbonsCDS->Edit();
    mRibbonID = getUUID();
    pgDM->ribbonsCDS->FieldByName("id")->Value 				= mRibbonID.c_str();
    pgDM->ribbonsCDS->FieldByName("status")->Value   		= 1;
    pgDM->ribbonsCDS->FieldByName("block_id")->Value 		= pgDM->allBlocksCDS->FieldByName("id")->Value;
    pgDM->ribbonsCDS->FieldByName("cutting_order")->Value  	= mMainForm.RibbonOrderCountLabel->Caption.ToInt();
    pgDM->ribbonsCDS->FieldByName("nr_of_sections")->Value 	= mMainForm.mUC7.getCurrentSectionCount();

    pgDM->ribbonsCDS->FieldByName("created_by")->Value 		= pgDM->usersCDS->FieldByName("id")->Value;
    pgDM->ribbonsCDS->FieldByName("coverslip_id")->Value   	= extractCoverSlipID(mBarCode);
    pgDM->ribbonsCDS->FieldByName("knife_id")->Value   		= -1;
}

void TRegisterNewRibbonForm::setCoverSlipBarcode(const string& barcode)
{
	mBarCode = barcode;
	mCSBarcode->Caption = vclstr(barcode);
}

int TRegisterNewRibbonForm::extractCoverSlipID(const string& bc)
{
	string temp(bc);
    //Make sure first char is a 'C'
    if(!bc.size() || bc[0] != 'C')
    {
    	Log(lError) << bc << " is not a valid barcode!";
        return -1;
    }

	temp.erase(0,1);
    int id = toInt(temp);
    Log(lDebug3) << "Extracted id "<<id<<" from "<<bc;
    return id;
}

//---------------------------------------------------------------------------
void __fastcall TRegisterNewRibbonForm::mOkCancelBtnClick(TObject *Sender)
{
	TArrayBotButton* b = dynamic_cast<TArrayBotButton*>(Sender);
	if(b == mCancelBtn)
    {
		pgDM->ribbonsCDS->Cancel();
	}
    else if (b == mRegisterBtn)
    {
        //Post data
        //Update movie and images table, using current coverslip ID
		pgDM->ribbonsCDS->Post();
   		pgDM->ribbonsCDS->First();
    	if(mRibbonNoteMemo->Lines->Count)
        {
        	Log(lDebug) << "Creating ribbon note";
            createNoteForCurrentRibbon(mRibbonID);
        }

        int csID = extractCoverSlipID(mBarCode);
        if(pgDM->updateMovieTableWithRibbonID(mRibbonID, csID) == 0)
        {
			Log(lWarning) << "No current movie for ribbonID: "<<mRibbonID;
        }
    }
}

bool TRegisterNewRibbonForm::updateCoverSlipStatus()
{
    TSQLQuery* tq = new TSQLQuery(NULL);
    tq->SQLConnection = pgDM->SQLConnection1;
    tq->SQLConnection->AutoClone = false;
    stringstream q;

    //Status 6 <=> post sectioning
    q <<"UPDATE coverslips SET status = 6 WHERE id = "<<extractCoverSlipID(mBarCode);
    tq->SQL->Add(q.str().c_str());
    int rAffected = tq->ExecSQL();
    tq->Close();

	Log(lInfo) <<"Updated status for " <<rAffected<<" coverslip";
    tq->SQL->Clear();
    return true;
}

//---------------------------------------------------------------------------
void __fastcall TRegisterNewRibbonForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Log(lInfo) << "Closed Register new ribbon form. Modal result is: " <<this->ModalResult;
}

//---------------------------------------------------------------------------
bool TRegisterNewRibbonForm::createNoteForCurrentRibbon(const string& rID)
{
    int uID = mMainForm.getCurrentUserID();

    //First insert a new note
    //Then use last insert id for this note to populate the ribbon_note table
    //Finally, select the note
    TSQLQuery* tq = new TSQLQuery(NULL);
    tq->SQLConnection = pgDM->SQLConnection1;
    tq->SQLConnection->AutoClone = false;
    stringstream q;
    vector<string> lines(stdlines(mRibbonNoteMemo->Lines));

    StringList m(lines);
    q <<"INSERT INTO notes (created_by, note) VALUES (:userID, :theNote) RETURNING id";
    tq->SQL->Add(q.str().c_str());
	tq->Params->ParamByName("userID")->AsInteger = uID;
    tq->Params->ParamByName("theNote")->AsString = m.asString('\n').c_str();


    tq->Open();
    int noteID = tq->FieldByName("id")->AsInteger;
    tq->Close();
    tq->SQL->Clear();

    q.str("");
    q << "INSERT INTO ribbon_note (ribbon_id, note_id) VALUES ('"<<rID<<"', "<<noteID<<")";
    tq->SQL->Add(q.str().c_str());
    tq->ExecSQL();
    tq->Close();
    return true;
}

//---------------------------------------------------------------------------
void __fastcall TRegisterNewRibbonForm::miscBtnClick(TObject *Sender)
{
	TArrayBotButton* b = dynamic_cast<TArrayBotButton*>(Sender);
    if(b == mIncrementSectionBtn)
    {
    	int nr = pgDM->ribbonsCDS->FieldByName("nr_of_sections")->Value;
        pgDM->ribbonsCDS->Edit();
        pgDM->ribbonsCDS->FieldByName("nr_of_sections")->Value = (nr + 1);
    }
    else if(b == mDecrementSectionBtn)
    {
    	int nr = pgDM->ribbonsCDS->FieldByName("nr_of_sections")->Value;
        pgDM->ribbonsCDS->Edit();
        pgDM->ribbonsCDS->FieldByName("nr_of_sections")->Value = (nr - 1);
    }
    else if(b == mIncrementCuttingOrderBtn)
    {
    	int nr = pgDM->ribbonsCDS->FieldByName("cutting_order")->Value;
        pgDM->ribbonsCDS->Edit();
        pgDM->ribbonsCDS->FieldByName("cutting_order")->Value = (nr + 1);

    }
    else if(b == mDecrementCuttingOrderBtn)
    {
    	int nr = pgDM->ribbonsCDS->FieldByName("cutting_order")->Value;
        pgDM->ribbonsCDS->Edit();
        pgDM->ribbonsCDS->FieldByName("cutting_order")->Value = (nr - 1);
    }
}

void __fastcall TRegisterNewRibbonForm::FormCreate(TObject *Sender)
{
	//Make any necessary queries..
}

