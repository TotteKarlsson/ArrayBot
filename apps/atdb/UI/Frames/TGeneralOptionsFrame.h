#ifndef TGeneralOptionsFrameH
#define TGeneralOptionsFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TIntegerLabeledEdit.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "mtkProperties.h"
#include "TPropertyCheckBox.h"
#include "TApplicationProperties.h"

using mtk::Properties;
class TOptionsForm;
//---------------------------------------------------------------------------
class PACKAGE TGeneralOptionsFrame : public TFrame
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TIntegerLabeledEdit *mNrOfHistoryItems;
    TGroupBox *GroupBox1;
    TActionList *ActionList1;
    TAction *ClearHistoryA;
    TButton *Button1;
    TGroupBox *GroupBox2;
    TPropertyCheckBox *ShowSplashOnStartupCB;
    void __fastcall mNrOfHistoryItemsKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall CheckBoxClick(TObject *Sender);
    void __fastcall ClearHistoryAExecute(TObject *Sender);

protected:	// User declarations
    TApplicationProperties&         mApplicationProperties;
    TOptionsForm*                   mParent;

public:		// User declarations
                    __fastcall      TGeneralOptionsFrame(TApplicationProperties& props, TComponent* Owner);
                    __fastcall      ~TGeneralOptionsFrame();
    bool                            hasChanges();
	void __fastcall                 setup();

};
//---------------------------------------------------------------------------
extern PACKAGE TGeneralOptionsFrame *GeneralOptionsFrame;
//---------------------------------------------------------------------------
#endif
