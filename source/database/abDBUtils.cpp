#pragma hdrstop
#include "abDBUtils.h"
#include "Poco/Data/SQLite/SQLiteException.h"
#include "Poco/Data/MySQL/MySqlException.h"
#include "mtkLogger.h"


//---------------------------------------------------------------------------
using namespace Poco::Data;
using namespace Poco::Data::SQLite;
using namespace mtk;
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

void handleSQLiteException()
{
	try
    {
    	throw;
    }
    catch(const Poco::Data::SQLite::SQLiteException& e)
    {
        Log(lError) << e.message() << endl;
    }
    catch(const Poco::NullPointerException& e)
    {
        Log(lError) << e.message() << endl;
    }
    catch(...)
    {
    	Log(lError) << "Unhandled PocoDataMySQL exception...";
    }

}
void handleMySQLException()
{
	try
    {
    	throw;
    }
	catch (const Poco::Data::ConnectionFailedException& e)
    {
        Log(lError) << e.message() <<endl;
    }
   	catch (const Poco::Data::MySQL::ConnectionException& e)
    {
        Log(lError) << e.message() <<endl;
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
        Log(lError) << e.message() << endl;
    }
    catch(...)
    {
    	Log(lError) << "Unhandled PocoDataMySQL exception...";
    }

}

