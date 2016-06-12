#include <vcl.h>
#pragma hdrstop
#include "TAboutArrayBotForm.h"
#include "TShowFileContentForm.h"
#include "mtkApplicationInfo.h"
#include "mtkVCLUtils.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TAboutArrayBotFrame"
#pragma resource "*.dfm"
TAboutArrayBotForm *AboutArrayBotForm;

using namespace mtk;
//---------------------------------------------------------------------------
__fastcall TAboutArrayBotForm::TAboutArrayBotForm(TComponent* Owner)
    : TForm(Owner),
    mRemoteDownloadURL(""),
    mRemoteVersion("")
{
}
//---------------------------------------------------------------------------
void __fastcall TAboutArrayBotForm::FormShow(TObject *Sender)
{
    if(!mAboutFrame)
    {
        mAboutFrame = new TAboutArrayBotFrame(this);
        mAboutFrame->Visible = false;
        mAboutFrame->populate();
        mAboutFrame->Parent =  this;
        mAboutFrame->AutoSize = true;
        mAboutFrame->Align = alClient;
        mAboutFrame->Visible = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TAboutArrayBotForm::Button4Click(TObject *Sender)
{
    CloseModal();
}


//void __fastcall TAboutArrayBotForm::Button2Click(TObject *Sender)
//{
//    TShowFileContentForm* e = new TShowFileContentForm(Application);
//    e->Memo1->Lines->LoadFromFile("LICENSE.txt");
//    e->ShowModal();
//    delete e;
//}
//---------------------------------------------------------------------------

void __fastcall TAboutArrayBotForm::Button3Click(TObject *Sender)
{
    try
    {
        TShowFileContentForm* e = new TShowFileContentForm(Application);
        e->Caption = "ArrayBot ChangeLog";
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
void __fastcall TAboutArrayBotForm::Button1Click(TObject *Sender)
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

//---------------------------------------------------------------------------
//Executed in a thread
void __fastcall TAboutArrayBotForm::NotifyAboutUpdate(const string& data)
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
//                mStartCheckForChangeLogThread = true;
                retrieveChangeLogA->Execute();
            }
        }
        else if(mRemoteVersion == currentVersion)
        {
            Application->MessageBox(L"You are running the latest version!", L"Checking for new version", MB_OK);
        }
        else
        {
            Application->MessageBox(L"You are running a newer version(!) than what is available!", L"Checking for new version", MB_OK);
        }
    }
    else
    {
            Application->MessageBox(L"We were unable to retrieve remote data!", L"Checking for new version", MB_OK);
    }

    checkForUpdateA->Caption = "Check for update";
}

//Executed in a thread
void __fastcall TAboutArrayBotForm::NotifyAboutChangeLog(const string& data)
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
void __fastcall TAboutArrayBotForm::checkForUpdateAExecute(TObject *Sender)
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


void __fastcall TAboutArrayBotForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}


void __fastcall TAboutArrayBotForm::retrieveChangeLogAExecute(TObject *Sender)
{
    mGetNewestChangeLogThread.setURL(joinPath(joinPath(mRemoteDownloadURL, mRemoteVersion.asString("major.minor.patch"),'/'), "CHANGELOG.txt", '/'));
    mGetNewestChangeLogThread.assignCallBack(NotifyAboutChangeLog);
    mGetNewestChangeLogThread.start();
}
//---------------------------------------------------------------------------


void __fastcall TAboutArrayBotForm::FormClose(TObject *Sender, TCloseAction &Action)

{
//    Action = caFree;
}

//---------------------------------------------------------------------------
void __fastcall TAboutArrayBotForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    //Check threads...
}


