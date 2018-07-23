#ifndef TMainFormH
#define TMainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.DBXMySQL.hpp>
#include <Data.SqlExpr.hpp>
#include <Data.FMTBcd.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.Mask.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "DbxDevartPostgreSQL.hpp"
#include "TPGDataModule.h"
#include "TPGConnectionFrame.h"
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TActionList *ActionList1;
	TAction *ConnectToDBA;
	TGroupBox *GroupBox1;
	TDBGrid *DBGrid1;
	TDBNavigator *DBNavigator1;
	TGroupBox *GroupBox2;
	TDBGrid *DBGrid2;
	TDBNavigator *DBNavigator2;
	TDBMemo *DBMemo1;
	TDBGrid *DBGrid3;
	TPGConnectionFrame *TPGConnectionFrame1;
	TDBNavigator *DBNavigator3;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TPanel *Panel1;
	TTabSheet *TabSheet4;
	TDBGrid *DBGrid4;
	TDataSource *AllBlocksDSrc;
	TDBGrid *DBGrid5;
	TDBNavigator *DBNavigator4;
	TPanel *Panel2;
	TTabSheet *TabSheet5;
	TDBGrid *DBGrid6;
	TDBNavigator *DBNavigator5;

	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


private:	// User declarations
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};

extern PACKAGE TMainForm *MainForm;
#endif
