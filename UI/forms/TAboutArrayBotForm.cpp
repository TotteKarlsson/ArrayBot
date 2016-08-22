#include <vcl.h>
#pragma hdrstop
#include "TAboutArrayBotForm.h"
#include "../source/vcl/forms/TShowFileContentForm.h"
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
    : TForm(Owner)
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
void __fastcall TAboutArrayBotForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}

void __fastcall TAboutArrayBotForm::FormClose(TObject *Sender, TCloseAction &Action)
{
//    Action = caFree;
}

//---------------------------------------------------------------------------
void __fastcall TAboutArrayBotForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    //Check threads...
}


