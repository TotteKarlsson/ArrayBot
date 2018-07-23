#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "TPGDataModule.h"
#include "TPGCoverSlipDataModule.h"
#include "TPGImagesAndMoviesDataModule.h"

using namespace dsl;

//---------------------------------------------------------------------------
void __fastcall TMainForm::NavigatorBeforeAction(TObject *Sender, TNavigateBtn Button)
{
	TDBNavigator* n = dynamic_cast<TDBNavigator*>(Sender);

    if(n == BlocksNavigator)
    {
        switch(Button)
        {
            case TNavigateBtn::nbDelete:
    //             if(MessageDlg("Deleting this block will delete all associated ribbons and notes!\nContinue?", mtWarning, TMsgDlgButtons() << mbOK<<mbCancel, 0) == mrCancel)
                 {
                    Abort();
                 }

    //			int blockID = pgDM->blocksCDS->FieldByName("id")->Value;
    //            mServerDBSession.deleteNotesForBlock(blockID);
    //            mServerDBSession.deleteRibbonsForBlock(blockID);
            break;
        }
    }
    else if(n == CSFreshBatchNavigator)
    {
        switch(Button)
        {
            case TNavigateBtn::nbDelete:
            	int mRes = MessageDlg("Deleting a batch will delete all coverslips in the batch.\n\nThis works only if no ribbons are associated with the coverslip", mtWarning, TMsgDlgButtons() << mbOK<<mbCancel, 0);
                if(mRes == mrCancel)
                {
                	Abort();
                }
            break;
        }
    }
}

void __fastcall TMainForm::NavigatorClick(TObject *Sender, TNavigateBtn Button)
{
	TDBNavigator* n = dynamic_cast<TDBNavigator*>(Sender);
    TDateTime dateTime(Now());

    if(n == UsersNavigator)
    {
        switch(Button)
        {
            case TNavigateBtn::nbInsert:
                pgDM->usersCDS->FieldValues["user_name"] = "New User";
            break;
            case TNavigateBtn::nbApplyUpdates:  break;
            case TNavigateBtn::nbRefresh:

            break;
        }
    }
    else if(n == SpecimenNavigator)
    {
		switch(Button)
        {
            case TNavigateBtn::nbInsert:
                if(UsersCB->KeyValue != -1)
                {
                    pgDM->specimenCDS->FieldByName("animal_id")->Value = "XXXX-XX";
                    pgDM->specimenCDS->FieldByName("entered_by")->Value = UsersCB->KeyValue;

                    if(SpecieRG->ItemIndex != -1)
                    {
                        string specie = stdstr(SpecieRG->Items->Strings[SpecieRG->ItemIndex]);
                        pgDM->specimenCDS->FieldByName("specie")->Value = pgDM->getIDForSpecie(specie);
                    }

                    TDateTime dt(Now());
                    pgDM->specimenCDS->FieldByName("intake_date")->Value = dt.CurrentDate();

                    //Open new specimen form
                    openSpecimenForm();

                }
                else
                {
                    MessageDlg("Please select a user before inserting new data ", mtInformation, TMsgDlgButtons() << mbOK, 0);
                }
            break;


            case TNavigateBtn::nbApplyUpdates:
                try
                {
                    Log(lWarning) << "About to delete a row";
                }
                catch(...)
                {}
            break;
        }

    }

    else if(n == SlicesNavigator)
    {
		switch(Button)
        {
            case TNavigateBtn::nbInsert:
                if(UsersCB->KeyValue != -1)
                {
                    pgDM->slicesCDS->FieldByName("specimen_id")->Value = pgDM->specimenCDS->FieldByName("id")->Value;
                    pgDM->slicesCDS->FieldByName("entered_by")->Value = UsersCB->KeyValue;

                    //Open new slice form
                    openSlicesForm();
                }
                else
                {
                    MessageDlg("Select a user before inserting new data ", mtInformation, TMsgDlgButtons() << mbOK, 0);
                }
            break;

            case TNavigateBtn::nbRefresh:            break;
        }
    }
    else if(n == BlocksNavigator)
    {
        switch(Button)
        {
            case TNavigateBtn::nbDelete:                 pgDM->blocksCDS->Refresh();            break;

            case TNavigateBtn::nbInsert:

                if(UsersCB->KeyValue != -1)
                {
                    pgDM->blocksCDS->FieldByName("entered_by")->Value             = UsersCB->KeyValue;
                    pgDM->blocksCDS->FieldByName("entered_on")->Value             = dateTime.CurrentDate();
                    pgDM->blocksCDS->FieldValues["slice_id"] 			          = pgDM->slicesCDS->FieldByName("id")->AsInteger;
                    pgDM->blocksCDS->FieldValues["serial"] 	 		              = pgDM->blocksCDS->RecordCount + 1;
                    pgDM->blocksCDS->FieldByName("date_embedded")->Value 		  = dateTime.CurrentDate();

                    if(pgDM->blocksCDS->RecordCount < 1)
                    {
                        pgDM->blocksCDS->FieldValues["status"] 	 				  = 0;
                        pgDM->blocksCDS->FieldValues["cryoprotection_protocol"]   = 0;
                        pgDM->blocksCDS->FieldValues["freezing_protocol"] 	 	  = 0;
                        pgDM->blocksCDS->FieldValues["substitution_protocol"]     = 0;
                        pgDM->blocksCDS->FieldValues["infiltration_protocol"]     = 0;
                        pgDM->blocksCDS->FieldValues["embedding_protocol"]    	  = 0;
                    }
                    else
                    {
                        //Clone the cursor
                        TClientDataSet *clone = new TClientDataSet(NULL);
                        clone->CloneCursor(pgDM->blocksCDS, false, false);
                        clone->Last();
                        pgDM->blocksCDS->FieldValues["status"] 	 				  = clone->FieldByName("status")->Value;
                        pgDM->blocksCDS->FieldValues["cryoprotection_protocol"]   = clone->FieldByName("cryoprotection_protocol")->Value;
                        pgDM->blocksCDS->FieldValues["freezing_protocol"] 	 	  = clone->FieldByName("freezing_protocol")->Value;
                        pgDM->blocksCDS->FieldValues["substitution_protocol"]     = clone->FieldByName("substitution_protocol")->Value;
                        pgDM->blocksCDS->FieldValues["infiltration_protocol"]     = clone->FieldByName("infiltration_protocol")->Value;
                        pgDM->blocksCDS->FieldValues["embedding_protocol"]    	  = clone->FieldByName("embedding_protocol")->Value;
                        clone->Close();
                        delete clone;
                    }

                    //Open form
                    openBlocksForm();
                }
                else
                {
                    MessageDlg("Select a user before inserting new data ", mtInformation, TMsgDlgButtons() << mbOK, 0);
                }

            break;
            case TNavigateBtn::nbPost:        		break;
            case TNavigateBtn::nbRefresh:        	Log(lInfo) << "Refreshed Blocks Dataset"; 		break;
        }
    }
    else if(n == BlockNotesNavigator)
    {
        switch(Button)
        {
            case TNavigateBtn::nbInsert:
                {
                    int uID = pgDM->usersCDS->FieldByName("id")->AsInteger;
                    int blockID = pgDM->blocksCDSid->Value;
                    string note("Block Note..");
                    pgDM->addNoteForBlock(blockID, uID, note);
                    pgDM->blockNotesCDS->Refresh();
                    pgDM->blockNotesCDS->Last();
                }
            break;

            case TNavigateBtn::nbDelete:        break;
        }
    }

    else if(n == RibbonsNavigator)
    {
    	switch(Button)
        {
        	case TNavigateBtn::nbDelete:        break;
        	case TNavigateBtn::nbInsert:
            {
    	        pgDM->ribbonsCDS->FieldByName("id")->Value 				= getUUID().c_str();
    	        pgDM->ribbonsCDS->FieldByName("block_id")->Value 		= pgDM->blocksCDS->FieldByName("id")->Value;
                pgDM->ribbonsCDS->FieldByName("created_by")->Value  	= UsersCB->KeyValue;
                pgDM->ribbonsCDS->FieldByName("coverslip_id")->Value  	= csPGDM->csCDS->FieldByName("id")->Value;
                pgDM->ribbonsCDS->FieldByName("created_on")->Value      = dateTime.CurrentDate();
                pgDM->ribbonsCDS->Post();
    			pgDM->ribbonsCDS->First();
            }
            break;
            case TNavigateBtn::nbPost:            															break;
            case TNavigateBtn::nbRefresh:            	Log(lInfo) << "Refreshed Ribbons Dataset";     		break;
        }
    }
    else if(n == RibbonNotesNavigator)
    {
        switch(Button)
        {
            case TNavigateBtn::nbInsert:
            {
                int uID = getCurrentUserID();
                String rID = pgDM->ribbonsCDSid->Value;
                string note("Ribbon Note..");
                pgDM->addNoteForRibbon(stdstr(rID), uID, note);
                pgDM->ribbonNotesCDS->Refresh();
                pgDM->ribbonNotesCDS->Last();
            }
            break;

            case TNavigateBtn::nbDelete:        break;
        }
    }
    else if(n == CSNavigator)
    {
        switch(Button)
        {
            case TNavigateBtn::nbInsert:
                csPGDM->csCDS->FieldValues["status"] 	= 1;
                csPGDM->csCDS->FieldValues["type"] 	= 1;
                csPGDM->csCDS->Post();
                csPGDM->csCDS->First();
        	break;
        }
    }

    else if(n == CSFreshBatchNavigator)
    {
        switch(Button)
        {
       		case TNavigateBtn::nbDelete:

            break;

        }
    }
    else if(n == KnifeNotesNavigator)
    {
        switch(Button)
        {
            case TNavigateBtn::nbInsert:
            {
                int uID = getCurrentUserID();
                int ID = pgDM->knifesCDSid->Value;
                string note("Knife Note..");
                pgDM->addNoteForKnife(ID, uID, note);
                pgDM->knifeNotesCDS->Refresh();
                pgDM->knifeNotesCDS->Last();
            }
            break;

            case TNavigateBtn::nbDelete:        break;
        }
    }

    else if(n == settingsNavigator)
    {
        switch(Button)
        {
        }
    }

    else
    {
    	Log(lWarning) << "This navigators click was not handled in code";
    }
}

