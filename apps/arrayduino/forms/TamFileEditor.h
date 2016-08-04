//---------------------------------------------------------------------------
#ifndef TamFileEditorH
#define TamFileEditorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <Dialogs.hpp>
#include <StdActns.hpp>
#include <System.Actions.hpp>
#include <vector>
#include "mtkStringList.h"
//---------------------------------------------------------------------------
using std::string;
using std::vector;
using mtk::StringList;

//Make this to a mtkChild
class PACKAGE TamFileEditor : public TForm
{
__published:    // IDE-managed Components
    TPanel *Panel1;
    TMemo *Memo1;
    TActionList *ActionList1;
    TAction *SaveFileAction1;
    TSaveDialog *SaveDialog1;
    TAction *SaveAsAction;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall SaveFileAction1Execute(TObject *Sender);
    void __fastcall ReloadFileActionExecute(TObject *Sender);
    void __fastcall SaveAsActionExecute(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:

public:
                    __fastcall TamFileEditor(const StringList& strs, TApplication* Owner);
    bool            __fastcall Read(const string& file);
    bool            __fastcall Write(const string& file);

};
//---------------------------------------------------------------------------
extern PACKAGE TamFileEditor *amFileEditor;
//---------------------------------------------------------------------------
#endif
