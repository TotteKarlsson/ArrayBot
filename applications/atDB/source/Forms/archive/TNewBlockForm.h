#ifndef TNewBlockFormH
#define TNewBlockFormH
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
class TNewBlockForm : public TForm
{
__published:	// IDE-managed Components
	TDataSource *DataSource1;
	TScrollBox *ScrollBox1;
	TPanel *Panel1;
	TButton *Button1;
	TButton *Button2;
	TDBEdit *DBEdit1;
	TLabel *Label1;
	TDBLookupComboBox *DBLookupComboBox1;
	TLabel *Label2;
	TLabel *Label10;
	TLabel *Label3;
	TDBLookupComboBox *DBLookupComboBox2;
	TLabel *Label4;
	TDBLookupComboBox *DBLookupComboBox3;
	TLabel *Label5;
	TDBLookupComboBox *DBLookupComboBox4;
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
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TNewBlockForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNewBlockForm *NewBlockForm;
//---------------------------------------------------------------------------
#endif
