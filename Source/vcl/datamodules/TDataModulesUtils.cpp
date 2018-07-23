#pragma hdrstop
#include "TDataModulesUtils.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace dsl;
bool connect(const DBCredentials& c, TSQLConnection* con)
{
    try
    {
        con->KeepConnection = true;
        con->Connected = false;
        con->Params->Values[_D("HostName")] = vclstr(c.getHost());
        con->Params->Values[_D("Database")] = vclstr(c.getDB());
        con->Params->Values[_D("User_Name")] = vclstr(c.getUserName());
        con->Params->Values[_D("Password")] = vclstr(c.getUserPassword());

        Log(lInfo) <<"Connecting to SQL server using connection parameters:\t"<<
                    "Host="		<<stdstr(con->Params->Values[_D("HostName")])<<"\t"<<
                    "UserNamet="<<stdstr(con->Params->Values[_D("User_Name")])<<"\t"<<
                    "Password="	<<stdstr(con->Params->Values[_D("Password")])<<"\t"<<
                    "Database="	<<stdstr(con->Params->Values[_D("Database")]);

        con->AutoClone      = false;
        con->KeepConnection = true;
        con->Connected = true;
        return con->Connected;
    }
    catch(const TDBXError& e)
    {
    	Log(lWarning) << stdstr(e.Message);
        return false;
    }
}

//---------------------------------------------------------------------------
bool connect(const string& host, const string& db, const string& user, const string& pwd, TSQLConnection* con)
{
    return connect(DBCredentials(host, db, user, pwd), con);
}

