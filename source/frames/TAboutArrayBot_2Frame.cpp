#include <vcl.h>
#pragma hdrstop
#include <sstream>
#include "TAboutArrayBot_2Frame.h"
#include "mtkStringList.h"
#include "mtkVCLUtils.h"
#include "mtkApplicationInfo.h"
#include "../abApplicationMessages.h"
#include "mtkLogger.h"

#include "Poco/DateTimeFormatter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "mtkURLLabel"
#pragma resource "*.dfm"
TAboutArrayBotFrame_2 *AboutArrayBotFrame_2;

using namespace std;
using namespace mtk;
//---------------------------------------------------------------------------
__fastcall TAboutArrayBotFrame_2::TAboutArrayBotFrame_2(TComponent* Owner)
:
TFrame(Owner)
{}

//---------------------------------------------------------------------------
void TAboutArrayBotFrame_2::populate()
{
    stringstream ss;
    mtkApplicationInfo appInfo(Application);

    //Current Version Info
    Version version(stdstr(appInfo.mVersion));
    ss <<version.getMajor()<<"."<<version.getMinor()<<"."<<version.getPatch();
    String versionMajorMinorPatch(ss.str().c_str());
    versionLabel->Caption = String("Version: ") + versionMajorMinorPatch;
    Memo1->Lines->LoadFromFile("CHANGELOG.txt");
}

//---------------------------------------------------------------------------
void __fastcall TAboutArrayBotFrame_2::CloseAExecute(TObject *Sender)
{
//    //Tell the application to go to the home tab
//  	HWND hWnd = Application->MainForm->Handle;
//    LRESULT res = SendMessage(hWnd, UWM_GOTO_HOME_PAGE, 0, 0);
//    if(res)
//    {
//        Log(lDebug)<<"Sending tab changed message was unsuccesful";
//    }

}


