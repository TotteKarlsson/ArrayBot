#ifndef TRegisterFreshCSBatchFormH
#define TRegisterFreshCSBatchFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTIntegerLabeledEdit.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Data.DB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Mask.hpp>
#include "dslTSTDStringLabeledEdit.h"
 //---------------------------------------------------------------------------
class TRegisterFreshCSBatchForm : public TForm
{
__published:	// IDE-managed Components
	TDateTimePicker *mDT;
	TIntegerLabeledEdit *mCSCount;
	TDBLookupComboBox *mCSTypeLookup;
	TLabel *Label1;
	TButton *mRegisterBtn;
	TLabel *Label2;
	TSTDStringLabeledEdit *mCoverSlipLOTE;
	TSTDStringLabeledEdit *mBoxof100NrEdit;
	void __fastcall mRegisterBtnClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormShow(TObject *Sender);

private:

public:
	__fastcall TRegisterFreshCSBatchForm(TComponent* Owner);
};

extern PACKAGE TRegisterFreshCSBatchForm *RegisterFreshCSBatchForm;
#endif
