#ifndef TNewCaseFormH
#define TNewCaseFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>
#include "TATDBDataModule.h"
//---------------------------------------------------------------------------
class TNewCaseForm : public TForm
{
__published:	// IDE-managed Components
	TDataSource *DataSource1;
	TScrollBox *ScrollBox1;
	TPanel *Panel1;
	TButton *Button1;
	TButton *CancelBtn;
	TLabel *Label2;
	TDBEdit *DBEdit2;
	TLabel *Label3;
	TDBEdit *DBEdit3;
	TLabel *Label4;
	TDBLookupComboBox *UserCB;
	TDBLookupComboBox *DBLookupComboBox1;
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
public:		// User declarations
	__fastcall TNewCaseForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNewCaseForm *NewCaseForm;
//---------------------------------------------------------------------------
#endif
