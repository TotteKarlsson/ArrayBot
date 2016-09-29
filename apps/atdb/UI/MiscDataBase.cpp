#pragma hdrstop
#include "TMainForm.h"
#include "TMemoLogger.h"
#include "mtkVCLUtils.h"
#include "mtkLogger.h"
#include "mtkSQLiteQuery.h"
#include "mtkSQLiteTable.h"
#include "mtkSQLiteException.h"
#include "mtkMoleculixException.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


using namespace mtk;
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


