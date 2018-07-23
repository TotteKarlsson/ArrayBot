#ifndef TSpecimenFormH
#define TSpecimenFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>
#include "TPGDataModule.h"
//---------------------------------------------------------------------------
class TSpecimenForm : public TForm
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
	TLabel *Label1;
	TLabel *Label5;
	TDBMemo *DBMemo1;
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
public:		// User declarations
	__fastcall TSpecimenForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSpecimenForm *SpecimenForm;
//---------------------------------------------------------------------------
#endif
