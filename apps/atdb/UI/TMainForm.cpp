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
void __fastcall TMainForm::mUsersNavigatorClick(TObject *Sender, TNavigateBtn Button)
{
	switch(Button)
    {
    	case TNavigateBtn::nbInsert:
        	atdbDM->usersCDS->FieldValues["user_name"] = "New User";
        break;
        case TNavigateBtn::nbApplyUpdates:      									  break;
        case TNavigateBtn::nbRefresh: 												  break;
    }
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
//	switch(Button)
//    {
//    	case TNavigateBtn::nbDelete:
////             if(MessageDlg("Deleting this ribbon will delete all associated notes!\nContinue?", mtWarning, TMsgDlgButtons() << mbOK<<mbCancel, 0) == mrCancel)
////             {
////				Abort();
////             }
//
////			String ribbonID = atdbDM->mRibbonCDS->FieldByName("id")->Value;
////            mServerDBSession.deleteNotesForRibbon(stdstr(ribbonID));
////            atdbDM->ribbonNotesCDS->Refresh();
//        break;
//    }
}

void __fastcall TMainForm::mBlocksNavigatorClick(TObject *Sender, TNavigateBtn Button)
{
	switch(Button)
    {
    	case TNavigateBtn::nbDelete:        break;

    	case TNavigateBtn::nbInsert:
        	if(!mUsersDBCB->KeyValue.IsNull())
            {
	        	atdbDM->blocksCDS->FieldValues["created_by"] = mUsersDBCB->KeyValue;
                atdbDM->blocksCDS->Post();
			    atdbDM->blocksCDS->First();
            }
            else
            {
            	MessageDlg("Select a user before inserting blocks..", mtInformation, TMsgDlgButtons() << mbOK, 0);
            	Log(lError) << "Bad...";
            }
        break;
        case TNavigateBtn::nbPost:        		break;
        case TNavigateBtn::nbRefresh:        	Log(lInfo) << "Refreshed Blocks Dataset"; 		break;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::RibbonsNavigatorClick(TObject *Sender, TNavigateBtn Button)
{
	switch(Button)
    {
    	case TNavigateBtn::nbDelete:        break;

    	case TNavigateBtn::nbInsert:
        {
	        atdbDM->mRibbonCDS->FieldByName("id")->Value 		= getUUID().c_str();
	        atdbDM->mRibbonCDS->FieldByName("block_id")->Value 	= atdbDM->blocksCDS->FieldByName("id")->Value;
            atdbDM->mRibbonCDS->Post();
			atdbDM->mRibbonCDS->First();
        }
        break;
        case TNavigateBtn::nbPost:
        break;
        case TNavigateBtn::nbRefresh:
        	Log(lInfo) << "Refreshed Ribbons Dataset";
 		break;
    }
}

void __fastcall TMainForm::PrintBarCodeClick(TObject *Sender)
{
	MessageDlg("Not Implemented", mtInformation, TMsgDlgButtons() << mbOK, 0);
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

//---------------------------------------------------------------------------
void __fastcall TMainForm::DBNavigator5Click(TObject *Sender, TNavigateBtn Button)
{
	switch(Button)
    {
    	case TNavigateBtn::nbInsert:
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
        break;

    	case TNavigateBtn::nbDelete:        break;
    }
}

void __fastcall TMainForm::DBNavigator6Click(TObject *Sender, TNavigateBtn Button)
{
	switch(Button)
    {
    	case TNavigateBtn::nbInsert:
			{
            int uID = atdbDM->usersCDS->FieldByName("id")->AsInteger;
            String rID = atdbDM->mRibbonCDSid->Value;
            string note("Ribbon Note..");

            try
            {
                mServerDBSession.addNoteForRibbon(stdstr(rID), uID, note);
            }
            catch(...)
            {
                handleMySQLException();
            }

            atdbDM->ribbonNotesCDS->Refresh();
            atdbDM->ribbonNotesCDS->Last();
            }
        break;

    	case TNavigateBtn::nbDelete:        break;
    }
}
