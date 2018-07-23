#pragma hdrstop
#include "atDBCredentials.h"
//---------------------------------------------------------------------------


void DBCredentials::setup(const string& h, const string& db, const string& user, const string& pwd)
{
    mHost = h;
    mDB = db;
    mUserName = user;
    mUserPassword = pwd;
}

