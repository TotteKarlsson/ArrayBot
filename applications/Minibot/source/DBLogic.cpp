#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "database/atDBUtils.h"
#include "atVCLUtils.h"
//#include "TSettingsForm.h"
#include "dslLogger.h"
#include "TPGDataModule.h"
#include "TPGCoverSlipDataModule.h"

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

