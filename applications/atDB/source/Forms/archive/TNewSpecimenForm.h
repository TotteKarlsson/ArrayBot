#ifndef TNewSpecimenFormH
#define TNewSpecimenFormH
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
class TNewSpecimenForm : public TForm
{
__published:	// IDE-managed Components
	TDataSource *DataSource1;
	TScrollBox *ScrollBox1;
	TPanel *Panel1;
	TButton *Button1;
	TButton *CancelBtn;
	TLabel *Label1;
	TDBEdit *DBEdit1;
	TLabel *Label2;
	TDBEdit *DBEdit2;
	TLabel *Label3;
	TDBEdit *DBEdit3;
	TDBLookupComboBox *DBLookupComboBox1;
	TDBLookupComboBox *DBLookupComboBox2;
	TLabel *Label4;
	TLabel *Label5;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
public:		// User declarations
	__fastcall TNewSpecimenForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNewSpecimenForm *NewSpecimenForm;
//---------------------------------------------------------------------------
#endif
