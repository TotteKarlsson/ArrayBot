#include <vcl.h>
#pragma hdrstop
#include <sstream>
#include "TAboutAmalyticoFrame.h"
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
__fastcall TAboutAmalyticoFrame::TAboutAmalyticoFrame(mtk::ApplicationLicenseController& lc, TRegistrationFile* reg, TComponent* Owner)
:
TFrame(Owner),
mIsUnlocking(false),
mLC(lc),
RegistrationFile1(reg),
mRemoteDownloadURL("http://www.moleculix.com/downloads/Amalytico"),
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



    RegistrationFile1->FileName = "amalytico-0.5.regi";
    // file checksum (SHA256)
    RegistrationFile1->FileChecksum = "134691e5754087835d24a30a1dce562703de19924f8a16bf827d91aab865d5c8";
    // ID String
    RegistrationFile1->IDString = "PreRelease";

    //Check if application been validated. If not, setup in trial mode
    RegistrationFile1->SerialKey = vclstr(mLC.retrieveActivationKey());

	int result = RegistrationFile1->ValidateSerialKey();
    bool isActivated = (result == 0) ? true : false;
    mLC.isActivated(isActivated);
    mLC.isActivated() == true ? mLC.setLicenseMode(lmActivated) : mLC.setLicenseMode(lmTrial);


    if(mLC.getLicenseMode() == lmTrial)
    {
        ss.str("");
        //Setup license info
        Poco::Timespan ts = mLC.getTrialPeriodLeft();
        if(ts < 0)
        {
            ts = 0;
        }
        ss<<"License: Time limited trial mode license ("<<Poco::DateTimeFormatter::format(ts, "%d")
        <<" days left out of "
        <<Poco::DateTimeFormatter::format(mLC.getTrialPeriod(), "%d")
        <<" days total).";
        ProdLicenseLbl->Caption = vclstr(ss.str());
        ProdLicenseLbl->Visible = true;
        UnlockBtn->Visible = true;
    }
    else
    {
        //Product is activated!
        serialKeyEnteringObjectsVisible(false);
        StartUnlockProcedureA->Visible = false;

        ss.str("");
        ss<<"Licence: Activated\n";
        ss<<"This product is licensed to be used on one computer.";
        ProdLicenseLbl->Caption = vclstr(ss.str());
        ProdLicenseLbl->Visible = true;
    }

    ss.str("");
    if(mLC.hasExpirationDate())
    {

        expirationLabel->Visible = true;
        expirationLabel->Color = clRed;
        ss<<"This product is a pre-release version and will expire on "<<Poco::DateTimeFormatter::format(mLC.getExpirationDate(), "%b %e, %Y");
        expirationLabel->Caption = vclstr(ss.str());
    }
}

void TAboutAmalyticoFrame::serialKeyEnteringObjectsVisible(bool setVisibility)
{
    UnlockBtn->Visible = setVisibility;
    Edit1->Visible = setVisibility;
    Edit2->Visible = setVisibility;
    Edit3->Visible = setVisibility;
    Edit4->Visible = setVisibility;
    Edit5->Visible = setVisibility;
    SubmitKeyButton->Visible = setVisibility;
}

//---------------------------------------------------------------------------
void __fastcall TAboutAmalyticoFrame::StartUnlockProcedureAExecute(TObject *Sender)
{
    mIsUnlocking = !mIsUnlocking;
    Edit1->Visible = mIsUnlocking;
    Edit2->Visible = mIsUnlocking;
    Edit3->Visible = mIsUnlocking;
    Edit4->Visible = mIsUnlocking;
    Edit5->Visible = mIsUnlocking;
    ValidateKeyAction->Visible = mIsUnlocking;
    SubmitKeyButton->Visible = mIsUnlocking;

    UnlockBtn->Caption = (mIsUnlocking) ? "Cancel Unlocking" : "Unlock";
    if(mIsUnlocking)
    {
        Edit1->SetFocus();
    }
}

void __fastcall TAboutAmalyticoFrame::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
    //Check which edit user are filling out. If full, jump to next edit
    TEdit* theEdit = dynamic_cast<TEdit*>(Sender);
    if(!theEdit)
    {
        return;
    }

    if(theEdit->Text.Length() >= 4)
    {
        //Gotta jump
        SelectNext(theEdit, true, true);
    }
}

//---------------------------------------------------------------------------
void __fastcall TAboutAmalyticoFrame::ValidateKeyActionExecute(TObject *Sender)
{
    // Serial key to check...
    RegistrationFile1->SerialKey = Edit1->Text + Edit2->Text + Edit3->Text + Edit4->Text + Edit5->Text;
    int result = RegistrationFile1->ValidateSerialKey();

    // Serial key to check...
    if (result == 0)
    {
        //A valid key was entered..
        //Put this key into the registry for later retrieval
        mLC.storeActivationKey(stdstr(RegistrationFile1->SerialKey));
        stringstream ss;
        ss<<"LicenceType: This license allow usage on one single computer";
        ProdLicenseLbl->Caption = vclstr(ss.str());
        StartUnlockProcedureAExecute(NULL);
        StartUnlockProcedureA->Visible = false;

        mLC.isActivated(true);

        //Tell the application that it is unlocked!
       	HWND hWnd = Application->MainForm->Handle;
        LRESULT res = SendMessage(hWnd, UWM_CHECK_LICENSE, 0, 0);
    	if(res)
	    {
		    Log(lDebug)<<"Sending tab changed message was unsuccesful";
    	}
    }

    if (result == -1)
    {
        ShowMessage("Can't validate! \nAn important file for serial key validation could not be found!");
    }

    if (result == -2)
    {
        ShowMessage("Hash check failed!");
    }

    if (result == -3)
    {
        ShowMessage("That serial key is not valid!");
        Edit1->SetFocus();
    }

    if (result == -4)
    {
        ShowMessage("File reading error!");
    }
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
void __fastcall TAboutAmalyticoFrame::showLicenseText(TObject *Sender)
{
    TShowFileContentForm* e = new TShowFileContentForm(Application);
    e->Memo1->Lines->LoadFromFile("LICENSE.txt");
    e->ShowModal();
    delete e;
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


