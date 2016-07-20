#ifndef TOptionsFormH
#define TOptionsFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <vector>
#include "TApplicationProperties.h"
//---------------------------------------------------------------------------

class TGeneralOptionsFrame;
using std::vector;

namespace mtk
{
class IniFileProperties;
class RegistryProperties;
}

class TOptionsForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TPanel *Panel2;
    TActionList *ActionList1;
    TButton *Button1;
    TButton *CancelBtn;
    TTreeView *mTree;
    TAction *OKAction;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall mTreeClick(TObject *Sender);
    void __fastcall OKActionExecute(TObject *Sender);
    void __fastcall CancelBtnClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);

private:	// User declarations
    enum  OptionFrame { ofGeneral = 0, ofExplorer };
    bool                                            mCancelBtnWasClicked;

    TTreeNode*                          __fastcall  getSelected();
    void                                            showFrame(OptionFrame);
    TGeneralOptionsFrame*                           mGOF;
    vector<TFrame*>                                 mOptionFrames;
    TApplicationProperties&                         mApplicationProperties;
    TFrame*                                         mCurrentOptionFrame;
    void                                            applyChanges();
public:		// User declarations
                                        __fastcall  TOptionsForm(TApplicationProperties& props, TComponent* Owner);
};

extern PACKAGE TOptionsForm *OptionsForm;
#endif
