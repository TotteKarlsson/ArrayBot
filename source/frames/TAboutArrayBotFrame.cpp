#include <vcl.h>
#pragma hdrstop
#include <sstream>
#include "TAboutArrayBotFrame.h"
#include "dslStringList.h"
#include "dslVCLUtils.h"
#include "dslApplicationInfo.h"
#include "../abApplicationMessages.h"
#include "dslLogger.h"
//#include "../source/vcl/forms/TShowFileContentForm.h"
#include "Poco/DateTimeFormatter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutArrayBotFrame *AboutArrayBotFrame;

using namespace std;
using namespace dsl;
//---------------------------------------------------------------------------
__fastcall TAboutArrayBotFrame::TAboutArrayBotFrame(TComponent* Owner)
:
TFrame(Owner)
{}

//---------------------------------------------------------------------------
void TAboutArrayBotFrame::populate()
{
    stringstream ss;
    dslApplicationInfo appInfo(Application);

    //Current Version Info
    Version version(stdstr(appInfo.mVersion));
    ss <<version.getMajor()<<"."<<version.getMinor()<<"."<<version.getPatch();
    String versionMajorMinorPatch(ss.str().c_str());
    versionLabel->Caption = String("Version: ") + versionMajorMinorPatch;
}

//---------------------------------------------------------------------------
void __fastcall TAboutArrayBotFrame::CloseAExecute(TObject *Sender)
{
//    //Tell the application to go to the home tab
//  	HWND hWnd = Application->MainForm->Handle;
//    LRESULT res = SendMessage(hWnd, UWM_GOTO_HOME_PAGE, 0, 0);
//    if(res)
//    {
//        Log(lDebug)<<"Sending tab changed message was unsuccesful";
//    }

}


