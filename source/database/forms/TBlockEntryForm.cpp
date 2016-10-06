#include <vcl.h>
#pragma hdrstop
#include "TBlockEntryForm.h"
#include "mtkLogger.h"
#include <Poco/Data/MySQL/MySQLException.h>
#include "Poco/Data/RecordSet.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TATDBServerEntry"
#pragma resource "*.dfm"
TBlockEntryForm *BlockEntryForm;

using namespace mtk;
using Poco::Data::RecordSet;
//---------------------------------------------------------------------------
__fastcall TBlockEntryForm::TBlockEntryForm(ATDBServerSession& dbs, TComponent* Owner)
	:
    TATDBServerEntry(dbs, Owner)
{
	mCancelBtn->TabOrder = 3;
    mSubmitButton->TabOrder = 4;
}

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
        //Fetch data
        RecordSet *rs =  mServerSession.getUsers();
        if(!rs->rowCount())
        {
            Log(lInfo) << "There are no users...";
        }
        else
        {
            int cols = rs->columnCount();
            int rows = rs->rowCount();

            // iterate over all rows and columns
            for (RecordSet::Iterator it = rs->begin(); it != rs->end(); ++it)
            {
                Poco::Data::Row& row = *it;
                string user(row[1].convert<std::string>());
				mUserCB->Items->Add(user.c_str());
                Log(lInfo) <<user;
            }
            mUserCB->ItemIndex = 0;
        }
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

void __fastcall TBlockEntryForm::mValidateTimerTimer(TObject *Sender)
{
	 mSubmitButton->Enabled  =  (mBlockLabel->Text.Length() > 10) ? true : false;
}
//---------------------------------------------------------------------------

