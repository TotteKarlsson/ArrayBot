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
    logMsgMethod(&logMsg),
    mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "atDB", gLogFileName), logMsgMethod)

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


