#include <vcl.h>
#pragma hdrstop
#include "TAboutAmalyticoForm.h"
#include "TShowFileContentForm.h"
#include "mtkApplicationInfo.h"
#include "mtkVCLUtils.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TAboutAmalyticoFrame"
#pragma resource "*.dfm"
TAboutAmalyticoForm *AboutAmalyticoForm;

using namespace mtk;
//---------------------------------------------------------------------------
__fastcall TAboutAmalyticoForm::TAboutAmalyticoForm(mtk::ApplicationLicenseController& lc, TRegistrationFile* reg, TComponent* Owner)
    : TForm(Owner),
    mLC(lc),
    mRegistrationComponent(reg),
    mRemoteDownloadURL("http://www.moleculix.com/downloads/Amalytico"),
    mRemoteVersion("")
{
}
//---------------------------------------------------------------------------
void __fastcall TAboutAmalyticoForm::FormShow(TObject *Sender)
{
    if(!mAboutFrame)
    {
        mAboutFrame = new TAboutAmalyticoFrame(mLC, mRegistrationComponent, this);
        mAboutFrame->Visible = false;
        mAboutFrame->populate();
        mAboutFrame->Parent =  this;
        mAboutFrame->AutoSize = true;
        mAboutFrame->Align = alClient;
        mAboutFrame->Visible = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TAboutAmalyticoForm::Button4Click(TObject *Sender)
{
    CloseModal();
}


//void __fastcall TAboutAmalyticoForm::Button2Click(TObject *Sender)
//{
//    TShowFileContentForm* e = new TShowFileContentForm(Application);
//    e->Memo1->Lines->LoadFromFile("LICENSE.txt");
//    e->ShowModal();
//    delete e;
//}
//---------------------------------------------------------------------------

void __fastcall TAboutAmalyticoForm::Button3Click(TObject *Sender)
{
    try
    {
        TShowFileContentForm* e = new TShowFileContentForm(Application);
        e->Caption = "Amalytico ChangeLog";
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
void __fastcall TAboutAmalyticoForm::Button1Click(TObject *Sender)
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
void __fastcall TAboutAmalyticoForm::NotifyAboutUpdate(const string& data)
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
void __fastcall TAboutAmalyticoForm::NotifyAboutChangeLog(const string& data)
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
void __fastcall TAboutAmalyticoForm::checkForUpdateAExecute(TObject *Sender)
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


void __fastcall TAboutAmalyticoForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}


void __fastcall TAboutAmalyticoForm::retrieveChangeLogAExecute(TObject *Sender)
{
    mGetNewestChangeLogThread.setURL(joinPath(joinPath(mRemoteDownloadURL, mRemoteVersion.asString("major.minor.patch"),'/'), "CHANGELOG.txt", '/'));
    mGetNewestChangeLogThread.assignCallBack(NotifyAboutChangeLog);
    mGetNewestChangeLogThread.start();
}
//---------------------------------------------------------------------------


void __fastcall TAboutAmalyticoForm::FormClose(TObject *Sender, TCloseAction &Action)

{
//    Action = caFree;
}

//---------------------------------------------------------------------------
void __fastcall TAboutAmalyticoForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    //Check threads...
}


