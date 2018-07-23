#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "database/atDBUtils.h"
//#include "Poco/Data/RecordSet.h"
#include "TSettingsForm.h"
#include "dslLogger.h"
#include "TPGDataModule.h"
#include "TPGCoverSlipDataModule.h"
#include "ArrayCamUtils.h"
#include "atVCLUtils.h"
#include "atUtilities.h"
#include "dslVCLUtils.h"

//---------------------------------------------------------------------------
using namespace at;
using namespace dsl;

//---------------------------------------------------------------------------
void __fastcall	TMainForm::afterDBServerConnect(System::TObject* Sender)
{
	Log(lInfo) << "Succesfully connected to DB Server";

	pgDM->afterConnect();
    csPGDM->afterConnect();

    TPGConnectionFrame1->afterConnect();
    RegisterRibbonBtn->Enabled = true;

	//Setup UI
    mUsersCB->KeyValue  	= mDBUserID.getValue();
    BlockIDCB->KeyValue 	= mBlockID.getValue();
    KnifeIDCB->KeyValue 	= mKnifeID.getValue();
    enableDisableGroupBox(BlockSelectionGB, true);
    enableDisableGroupBox(RibbonRegistrationGB, true);
//    enableDisableGroupBox(RibbonsDataGB, true);
}

//---------------------------------------------------------------------------
void __fastcall	TMainForm::afterDBServerDisconnect(System::TObject* Sender)
{
	Log(lInfo) << "Disconnected from the DB Server";
	pgDM->afterDisConnect();

	TPGConnectionFrame1->afterDisconnect();
	RegisterRibbonBtn->Enabled = false;

    enableDisableGroupBox(RibbonRegistrationGB, false);
    enableDisableGroupBox(BlockSelectionGB, false);
//    enableDisableGroupBox(RibbonsDataGB, false);
}

//---------------------------------------------------------------------------
int TMainForm::getCurrentUserID()
{
	return  mUsersCB->KeyValue;
}

int TMainForm::getCurrentCoverSlipID()
{
	return extractCoverSlipID(stdstr(BarcodeLbl->Caption));
}

int TMainForm::getCurrentBlockID()
{
	return pgDM->getCurrentBlockIDFromAllBlocks();
}

int TMainForm::getCurrentKnifeID()
{
	return -1;
}

bool registerVideoInDB(const string& lUUID, const string& videoExtension, int userID, int coverslipID, int blockID, const string& ribbonID)
{
    try
    {
        //Add image to database
        std::auto_ptr <TSQLQuery> tq(new TSQLQuery(NULL));
        tq->SQLConnection = pgDM->SQLConnection1;
        tq->SQLConnection->AutoClone = false;
        stringstream q;
        q <<"INSERT INTO movies (id, fileextension, created_by, coverslip_id, block_id, ribbon_id) VALUES ('"
                    <<lUUID<<"', '"
                    <<videoExtension<<"', '"
                    <<userID<<"', '"
                    <<coverslipID<<"', '"
                    <<blockID<<"', '"
                    <<ribbonID
                    <<"')";

        string s(q.str());
        Log(lDebug) <<"Image Insertion Query: "<<s;
        tq->SQL->Add(q.str().c_str());
        tq->ExecSQL();
        tq->Close();
    }
    catch(const Exception& e)
    {
        Log(lError)<<"Failed registering video in database";
        Log(lError)<<"Exception: "<<stdstr(e.Message);
        return false;
    }

    return true;
}
