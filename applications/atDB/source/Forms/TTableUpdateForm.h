#ifndef TTableUpdateFormH
#define TTableUpdateFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>

//---------------------------------------------------------------------------
class TTableUpdateForm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TComboBox *tableCB;
	TDBGrid *DBGrid1;
	TSQLDataSet *SQLDataSet1;
	TClientDataSet *ClientDataSet1;
	TDataSetProvider *DataSetProvider1;
	TDBNavigator *DBNavigator1;
	TDataSource *DataSource1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tableCBChange(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
	TSQLConnection* mDBConnection;

    public:		// User declarations
	__fastcall TTableUpdateForm(TSQLConnection* c, TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTableUpdateForm *TableUpdateForm;
//---------------------------------------------------------------------------
#endif
