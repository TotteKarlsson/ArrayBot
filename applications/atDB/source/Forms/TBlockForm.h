#ifndef TBlockFormH
#define TBlockFormH
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
class TBlockForm : public TForm
{
__published:	// IDE-managed Components
	TDataSource *DataSource1;
	TPanel *Panel1;
	TButton *Button1;
	TButton *Button2;
	TDBEdit *DBEdit1;
	TLabel *Label1;
	TLabel *Label6;
	TDBLookupComboBox *DBLookupComboBox5;
	TLabel *Label7;
	TDBLookupComboBox *DBLookupComboBox6;
	TLabel *Label8;
	TDBLookupComboBox *DBLookupComboBox7;
	TLabel *Label9;
	TDBLookupComboBox *DBLookupComboBox8;
	TLabel *Label11;
	TDBLookupComboBox *DBLookupComboBox9;
	TGroupBox *GroupBox1;
	TLabel *Label12;
	TDBEdit *DBEdit2;
	TLabel *Label13;
	TDBLookupComboBox *DBLookupComboBox10;
	TLabel *Label14;
	TDBEdit *DBEdit3;
	TLabel *Label15;
	TDBLookupComboBox *DBLookupComboBox11;
	TLabel *Label2;
	TDBEdit *DBEdit4;
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
public:		// User declarations
	__fastcall TBlockForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBlockForm *BlockForm;
//---------------------------------------------------------------------------
#endif
