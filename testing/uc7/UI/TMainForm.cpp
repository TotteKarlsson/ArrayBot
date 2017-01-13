#include <vcl.h>
#pragma hdrstop
#include "atVCLUtils.h"
#include "database/atDBUtils.h"
#include "mtkLogger.h"
#include "mtkMoleculixException.h"
#include "mtkSQLiteException.h"
#include "mtkSQLiteQuery.h"
#include "mtkSQLiteTable.h"
#include "mtkStringUtils.h"
#include "mtkUtils.h"
#include "mtkVCLUtils.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Glob.h"
#include "Poco/Timezone.h"
#include "TMainForm.h"
#include "TMemoLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "mtkIniFileC"
#pragma link "mtkIniFileC"
#pragma resource "*.dfm"

TMainForm *MainForm;
using namespace mtk;
using namespace ab;

extern string gLogFileName;
extern string gApplicationRegistryRoot;
extern string gDefaultAppTheme;
extern string gFullDateTimeFormat;
extern bool gIsDevelopmentRelease;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TRegistryForm(gApplicationRegistryRoot, "MainForm", Owner),

    mBottomPanelHeight(205),
    mSplashProperties(gApplicationRegistryRoot, "Splash"),
    mShowSplashOnStartup(true),
    mLogLevel(lAny),
    mIsStyleMenuPopulated(false),
    gCanClose(true),
    mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "atUC7", gLogFileName), &logMsg),
    mCOMPort(0)
{
    //Close any dataconnection created by stupid TSQLConnection
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

void __fastcall TMainForm::mConnectUC7BtnClick(TObject *Sender)
{
	if(mConnectUC7Btn->Caption == "Open")
    {
        if(mUC7.connect(getCOMPortNumber()))
        {
            Log(lInfo) << "Connected to a UC7 device";
        }
        else
        {
            Log(lInfo) << "Connection failed";
        }
    }
    else
    {
        if(!mUC7.disConnect())
        {
			Log(lError) << "Failed to close serial port";
        }
    }

    if(mUC7.isConnected())
    {
	    onConnectedToUC7();
        mConnectUC7Btn->Caption = "Close";
    }
    else
    {
		onDisConnectedToUC7();
    	mConnectUC7Btn->Caption = "Open";
    }
}

//---------------------------------------------------------------------------
int	TMainForm::getCOMPortNumber()
{
	return mComportCB->ItemIndex + 1;
}

void __fastcall TMainForm::mSendBtn1Click(TObject *Sender)
{
	mUC7.sendRawMessage(mSendRAW1->getValue());
}

void __fastcall TMainForm::onConnectedToUC7()
{
	mSendRAW1->Enabled = true;
	mSendBtn1->Enabled = true;
}

void __fastcall TMainForm::onDisConnectedToUC7()
{
	mSendRAW1->Enabled = false;
	mSendBtn1->Enabled = false;
}
