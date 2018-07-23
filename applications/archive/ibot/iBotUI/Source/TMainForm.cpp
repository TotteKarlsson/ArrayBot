#include <vcl.h>
#pragma hdrstop
#include "dslTMemoLogger.h"
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "Poco/Glob.h"
#include "dslMoleculixException.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "dslStringUtils.h"
#include "dslSQLiteQuery.h"
#include "dslLogger.h"
#include "dslSQLiteTable.h"
#include "dslSQLiteException.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Timezone.h"
#include "iBotDataModule.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslIniFileC"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "TSlotFrame"
#pragma resource "*.dfm"

TMainForm *MainForm;
using namespace dsl;
using namespace Poco;

extern string gLogFileName;
extern string gApplicationRegistryRoot;
extern string gDefaultAppTheme;
extern bool gIsDevelopmentRelease;
//extern TSplashForm*  gSplashForm;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    :
    TRegistryForm(gApplicationRegistryRoot, "MainForm", Owner),
    mBottomPanelHeight(205),
    mMainTabIndex(0),
    mSplashProperties(gApplicationRegistryRoot, "Splash"),
    mShowSplashOnStartup(true),
    mLogLevel(lAny),
    mIsStyleMenuPopulated(false),
    gCanClose(true),
    logMsgMethod(&logMsg),
    mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "iBot", gLogFileName), logMsgMethod)
{
    mTempFileFolder = joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "iBot");
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
void __fastcall TMainForm::LogLevelCBChange(TObject *Sender)
{
    if(LogLevelCB->ItemIndex == 0)
    {
        mLogLevel = lInfo;
    }
    else if(LogLevelCB->ItemIndex == 1)
    {
        mLogLevel = lAny;
    }

    gLogger.setLogLevel(mLogLevel);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::AppInBox(mlxStructMessage &msg)
{
    if(msg.lparam == NULL)
    {
        return;
    }

    try
    {
        ApplicationMessageEnum aMsg = msg.lparam->mMessageEnum;

        switch(aMsg)
        {
            case amSplashWasClosed:
                Log(lDebug2) << "Splash form sent message that it was closed";
//                gSplashForm = NULL;
            break;

            default:
            break ;
        }
	}
	catch(...)
	{
		Log(lError) << "Received an unhandled windows message!";
	}
}

void __fastcall TMainForm::MainPCChange(TObject *Sender)
{
    //Check what tb is open
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DBLookupComboBox5CloseUp(TObject *Sender)
{
	//Fill out the slots drop downs
	String blockId = mBlocksCB->Text;
    if(blockId.Length())
    {
    	//Query db for ribbons
        TSQLQuery* q = new TSQLQuery(NULL);
        q->SQLConnection = atdbDM->SQLConnection1;
    	stringstream qs;
    	qs << "SELECT * from ribbon where block_id = "<<stdstr(atdbDM->blocksCDS->FieldByName("id")->AsString);
        string qstr = qs.str();
        q->SQL->Add(qstr.c_str());
        q->Open();

        clearSlots();
        //Get records and populate slots
        for(int i = 0; i < q->RecordCount; i++)
        {
			string ribbonID = stdstr(q->FieldByName("id")->AsString);
        	Log(lInfo) << ribbonID;
			addItemToSlots(ribbonID, NULL);
            q->Next();
        }
        q->Close();
    }
}

//---------------------------------------------------------------------------
void TMainForm::clearSlots()
{
	SlotFrame1->mRibbonCB->Clear();
	SlotFrame2->mRibbonCB->Clear();
	SlotFrame3->mRibbonCB->Clear();
	SlotFrame4->mRibbonCB->Clear();
}

void TMainForm::addItemToSlots(const string& id, TObject* o)
{
	SlotFrame1->mRibbonCB->Items->AddObject(vclstr(id), o);
	SlotFrame2->mRibbonCB->Items->AddObject(vclstr(id), o);
	SlotFrame3->mRibbonCB->Items->AddObject(vclstr(id), o);
	SlotFrame4->mRibbonCB->Items->AddObject(vclstr(id), o);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
	BottomPanel->Visible = false;
}


void __fastcall TMainForm::NotImplementedYetAExecute(TObject *Sender)
{
	MessageDlg("This functionlaity is not yet implemented", mtInformation, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

