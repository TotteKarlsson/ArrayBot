#include <vcl.h>
#pragma hdrstop
#include "TAboutArduinoServerForm.h"
#include "TShowFileContentForm.h"
#include "mtkApplicationInfo.h"
#include "mtkVCLUtils.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TAboutArduinoServerFrame"
#pragma resource "*.dfm"
TAboutArduinoServerForm *AboutArduinoServerForm;

using namespace mtk;
//---------------------------------------------------------------------------
__fastcall TAboutArduinoServerForm::TAboutArduinoServerForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAboutArduinoServerForm::FormShow(TObject *Sender)
{
    if(!mAboutFrame)
    {
        mAboutFrame = new TAboutArduinoServerFrame(this);
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
void __fastcall TAboutArduinoServerForm::Button4Click(TObject *Sender)
{
    CloseModal();
}

//---------------------------------------------------------------------------
void __fastcall TAboutArduinoServerForm::Button3Click(TObject *Sender)
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
void __fastcall TAboutArduinoServerForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}

void __fastcall TAboutArduinoServerForm::FormClose(TObject *Sender, TCloseAction &Action)
{
//    Action = caFree;
}

//---------------------------------------------------------------------------
void __fastcall TAboutArduinoServerForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    //Check threads...
}


