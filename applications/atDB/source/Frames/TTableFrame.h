#ifndef TTableFrameH
#define TTableFrameH
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
#include <string>
#include "dslStopWatch.h"

//---------------------------------------------------------------------------
using std::string;
using dsl::StopWatch;

class PACKAGE TTableFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TDBGrid *DBGrid1;
	TDBNavigator *DBNavigator1;
	TDataSource *DataSource1;
	TClientDataSet *ClientDataSet1;
	TDataSetProvider *DataSetProvider1;
	TSQLDataSet *SQLDataSet1;
	TTimer *LockoutCheckTimer;
	void __fastcall LockoutCheckTimerTimer(TObject *Sender);
	void __fastcall DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBGrid1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);



private:
	TSQLConnection* 		mDBConnection;
    Poco::Timespan			mLockoutTimeout;

public:
				__fastcall TTableFrame(TComponent* Owner);
    bool					loadTable(const string& t);
    void					assignDBconnection(TSQLConnection* c);
    void					unlock();
    void					lock();
    StopWatch				mLockoutTimer;

};

extern PACKAGE TTableFrame *TableFrame;
#endif
