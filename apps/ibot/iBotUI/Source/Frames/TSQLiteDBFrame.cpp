#include <vcl.h>
#pragma hdrstop
#include "TSQLiteDBFrame.h"
#include "mtkLogger.h"
#include "mtkSQLiteTable.h"
#include "mtkSQLiteQuery.h"
#include "mtkMoleculixException.h"
#include "ibUtilities.h"
#include "mtkUtils.h"
#include "mtkWin32Utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntLabel"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"
TSQLiteDBFrame *SQLiteDBFrame;

using namespace mtk;
//---------------------------------------------------------------------------
__fastcall TSQLiteDBFrame::TSQLiteDBFrame(TComponent* Owner)
    : TFrame(Owner)
{
}

void TSQLiteDBFrame::updateFrame()
{
}
//---------------------------------------------------------------------------
void TSQLiteDBFrame::setDBName(const string& name)
{
    mDBName = name;
    string fullPath = joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "iBot", mDBName + ".db");
    DBNameE->setValue(fullPath);
    DBNameE->Enabled = false;
    bool exists = fileExists(fullPath);

    if(!exists)
    {

    }
    else
    {
        try
        {
            if(mDB.open(fullPath))
            {
                Log(lDebug) << "Opened DB"<<fullPath;
                updateFrame();

            }
        }
        catch(const MoleculixException& e)
        {
            Log(lError) << "Exception: "<<e.what();
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TSQLiteDBFrame::Button1Click(TObject *Sender)
{
    //Truncate database table
    try
    {
        if(MessageDlg("You are about to delete your local data?\n", mtWarning, TMsgDlgButtons() << mbOK<<mbCancel, 0) == mrOk)
        {

//            int count = mDB.execDML("DELETE FROM 'orders'");
//            Log(lDebug2)<< "Deleted "<<count<<" orders from local database";
//
//            count = mDB.execDML("DELETE FROM 'customers'");
//            Log(lDebug2)<< "Deleted "<<count<<" customers from local database";
//
//			count = mDB.execDML("DELETE FROM 'state_or_regions'");
//			Log(lDebug2)<< "Deleted "<<count<<" states or regions from local database";
//
//            //Clean up internals
//            SQLiteQuery q  = mDB.execQuery("SELECT count(*) FROM sqlite_master WHERE type='table' AND name='SQLITE_SEQUENCE';");
//            count = q.getIntField(0,0);
//            if(count)
//            {
//                mDB.execDML("DELETE FROM SQLITE_SEQUENCE WHERE name='orders'");
//            }
            updateFrame();
        }
    }
    catch(const MoleculixException& e)
    {
        Log(lError) << "Exception: "<<e.what();
    }
}
