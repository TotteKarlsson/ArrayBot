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
#pragma link "dslTURLLabel"
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
    string f("CHANGELOG.txt");
    try
    {
        stringstream ss;
        dslApplicationInfo appInfo(Application);

        //Current Version Info
         Version version(stdstr(appInfo.mVersion));
        ss <<version.getMajor()<<"."<<version.getMinor()<<"."<<version.getPatch();
        String versionMajorMinorPatch(ss.str().c_str());
        versionLabel->Caption = String("Version: ") + versionMajorMinorPatch;
        Memo1->Lines->LoadFromFile(f.c_str());
    }
    catch(const EFOpenError& e)
    {
        Log(lError) << "EFileOpenError: " << stdstr(e.Message);
    }
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


