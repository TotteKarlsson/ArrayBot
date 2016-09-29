#pragma hdrstop
#include "abDBUtils.h"
//---------------------------------------------------------------------------

using namespace std;
string toString(dbSQLKeyword kw)
{
	switch(kw)
    {
    	case dbSQLKeyword::dbAscending: return "ASC";
    	case dbSQLKeyword::dbDescending: return "DESC";
    }
    return "";
}

