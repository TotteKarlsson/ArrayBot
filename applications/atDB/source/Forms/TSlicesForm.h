#ifndef TSlicesFormH
#define TSlicesFormH
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
class TSlicesForm : public TForm
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
	TLabel *Label4;
	TDBEdit *DBEdit4;
	TLabel *Label5;
	TDBEdit *DBEdit5;
	TLabel *Label6;
	TDBLookupComboBox *DBLookupComboBox1;
	TLabel *Label7;
	TDBLookupComboBox *DBLookupComboBox2;
	TLabel *Label8;
	TDBLookupComboBox *DBLookupComboBox3;
	TLabel *Label9;
	TDBLookupComboBox *DBLookupComboBox4;
	TLabel *Label10;
	TDBLookupComboBox *DBLookupComboBox5;
	TLabel *Label11;
	TDBLookupComboBox *DBLookupComboBox6;
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBLookupComboBoxDropDown(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TSlicesForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSlicesForm *SlicesForm;
//---------------------------------------------------------------------------
#endif
