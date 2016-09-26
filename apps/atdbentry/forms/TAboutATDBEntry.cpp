#include <vcl.h>
#pragma hdrstop
#include "TAboutATDBEntry.h"
#include "TShowFileContentForm.h"
#include "mtkApplicationInfo.h"
#include "mtkVCLUtils.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TAboutATDBEntryFrame"
#pragma resource "*.dfm"
TAboutATDBEntry *AboutATDBEntry;

using namespace mtk;
//---------------------------------------------------------------------------
__fastcall TAboutATDBEntry::TAboutATDBEntry(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAboutATDBEntry::FormShow(TObject *Sender)
{
    if(!mAboutFrame)
    {
        mAboutFrame = new TAboutATDBDataEntryFrame(this);
        mAboutFrame->Visible = false;
        mAboutFrame->populate();
        mAboutFrame->Parent =  this;
        mAboutFrame->AutoSize = true;
        mAboutFrame->Align = alClient;
		Button3Click(Sender);
        mAboutFrame->Visible = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TAboutATDBEntry::Button4Click(TObject *Sender)
{
    CloseModal();
}

//---------------------------------------------------------------------------
void __fastcall TAboutATDBEntry::Button3Click(TObject *Sender)
{
    try
    {
        mAboutFrame->mChangeLogMemo->Lines->LoadFromFile("CHANGELOG.txt");
    }
    catch(...)
    {
        MessageDlg("There was a problem opening the file!", mtInformation, TMsgDlgButtons() << mbOK, 0);
    }
}

//---------------------------------------------------------------------------
void __fastcall TAboutATDBEntry::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}

void __fastcall TAboutATDBEntry::FormClose(TObject *Sender, TCloseAction &Action)
{
//    Action = caFree;
}

//---------------------------------------------------------------------------
void __fastcall TAboutATDBEntry::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    //Check threads...
}


