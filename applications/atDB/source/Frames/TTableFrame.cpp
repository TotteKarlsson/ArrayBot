#include <vcl.h>
#pragma hdrstop
#include "TTableFrame.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTableFrame *TableFrame;

using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TTableFrame::TTableFrame(TComponent* Owner)
	: TFrame(Owner),
    mLockoutTimeout(Poco::Timespan(360*Poco::Timespan::SECONDS))
{
}

//---------------------------------------------------------------------------
void TTableFrame::assignDBconnection(TSQLConnection* c)
{
	mDBConnection = c;
	SQLDataSet1->SQLConnection = mDBConnection;
}

void TTableFrame::unlock()
{
	DBNavigator1->Enabled = true;
    DBGrid1->Enabled = true;
    DBGrid1->ReadOnly = false;
    LockoutCheckTimer->Enabled = true;
    mLockoutTimer.start();
}

void TTableFrame::lock()
{
	DBNavigator1->Enabled = false;
    DBGrid1->Enabled = false;
    DBGrid1->ReadOnly = true;
    mLockoutTimer.stop();
}

//---------------------------------------------------------------------------
bool TTableFrame::loadTable(const string& t)
{
	if(!mDBConnection || mDBConnection->Connected == false)
    {
    	MessageDlg("You need to connect to remote ATDB database!", mtWarning, TMsgDlgButtons() << mbOK, 0);
        return false;
    }

	String tableName = vclstr(t);
	SQLDataSet1->Active 		= false;
    ClientDataSet1->Active 		= false;
    SQLDataSet1->CommandText 	= "SELECT * FROM " + tableName ;

	SQLDataSet1->Active = true;
    ClientDataSet1->Active = true;
    ClientDataSet1->Refresh();

    //Set all columnwidts
	int cols = DBGrid1->Columns->Count;
    for(int i = 0; i < cols; i++)
    {
		DBGrid1->Columns->Items[i]->Width = 200;
    }
	return true;
}

void __fastcall TTableFrame::LockoutCheckTimerTimer(TObject *Sender)
{
	if(mLockoutTimer.getElapsedTime() > mLockoutTimeout)
    {
    	lock();
		LockoutCheckTimer->Enabled = false;
    }
}

//---------------------------------------------------------------------------
void __fastcall TTableFrame::DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	mLockoutTimer.reStart();
}


//---------------------------------------------------------------------------
void __fastcall TTableFrame::DBGrid1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
	mLockoutTimer.reStart();
    Log(lDebug) << "Restarting table lockout timer";
}


