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
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzDBSpin"
#pragma link "RzSpnEdt"
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
	mServerDBSession("atdb"),
    mDBUserID(0)
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

//---------------------------------------------------------------------------
void __fastcall TMainForm::mBlocksNavigatorBeforeAction(TObject *Sender, TNavigateBtn Button)
{
	switch(Button)
    {
    	case TNavigateBtn::nbDelete:
             if(MessageDlg("Deleting this block will delete all associated ribbons and notes!\nContinue?", mtWarning, TMsgDlgButtons() << mbOK<<mbCancel, 0) == mrCancel)
             {
				Abort();
             }

			int blockID = atdbDM->blocksCDS->FieldByName("id")->Value;
            mServerDBSession.deleteNotesForBlock(blockID);
            mServerDBSession.deleteRibbonsForBlock(blockID);
        break;
    }
}

void __fastcall TMainForm::mRibbonsNavigatorBeforeAction(TObject *Sender, TNavigateBtn Button)
{
	switch(Button)
    {
    	case TNavigateBtn::nbDelete:
             if(MessageDlg("Deleting this ribbon will delete all associated notes!\nContinue?", mtWarning, TMsgDlgButtons() << mbOK<<mbCancel, 0) == mrCancel)
             {
				Abort();
             }

			String ribbonID = atdbDM->mRibbonCDS->FieldByName("id")->Value;
            mServerDBSession.deleteNotesForRibbon(stdstr(ribbonID));
            atdbDM->ribbonNotesCDS->Refresh();
        break;
    }
}

void __fastcall TMainForm::mBlocksNavigatorClick(TObject *Sender, TNavigateBtn Button)
{
	switch(Button)
    {
    	case TNavigateBtn::nbDelete:
        {

        }
        break;

    	case TNavigateBtn::nbInsert:
        	if(!mUsersDBCB->KeyValue.IsNull())
            {
                atdbDM->blocksCDS->Append();
	        	atdbDM->blocksCDS->FieldValues["created_by"] = mUsersDBCB->KeyValue;
				mBlocksNavigator->BtnClick( Data::Bind::Controls::nbPost);
			    atdbDM->blocksCDS->Last();
            }
            else
            {
            	MessageDlg("Select a user before inserting blocks..", mtInformation, TMsgDlgButtons() << mbOK, 0);
            	Log(lError) << "Bad...";
            }
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
void __fastcall TMainForm::mDeleteNoteBtnClick(TObject *Sender)
{
	TButton* b = dynamic_cast<TButton*>(Sender);

    TClientDataSet *ds = NULL;
    if(b == mDeleteBlockNoteBtn)
	{
        ds = atdbDM->blockNotesCDS;
    }
    else if(b == mDeleteRibbonNoteBtn)
    {
        ds = atdbDM->ribbonNotesCDS;
    }
    int noteID =  ds->FieldByName("id")->AsInteger;;

    stringstream q;
    TSQLQuery* tq = new TSQLQuery(NULL);
    tq->SQLConnection = atdbDM->SQLConnection1;

    q <<"DELETE FROM note WHERE id = "<<noteID;
    Log(lDebug) << q.str();
    tq->SQL->Add(q.str().c_str());
    tq->ExecSQL(true);
    delete tq;

    ds->Refresh();
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
			atdbDM->mRibbonCDS->Refresh();
        	Log(lInfo) << "Refreshed Ribbons Dataset";
 		break;
    }

	mRibbonsGrid->Width = mRibbonsGrid->Width + 1;
	mRibbonsGrid->Width = mRibbonsGrid->Width - 1;

}


void __fastcall TMainForm::PrintBarCodeClick(TObject *Sender)
{
	MessageDlg("Not Implemented", mtInformation, TMsgDlgButtons() << mbOK, 0);
}


void __fastcall TMainForm::mUsersCBEnter(TObject *Sender)
{
//    mUsersQ->Close();
////    mUsersCB->Clear();
//    mUsersQ->Open();
//    while(mUsersQ->Eof != true)
//    {
//	    int* id = new int;
//		*id = mUsersQ->Fields->Fields[0]->AsInteger;
////        mUsersCB->Items->AddObject(mUsersQ->Fields->Fields[1]->AsString, (TObject*) id);
//        mUsersQ->Next();
//    }
}


void __fastcall	TMainForm::afterServerConnect(System::TObject* Sender)
{
	atdbDM->afterConnect();
	mUsersDBCB->Enabled = true;
    mUsersDBCB->KeyValue = mDBUserID.getValue();
    mATDBServerBtnConnect->Caption = "Disconnect";
    mUsersDBCB->OnCloseUp(NULL);

}

void __fastcall	TMainForm::afterServerDisconnect(System::TObject* Sender)
{
	mUsersDBCB->Enabled = false;
	atdbDM->afterDisConnect();

    mATDBServerBtnConnect->Caption = "Connect";
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
	//connect(const string& ip, const string& dbUser, const string& dbPassword, const string& db)
	    atdbDM->connect(mServerIPE->getValue(), mDBUserE->getValue(), mPasswordE->getValue(), mDatabaseE->getValue());
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
	TButton* b = dynamic_cast<TButton*>(Sender);
    if(b == mNewBlockNoteBtn)
    {
        int uID = atdbDM->usersCDS->FieldByName("id")->AsInteger;
        int blockID = atdbDM->blocksCDSid->Value;
        string note("Block Note..");

        try
        {
            mServerDBSession.addNoteForBlock(blockID, uID, note);
        }
        catch(...)
        {
            handleMySQLException();
        }

        atdbDM->blockNotesCDS->Refresh();
        atdbDM->blockNotesCDS->Last();
    }
    else if(b == mNewRibbonNote)
    {
        int uID = atdbDM->usersCDS->FieldByName("id")->AsInteger;
        String ribbonID = atdbDM->mRibbonCDSid->AsString;
        string note("Ribbon Note..");

        try
        {
            mServerDBSession.addNoteForRibbon(stdstr(ribbonID), uID, note);
        }
        catch(...)
        {
            handleMySQLException();
        }

        atdbDM->ribbonNotesCDS->Refresh();
        atdbDM->ribbonNotesCDS->Last();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mUpdateNoteBtnClick(TObject *Sender)
{
	atdbDM->blockNotesCDS->Post();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mUsersDBCBCloseUp(TObject *Sender)
{
	if(mUsersDBCB->KeyValue.IsNull())
    {
    	enableDisableGroupBox(mBlocksGB, false);
    }
    else
    {
    	enableDisableGroupBox(mBlocksGB, true);
		mDBUserID = mUsersDBCB->KeyValue;
    }
}
