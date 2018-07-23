#ifndef TDataModulesUtilsH
#define TDataModulesUtilsH
#include "database/atDBCredentials.h"
#include <Data.SqlExpr.hpp>
//---------------------------------------------------------------------------

bool PACKAGE connect(const DBCredentials& c, TSQLConnection* con);
bool PACKAGE connect(const string& host, const string& db, const string& user, const string& pwd, TSQLConnection* con);

#endif
