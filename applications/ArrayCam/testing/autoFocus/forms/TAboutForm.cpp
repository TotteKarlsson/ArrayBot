#include <vcl.h>
#pragma hdrstop
#include "TAboutForm.h"
#include "dslApplicationInfo.h"
#include "dslVersion.h"
#include "dslVCLUtils.h"
#include <sstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


using namespace dsl;
using namespace std;

TAboutForm *AboutForm;


//---------------------------------------------------------------------------
__fastcall TAboutForm::TAboutForm(TComponent* Owner)
	: TForm(Owner)
{}

//---------------------------------------------------------------------------
void __fastcall TAboutForm::FormCreate(TObject *Sender)
{
	//Populate MEMO
    stringstream ss;
    dslApplicationInfo appInfo(Application);

    //Current Version Info
    Version version(stdstr(appInfo.mVersion));
    ss <<version.getMajor()<<"."<<version.getMinor()<<"."<<version.getPatch();
    String versionMajorMinorPatch(ss.str().c_str());
    versionLabel->Caption = String("Version: ") + versionMajorMinorPatch;

     if(fileExists("CHANGELOG.txt"))
    {
	    Memo1->Lines->LoadFromFile("CHANGELOG.txt");
    }
}

//---------------------------------------------------------------------------
void __fastcall TAboutForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}


