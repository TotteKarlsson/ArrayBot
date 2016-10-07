#include <vcl.h>
#pragma hdrstop
#include "mtkLogger.h"
#include "mtkMoleculixException.h"
#include "mtkSQLiteException.h"
#include "mtkSQLiteQuery.h"
#include "mtkSQLiteTable.h"
#include "mtkStringUtils.h"
#include "mtkVCLUtils.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Glob.h"
#include "Poco/Timezone.h"
#include "TamFileEditor.h"
#include "TMainForm.h"
#include "TMemoLogger.h"
#include "TShowFileContentForm.h"
#include "TATDBDataModule.h"
#include "mtkUtils.h"
#include "abVCLUtils.h"
#include "database/abDBUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "mtkIniFileC"
#pragma link "TIntegerLabeledEdit"
#pragma link "pBarcode1D"
#pragma link "pUPC"
#pragma link "pUPCA"
#pragma link "pCode39"
#pragma link "pDBBarcode1D"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"

TMainForm *MainForm;
using namespace mtk;
using namespace ab;
//using namespace Poco;

extern string gLogFileName;
extern string gApplicationRegistryRoot;
extern string gDefaultAppTheme;
extern string gFullDateTimeFormat;
extern bool gIsDevelopmentRelease;
//extern TSplashForm*  gSplashForm;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TRegistryForm(gApplicationRegistryRoot, "MainForm", Owner),

    mBottomPanelHeight(205),
    mMainTabIndex(0),
    mSplashProperties(gApplicationRegistryRoot, "Splash"),
    mShowSplashOnStartup(true),
    mLogLevel(lAny),
    mIsStyleMenuPopulated(false),
    gCanClose(true),
    logMsgMethod(&logMsg),
    mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "atDB", gLogFileName), logMsgMethod),
    mLocalDBFile(""),
	mServerDBSession("atdb")
{
    //Close any dataconnection created by stupid TSQLConnection
    mTempFileFolder = joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "atDB");
    TMemoLogger::mMemoIsEnabled = false;
    setupIniFile();
    setupAndReadIniParameters();

}

//This one is called from the reader thread
void __fastcall TMainForm::logMsg()
{
    infoMemo->Lines->Add(vclstr(mLogFileReader.getData()));
    mLogFileReader.purge();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mUsersCBClick(TObject *Sender)
{
//	Log(lInfo) <<"Selected: " << stdstr(mUsersCB->ListSource->DataSet->FieldByName("user_name")->AsString);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mUsersNavigatorBeforeAction(TObject *Sender, TNavigateBtn Button)
{
	switch(Button)
    {
    	case TNavigateBtn::nbInsert:
//	        mUserCreatedE->Text = getFormattedDateTimeString(gFullDateTimeFormat).c_str();
//            mUserNameE->Text = "New User";
        break;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mUsersNavigatorClick(TObject *Sender, TNavigateBtn Button)
{
//	switch(Button)
//    {
//    	case TNavigateBtn::nbInsert:            mUserNameE->Text = "New User";        break;
//        case TNavigateBtn::nbApplyUpdates:      									  break;
//        case TNavigateBtn::nbRefresh: 												  break;
//        default:
//		    mUsersCB->KeyValue = atdbDM->usersClientDataSet->FieldByName("id")->AsInteger;
//        break;
//    }
}

void __fastcall TMainForm::mBlocksNavigatorClick(TObject *Sender, TNavigateBtn Button)
{
	switch(Button)
    {
    	case TNavigateBtn::nbDelete:        break;

    	case TNavigateBtn::nbInsert:
//        	if(!mUsersCB->KeyValue.IsNull())
//            {
//	        	atdbDM->blocksCDS->FieldByName("created_by")->Value = mUsersCB->KeyValue;
//				mBlocksNavigator->BtnClick( Data::Bind::Controls::nbPost);
//            }
//            else
//            {
//            	MessageDlg("Select a user before inserting blocks..", mtInformation, TMsgDlgButtons() << mbOK, 0);
//            	Log(lError) << "Bad...";
//            }
        break;
        case TNavigateBtn::nbPost:
//	        mBlocksNavigator->BtnClick( Data::Bind::Controls::nbRefresh);
//	        mBlocksNavigator->BtnClick( Data::Bind::Controls::nbRefresh);
//	        mBlocksNavigator->BtnClick( Data::Bind::Controls::nbLast);
//	        mBlocksNavigator->BtnClick( Data::Bind::Controls::nbRefresh);
        break;
        case TNavigateBtn::nbRefresh:
        	Log(lInfo) << "Refreshed Blocks Dataset";
 		break;
        default:
//		    mUsersCB->KeyValue = atdbDM->usersClientDataSet->FieldByName("id")->AsInteger;
        break;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mUserNameEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkReturn)
    {
		atdbDM->usersCDS->Post();
    }
}

//---------------------------------------------------------------------------
//void __fastcall TMainForm::Button3Click(TObject *Sender)
//{
////    stringstream q;
////    int nID = atdbDM->blockNotesDSet->FieldByName("id")->AsInteger;
////
////    stringstream memo;
////    for(int i = 0; i <  mBlockNoteMemo->Lines->Count; i++)
////    {
////        memo<<stdstr(mBlockNoteMemo->Lines->Strings[i]);
////        if(i < mBlockNoteMemo->Lines->Count -1 )
////        {
////            memo<<endl;
////        }
////    }
////    string s(memo.str());
////    q << "UPDATE note SET note=\""<< s <<"\" WHERE id=\""<<nID<<"\"";
////    Log(lInfo) << q.str();
////
////    atdbDM->updateNoteQ->SQL->Clear();
////    atdbDM->updateNoteQ->SQL->Add(q.str().c_str());
////    atdbDM->updateNoteQ->ExecSQL(true);
//}
//
//---------------------------------------------------------------------------
void __fastcall TMainForm::mDeleteNoteBtnClick(TObject *Sender)
{
//    int uID 	= atdbDM->usersClientDataSet->FieldByName("id")->AsInteger;
//    int blockID = atdbDM->blocksCDSid->Value;
    int noteID  = atdbDM->blockNotesCDS->FieldByName("id")->AsInteger;

    stringstream q;
    TSQLQuery* tq = new TSQLQuery(NULL);
    tq->SQLConnection = atdbDM->SQLConnection1;

    q <<"DELETE FROM note WHERE id = "<<noteID;
    Log(lInfo) << q.str();

    tq->SQL->Add(q.str().c_str());
    tq->ExecSQL(true);
    delete tq;

    atdbDM->blockNotesCDS->Refresh();

}


void __fastcall TMainForm::RibbonsNavigatorClick(TObject *Sender, TNavigateBtn Button)
{
	switch(Button)
    {
    	case TNavigateBtn::nbDelete:
        break;

    	case TNavigateBtn::nbInsert:
	        atdbDM->mRibbonCDS->FieldByName("id")->Value = getUUID().c_str();
	        atdbDM->mRibbonCDS->FieldByName("block_id")->Value = atdbDM->blocksCDS->FieldByName("id")->Value;
			mRibbonsNavigator->BtnClick( (TNavigateBtn) Data::Bind::Controls::nbPost);
        break;
        case TNavigateBtn::nbPost:
	        mRibbonsNavigator->BtnClick( (TNavigateBtn) Data::Bind::Controls::nbRefresh);
	        mRibbonsNavigator->BtnClick( (TNavigateBtn) Data::Bind::Controls::nbRefresh);
	        mRibbonsNavigator->BtnClick( (TNavigateBtn) Data::Bind::Controls::nbLast);
	        mRibbonsNavigator->BtnClick( (TNavigateBtn) Data::Bind::Controls::nbRefresh);
        break;
        case TNavigateBtn::nbRefresh:
        	Log(lInfo) << "Refreshed Ribbons Dataset";
 		break;
    }

	mRibbonsGrid->Width = mRibbonsGrid->Width + 1;
	mRibbonsGrid->Width = mRibbonsGrid->Width - 1;

}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mBlocksNavigatorBeforeAction(TObject *Sender, TNavigateBtn Button)
{
	switch(Button)
    {
    	case TNavigateBtn::nbDelete:
             if(MessageDlg("Deleting this block will also delete all associated ribbons!\nContinue?", mtWarning, TMsgDlgButtons() << mbOK<<mbCancel, 0) == mrCancel)
             {
				Abort();
             }
        break;
    }
}

void __fastcall TMainForm::PrintBarCodeClick(TObject *Sender)
{
	MessageDlg("Not Implemented", mtInformation, TMsgDlgButtons() << mbOK, 0);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::RegisterNewBlock(TObject *Sender)
{
	if(mUsersCB->ItemIndex == -1)
    {
        return;
    }

    int* userID = (int*) mUsersCB->Items->Objects[mUsersCB->ItemIndex];
	atdbDM->blocksCDS->Append();
    atdbDM->blocksCDS->FieldValues["created_by"] = userID;
	atdbDM->blocksCDS->Post();
}

void __fastcall TMainForm::mUsersCBChange(TObject *Sender)
{
	mNewBlockBtn->Enabled = (mUsersCB->ItemIndex != -1) ?  true : false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mUsersCBEnter(TObject *Sender)
{
    mUsersQ->Close();
    mUsersQ->Open();
    while(mUsersQ->Eof != true)
    {
	    int* id = new int;
		*id = mUsersQ->Fields->Fields[0]->AsInteger;
        mUsersCB->Items->AddObject(mUsersQ->Fields->Fields[1]->AsString, (TObject*) id);
        mUsersQ->Next();
    }
}


void __fastcall	TMainForm::afterServerConnect(System::TObject* Sender)
{
	atdbDM->afterConnect();
//    enableDisableGroupBox(mATDBServerGB, true);
    mATDBServerBtnConnect->Caption = "Disconnect";
}

void __fastcall	TMainForm::afterServerDisconnect(System::TObject* Sender)
{
	atdbDM->afterDisConnect();
//    enableDisableGroupBox(mATDBServerGB, false);
    mATDBServerBtnConnect->Caption = "Connect";
}

void TMainForm::populateUsers()
{
    try
    {
//    	populateUsersCB(mUsersCB, mClientDBSession);
    }
    catch(...)
    {
//    	handleMySQLException();
    }
}


void __fastcall TMainForm::mATDBServerBtnConnectClick(TObject *Sender)
{
	if(atdbDM->SQLConnection1->Connected)
    {
	    atdbDM->SQLConnection1->Connected = false;
	    atdbDM->SQLConnection1->Close();
    }
    else
    {
	    atdbDM->connect("atdb");
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mBlocksGridDblClick(TObject *Sender)
{
	//Edit Block Record
    MessageDlg("Edit Block Record", mtWarning, TMsgDlgButtons() << mbOK, 0);
	int bID = mBlocksGrid->DataSource->DataSet->FieldByName("id")->AsInteger;
}

void __fastcall TMainForm::mNewNoteBtnClick(TObject *Sender)
{
    int uID = atdbDM->usersCDS->FieldByName("id")->AsInteger;
    int blockID = atdbDM->blocksCDSid->Value;
    string note("<none>");

    try
    {
		mServerDBSession.addNoteForBlock(blockID, uID, note);
    }
    catch(...)
    {
    	handleMySQLException();
    }

	atdbDM->blockNotesCDS->Refresh();

//    TSQLQuery* tq = new TSQLQuery(NULL);
//    tq->SQLConnection = atdbDM->SQLConnection1;
//
//    stringstream q;
//    q <<"INSERT INTO note (created_by, note) VALUES ("<<uID<<", \'<none>\');";
//    q << "SELECT LAST_INSERT_ID() AS lastNoteID;";
//    Log(lInfo) << q.str();
//    tq->SQL->Add(q.str().c_str());
//    tq->Open();
//    int noteID = tq->FieldByName("noteID")->AsInteger;
//    tq->Close();


//    //Associate
//    q.str("");
//    q << "INSERT INTO block_note (block_id, note_id) VALUES("<<blockID<<","<<noteID<<")";
//    Log(lInfo) << q.str();
//    tq->SQL->Clear();
//    tq->SQL->Add(q.str().c_str());
//    tq->ExecSQL(true);

//    delete tq;

}

void __fastcall TMainForm::DBMemo2KeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == vkReturn)
    {
    	Key = NULL;
        mBlocksNavigator->BtnClick((TNavigateBtn) Vcl::Dbctrls::nbPost);
        DBMemo2->Lines->Delete(1);
    }

}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mUpdateNoteBtnClick(TObject *Sender)
{
	atdbDM->blockNotesCDS->Post();


}


