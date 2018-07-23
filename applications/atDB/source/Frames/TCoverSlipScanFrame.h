#ifndef TCoverSlipScanFrameH
#define TCoverSlipScanFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTSTDStringLabeledEdit.h"
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include "dslTIntegerLabeledEdit.h"
#include <Vcl.DBCtrls.hpp>
#include <Vcl.Mask.hpp>
#include "TMoviesFrame.h"
#include "TRibbonNotesFrame.h"

//---------------------------------------------------------------------------
class TCoverSlipScanFrame : public TFrame
{
    __published:
        TGroupBox *GroupBox1;
	TDataSource *DataSource1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *ClientDataSet1;
	TIntegerLabeledEdit *CSIDE;
	TGroupBox *GroupBox3;
	TPanel *Panel1;
	TPanel *TopPanel;
	TSQLDataSet *SQLDataSet1;
	TWideStringField *SQLDataSet1ribbon_id;
	TWideStringField *SQLDataSet1animal_id;
	TSQLTimeStampField *SQLDataSet1intake_date;
	TIntegerField *SQLDataSet1slice_id;
	TIntegerField *SQLDataSet1block_id;
	TSmallintField *SQLDataSet1block_status;
	TIntegerField *SQLDataSet1knife_id;
	TIntegerField *SQLDataSet1cutting_order;
	TSmallintField *SQLDataSet1nr_of_sections;
	TWideStringField *ClientDataSet1ribbon_id;
	TWideStringField *ClientDataSet1animal_id;
	TSQLTimeStampField *ClientDataSet1intake_date;
	TIntegerField *ClientDataSet1slice_id;
	TIntegerField *ClientDataSet1block_id;
	TIntegerField *ClientDataSet1knife_id;
	TIntegerField *ClientDataSet1cutting_order;
	TSmallintField *ClientDataSet1nr_of_sections;
	TIntegerField *SQLDataSet1ribbon_status;
	TDBNavigator *DBNavigator1;
	TStringField *ClientDataSet1blockStatusL;
	TStringField *ClientDataSet1ribbonStatusL;
	TLabel *Label2;
	TDBEdit *DBEdit2;
	TLabel *Label3;
	TDBEdit *DBEdit3;
	TLabel *Label4;
	TDBEdit *DBEdit4;
	TLabel *Label5;
	TDBEdit *DBEdit5;
	TLabel *Label6;
	TDBEdit *DBEdit6;
	TLabel *Label7;
	TDBEdit *DBEdit7;
	TLabel *Label8;
	TDBEdit *DBEdit8;
	TLabel *Label9;
	TDBLookupComboBox *DBLookupComboBox1;
	TLabel *Label10;
	TDBLookupComboBox *DBLookupComboBox2;
	TSmallintField *ClientDataSet1block_status;
	TIntegerField *ClientDataSet1ribbon_status;
	TMoviesFrame *MoviesFrame1;
	TWideStringField *SQLDataSet1summary;
	TSmallintField *SQLDataSet1infiltration_protocol;
	TWideStringField *ClientDataSet1summary;
	TSmallintField *ClientDataSet1infiltration_protocol;
	TLabel *Label1;
	TDBEdit *DBEdit1;
	TStringField *ClientDataSet1blockResin;
	TLabel *Label11;
	TDBLookupComboBox *DBLookupComboBox3;
	TPanel *Panel2;
	TRibbonNotesFrame *TRibbonNotesFrame1;
	TPanel *BottomPanel;

    private:
    	int					mCSID;

    public:
    			__fastcall 	TCoverSlipScanFrame(TComponent* Owner);
		void				populate(int csID, const Poco::Path& p);
};

extern PACKAGE TCoverSlipScanFrame *CoverSlipScanFrame;
#endif
