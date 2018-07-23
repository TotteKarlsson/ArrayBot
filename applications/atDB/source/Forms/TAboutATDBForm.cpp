#include <vcl.h>
#pragma hdrstop
#include "TAboutATDBForm.h"
#include "dslApplicationInfo.h"
#include "dslLogger.h"
#include <sstream>
#include "dslVersion.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TAboutATDBForm *AboutATDBForm;
using namespace std;
using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TAboutATDBForm::TAboutATDBForm(TComponent* Owner)
	: TForm(Owner)
{}

//---------------------------------------------------------------------------
void __fastcall TAboutATDBForm::FormShow(TObject *Sender)
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
void __fastcall TAboutATDBForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
    	this->Close();
    }
}


