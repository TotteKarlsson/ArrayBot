#include <vcl.h>
#pragma hdrstop
#include <sstream>
#include "TAboutArduinoServerFrame.h"
#include "mtkStringList.h"
#include "mtkVCLUtils.h"
#include "mtkApplicationInfo.h"
#include "abApplicationMessages.h"
#include "mtkLogger.h"
#include "Poco/DateTimeFormatter.h"
#include "mtkVersion.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutArduinoServerFrame *AboutArduinoServerFrame;

using namespace std;
using namespace mtk;
//---------------------------------------------------------------------------
__fastcall TAboutArduinoServerFrame::TAboutArduinoServerFrame(TComponent* Owner)
:
TFrame(Owner)
{}

//---------------------------------------------------------------------------
void TAboutArduinoServerFrame::populate()
{
    stringstream ss;
    mtkApplicationInfo appInfo(Application);

    //Current Version Info
    Version version(stdstr(appInfo.mVersion));
    ss <<version.getMajor()<<"."<<version.getMinor()<<"."<<version.getPatch();
    String versionMajorMinorPatch(ss.str().c_str());
    versionLabel->Caption = String("Version: ") + versionMajorMinorPatch;
}

//---------------------------------------------------------------------------
void __fastcall TAboutArduinoServerFrame::CloseAExecute(TObject *Sender)
{
//    //Tell the application to go to the home tab
//  	HWND hWnd = Application->MainForm->Handle;
//    LRESULT res = SendMessage(hWnd, UWM_GOTO_HOME_PAGE, 0, 0);
//    if(res)
//    {
//        Log(lDebug)<<"Sending tab changed message was unsuccesful";
//    }

}




