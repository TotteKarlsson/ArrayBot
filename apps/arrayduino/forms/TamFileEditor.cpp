#pragma hdrstop
#include "TamFileEditor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//#pragma link "*.dfm"
TamFileEditor *amFileEditor;
//---------------------------------------------------------------------------

__fastcall TamFileEditor::TamFileEditor(const StringList& strs, TApplication* Owner)
:
TForm(Owner)
{
    Memo1->Clear();
    for(unsigned int i = 0; i < strs.size(); i++)
    {
      Memo1->Lines->Add(strs[i].c_str());
    }
    Caption =  "No File";
}

//---------------------------------------------------------------------------
void __fastcall TamFileEditor::FormClose(TObject *Sender, TCloseAction &Action)
{
    Action = caFree;
}

//---------------------------------------------------------------------------
void __fastcall TamFileEditor::SaveFileAction1Execute(TObject *Sender)
{
//      Memo1->Lines->SaveToFile(Label1->Caption);
}

//---------------------------------------------------------------------------
void __fastcall TamFileEditor::ReloadFileActionExecute(TObject *Sender)
{
//      Memo1->Lines->LoadFromFile(Label1->Caption);
}

//---------------------------------------------------------------------------
void __fastcall TamFileEditor::SaveAsActionExecute(TObject *Sender)
{
      if(SaveDialog1->Execute())
      {
        Memo1->Lines->SaveToFile(SaveDialog1->FileName);
      }
}

//---------------------------------------------------------------------------
bool __fastcall TamFileEditor::Read(const string& file)
{
    ShowMessage("Reading is not implemented");
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall TamFileEditor::Write(const string& file)
{
    ShowMessage("Writing is not implemented");
    return false;
}

void __fastcall TamFileEditor::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}



