#include <vcl.h>
#pragma hdrstop
#include "TBlockEntryForm.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TATDBServerEntry"
#pragma resource "*.dfm"
TBlockEntryForm *BlockEntryForm;

using namespace mtk;

//---------------------------------------------------------------------------
__fastcall TBlockEntryForm::TBlockEntryForm(ATDBServerSession& dbs, TComponent* Owner)
	:
    TATDBServerEntry(dbs, Owner)
{}

void __fastcall TBlockEntryForm::FormShow(TObject *Sender)
{
	if(!mServerSession.isConnected())
    {
    	//Disable..
        Log(lWarning) << "Not connected!";
        return;
    }

	//Populate user drop down
    try
    {
        RecordSet rs = mServerSession.getUsers();
//        else
//        {
//            bool more = rs->moveFirst();
//            int rows = rs->rowCount();
//            int cols = rs->columnCount();
//
//
//            while(more)
//            {
//                // print all column names
//                for (std::size_t col = 0; col < cols; ++col)
//                {
//                    Log(lInfo) << rs->columnName(col) << std::endl;
//                }
//
//                more = rs->moveNext();
//            }
//        }
//        delete rs;
    }
    catch(const Poco::Data::MySQL::StatementException& e)
    {
        Log(lError) << e.message() << endl;
    }
    catch(const Poco::Data::MySQL::MySQLException& e)
    {
        Log(lError) << e.message() << endl;
    }
    catch(const Poco::NullPointerException& e)
    {
    	Log(lError) << "Null Pointer exception..";
    }
    catch(...)
    {
    	Log(lError) << "Unhandled exception...";
    }

}


