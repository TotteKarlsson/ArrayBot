#include <vcl.h>
#pragma hdrstop
#include <sstream>
#include "TAboutArrayBotFrame.h"
#include "mtkStringList.h"
#include "mtkVCLUtils.h"
#include "mtkApplicationInfo.h"
#include "amlApplicationMessages.h"
#include "mtkLogger.h"
#include "TShowFileContentForm.h"
#include "Poco/DateTimeFormatter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SKGenerator"
#pragma link "mtkURLLabel"
#pragma link "mtkURLLabel"
#pragma resource "*.dfm"
TAboutAmalyticoFrame *AboutAmalyticoFrame;

using namespace std;
using namespace mtk;
//---------------------------------------------------------------------------
__fastcall TAboutAmalyticoFrame::TAboutAmalyticoFrame(TComponent* Owner)
:
TFrame(Owner),
mRemoteDownloadURL(""),
mRemoteVersion("")
{}

//---------------------------------------------------------------------------
void TAboutAmalyticoFrame::populate()
{
    stringstream ss;
    mtkApplicationInfo appInfo(Application);

    //Current Version Info
    Version version(stdstr(appInfo.mVersion));
    ss <<version.getMajor()<<"."<<version.getMinor()<<"."<<version.getPatch();
    String versionMajorMinorPatch(ss.str().c_str());
    versionLabel->Caption = String("Version: ") + versionMajorMinorPatch;
}

void TAboutAmalyticoFrame::serialKeyEnteringObjectsVisible(bool setVisibility)
{
}


//---------------------------------------------------------------------------
void __fastcall TAboutAmalyticoFrame::checkForUpdateAExecute(TObject *Sender)
{
    if(startsWith(stdstr(checkForUpdateA->Caption), "Check"))
    {
        mGetRemoteVersionThread.setURL(joinPath(mRemoteDownloadURL, "VERSION.txt", '/'));
        mGetRemoteVersionThread.assignCallBack(NotifyAboutUpdate);
        mGetRemoteVersionThread.start();

        checkForUpdateA->Caption = "Cancel";
    }
    else
    {
        checkForUpdateA->Caption = "Check for update";
    }
}

void __fastcall TAboutAmalyticoFrame::retrieveChangeLogAExecute(TObject *Sender)
{
    mGetNewestChangeLogThread.setURL(joinPath(joinPath(mRemoteDownloadURL, mRemoteVersion.asString("major.minor.patch"),'/'), "CHANGELOG.txt", '/'));
    mGetNewestChangeLogThread.assignCallBack(NotifyAboutChangeLog);
    mGetNewestChangeLogThread.start();
}

//---------------------------------------------------------------------------
//Executed in a thread
void __fastcall TAboutAmalyticoFrame::NotifyAboutUpdate(const string& data)
{
    if(data.size())
    {
        //Start a check for update thread
        mRemoteVersion = Version(data);
        Version currentVersion(stdstr(getProductVersion(Application)));

        Log(lInfo) <<"Current version is: "<<currentVersion;
        Log(lInfo) <<"Remote version: "<<mRemoteVersion;

        if(mRemoteVersion > currentVersion)
        {
            stringstream msg;
            msg<<"A new version is available!\n";
            msg<<"Your version is: "<<currentVersion<<"\n";
            msg<<"Remote version is: "<<mRemoteVersion<<"\n\n";
            msg<<"Get information about the latest version?"<<"\n\n";
            wstring msgS(wstdstr(msg.str()));

            int mResult = Application->MessageBox(msgS.c_str(), L"Checked for remote version", MB_OKCANCEL|MB_ICONQUESTION);
            if(mResult == 1)
            {
                //Start thread to retrieve the changelog
                mStartCheckForChangeLogThread = true;
            }


        }
        else if(mRemoteVersion == currentVersion)
        {
            Application->MessageBox(L"You are running the latest version!", L"Checking for new version", MB_OK);
        }
    }
    else
    {
            Application->MessageBox(L"We were unable to retrieve remote data!", L"Checking for new version", MB_OK);
    }

    checkForUpdateA->Caption = "Check for update";
}

//Executed in a thread
void __fastcall TAboutAmalyticoFrame::NotifyAboutChangeLog(const string& data)
{
    if(data.size())
    {
        StringList lines(data);

        if(lines.count() > 30)
        {
            lines.truncate(30);
            lines.append(".. remote data was truncated to fit the screen.");
        }

        wstring msgS(wstdstr(lines.asString('\n')));
        int mResult = Application->MessageBox(msgS.c_str(), L"Remote Change Log", MB_OK);
    }
    else
    {
        Application->MessageBox(L"We were unable to retrieve remote data!", L"Checked for changelog", MB_OK);
    }

    checkForUpdateA->Caption = "Check for update";
}

//---------------------------------------------------------------------------
void __fastcall TAboutAmalyticoFrame::ThreadCheckTimerTimer(TObject *Sender)
{
    if(mStartCheckForChangeLogThread)
    {
        mStartCheckForChangeLogThread = false;
        retrieveChangeLogA->Execute();
    }
}

//---------------------------------------------------------------------------
void __fastcall TAboutAmalyticoFrame::showChangeLogExecute(TObject *Sender)
{
    try
    {
        TShowFileContentForm* e = new TShowFileContentForm(Application);
        e->Memo1->Lines->LoadFromFile("CHANGELOG.txt");
        e->ShowModal();
        delete e;
    }
    catch(...)
    {
        MessageDlg("There was a problem opening the file!", mtInformation, TMsgDlgButtons() << mbOK, 0);
    }
}

//---------------------------------------------------------------------------
void __fastcall TAboutAmalyticoFrame::CloseAExecute(TObject *Sender)
{
//    //Tell the application to go to the home tab
//  	HWND hWnd = Application->MainForm->Handle;
//    LRESULT res = SendMessage(hWnd, UWM_GOTO_HOME_PAGE, 0, 0);
//    if(res)
//    {
//        Log(lDebug)<<"Sending tab changed message was unsuccesful";
//    }

}


