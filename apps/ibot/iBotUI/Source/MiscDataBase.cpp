#pragma hdrstop
#include "TMainForm.h"
#include "dslTMemoLogger.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "dslSQLiteQuery.h"
#include "dslSQLiteTable.h"
#include "dslSQLiteException.h"
#include "dslMoleculixException.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


using namespace dsl;
extern string gCommonAppDataLocation;
//---------------------------------------------------------------------------
bool TMainForm::ConnectToDataBase(const string& dbName)
{
    Log(lInfo) << "Creating DB connection with DB: "<<dbName;

    //This will trigger the OnBeforeConnect event
    //Setup db parameters in the event
    string dbPath = joinPath (gCommonAppDataLocation, dbName + ".db");

    return true;
}


