#ifndef TGeneralOptionsFrameH
#define TGeneralOptionsFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTIntegerLabeledEdit.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "dslProperties.h"
#include "dslTPropertyCheckBox.h"
#include "dslApplicationProperties.h"
#include "dslTPropertyCheckBox.h"

using dsl::Properties;
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
    ApplicationProperties&          mApplicationProperties;
    TOptionsForm*                   mParent;

public:		// User declarations
                    __fastcall      TGeneralOptionsFrame(ApplicationProperties& props, TComponent* Owner);
                    __fastcall      ~TGeneralOptionsFrame();
    bool                            hasChanges();
	void __fastcall                 setup();

};
//---------------------------------------------------------------------------
extern PACKAGE TGeneralOptionsFrame *GeneralOptionsFrame;
//---------------------------------------------------------------------------
#endif
