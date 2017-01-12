#include <vcl.h>
#pragma hdrstop
#include "atdbVCLUtils.h"
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
#include "TamFileEditor.h"
#include "TATDBDataModule.h"
#include "TCoverSlipDataModule.h"
#include "TImagesDataModule.h"
#include "TMainForm.h"
#include "TMemoLogger.h"
#include "TNewSpecimenForm.h"
#include "TNewBlockForm.h"
#include "TShowFileContentForm.h"
#include "TTableUpdateForm.h"
#include "TRegisterFreshCSBatchForm.h"
#include "TPrintLabelForm.h"
#include "atQueryBuilder.h"
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
#pragma link "TTableFrame"
#pragma link "pBarcode2D"
#pragma link "pCore2D"
#pragma link "pDataMatrix"
#pragma link "pDBBarcode2D"
#pragma link "pQRCode"
#pragma link "TIntLabel"
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



