#include <vcl.h>
#pragma hdrstop
#include "TAboutArduinoControllerForm.h"
#include "TShowFileContentForm.h"
#include "mtkApplicationInfo.h"
#include "mtkVCLUtils.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TAboutArduinoServerFrame"
#pragma resource "*.dfm"
TAboutArduinoControllerForm *AboutArduinoControllerForm;

using namespace mtk;
//---------------------------------------------------------------------------
__fastcall TAboutArduinoControllerForm::TAboutArduinoControllerForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAboutArduinoControllerForm::FormShow(TObject *Sender)
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
void __fastcall TAboutArduinoControllerForm::Button4Click(TObject *Sender)
{
    CloseModal();
}

//---------------------------------------------------------------------------
void __fastcall TAboutArduinoControllerForm::Button3Click(TObject *Sender)
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
void __fastcall TAboutArduinoControllerForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}

void __fastcall TAboutArduinoControllerForm::FormClose(TObject *Sender, TCloseAction &Action)
{
//    Action = caFree;
}

//---------------------------------------------------------------------------
void __fastcall TAboutArduinoControllerForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    //Check threads...
}


