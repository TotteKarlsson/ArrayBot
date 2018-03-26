#include <vcl.h>
#pragma hdrstop
#include <sstream>
#include "TAboutArrayBot_2Frame.h"
#include "dslStringList.h"
#include "dslVCLUtils.h"
#include "dslApplicationInfo.h"
#include "../abApplicationMessages.h"
#include "dslLogger.h"

#include "Poco/DateTimeFormatter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslURLLabel"
#pragma resource "*.dfm"
TAboutArrayBotFrame_2 *AboutArrayBotFrame_2;

using namespace std;
using namespace dsl;
//---------------------------------------------------------------------------
__fastcall TAboutArrayBotFrame_2::TAboutArrayBotFrame_2(TComponent* Owner)
:
TFrame(Owner)
{}

//---------------------------------------------------------------------------
void TAboutArrayBotFrame_2::populate()
{
    stringstream ss;
    dslApplicationInfo appInfo(Application);

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


