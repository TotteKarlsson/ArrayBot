#ifndef TSelectIntegerFormH
#define TSelectIntegerFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "dslTIntLabel.h"
//---------------------------------------------------------------------------
class PACKAGE TSelectIntegerForm : public TForm
{
	__published:	// IDE-managed Components
        TListBox *NumbersList;
        TPanel *Panel1;
        TArrayBotButton *OkBtn;
        TArrayBotButton *CancelBtn;
        TIntLabel *mTheNumberLbl;
        TGroupBox *GroupBox1;
        void __fastcall NumbersListClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall NumbersListDrawItem(TWinControl *Control, int Index, TRect &Rect,
              TOwnerDrawState State);

    private:	// User declarations
    public:		// User declarations
        				__fastcall  TSelectIntegerForm(TComponent* Owner);
        bool						setCurrentNumber(int nr);

};

extern PACKAGE TSelectIntegerForm *SelectIntegerForm;
#endif
