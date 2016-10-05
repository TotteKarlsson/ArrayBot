#pragma hdrstop
#include "abDBUtils.h"
#include "Poco/Data/SQLite/SQLiteException.h"
#include "Poco/Data/MySQL/MySqlException.h"
#include "mtkLogger.h"


//---------------------------------------------------------------------------
namespace ab
{
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
    catch(const Poco::NullPointerException& e)
    {
        Log(lError) << e.message() << endl;
    }
    catch(const InvalidSQLStatementException&e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const InternalDBErrorException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const DBAccessDeniedException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const ExecutionAbortedException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const DBLockedException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const TableLockedException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const NoMemoryException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const ReadOnlyException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const InterruptException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const IOErrorException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const CorruptImageException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const TableNotFoundException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const DatabaseFullException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const CantOpenDBFileException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const LockProtocolException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const InternalDBErrorException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const SchemaDiffersException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const RowTooBigException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const ConstraintViolationException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const DataTypeMismatchException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const InvalidLibraryUseException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const OSFeaturesMissingException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const AuthorizationDeniedException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const CorruptImageException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const CorruptImageException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const InvalidSQLStatementException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const SQLiteException& e )
    {
        Log(lError) << e.message() << endl;
    }
    catch(const Poco::Data::SQLite::SQLiteException& e)
    {
        Log(lError) << e.message() << endl;
    }
    catch(...)
    {
    	Log(lError) << "Unhandled PocoDataMySQL exception...";
    }

//		throw InvalidSQLStatementException(std::string("SQL error or missing database"), addErrMsg);
//	case SQLITE_INTERNAL:
//		throw InternalDBErrorException(std::string("An internal logic error in SQLite"), addErrMsg);
//	case SQLITE_PERM:
//		throw DBAccessDeniedException(std::string("Access permission denied"), addErrMsg);
//	case SQLITE_ABORT:
//		throw ExecutionAbortedException(std::string("Callback routine requested an abort"), addErrMsg);
//	case SQLITE_BUSY:
//		throw DBLockedException(std::string("The database file is locked"), addErrMsg);
//	case SQLITE_LOCKED:
//		throw TableLockedException(std::string("A table in the database is locked"), addErrMsg);
//	case SQLITE_NOMEM:
//		throw NoMemoryException(std::string("A malloc() failed"), addErrMsg);
//	case SQLITE_READONLY:
//		throw ReadOnlyException(std::string("Attempt to write a readonly database"), addErrMsg);
//	case SQLITE_INTERRUPT:
//		throw InterruptException(std::string("Operation terminated by sqlite_interrupt()"), addErrMsg);
//	case SQLITE_IOERR:
//		throw IOErrorException(std::string("Some kind of disk I/O error occurred"), addErrMsg);
//	case SQLITE_CORRUPT:
//		throw CorruptImageException(std::string("The database disk image is malformed"), addErrMsg);
//	case SQLITE_NOTFOUND:
//		throw TableNotFoundException(std::string("Table or record not found"), addErrMsg);
//	case SQLITE_FULL:
//		throw DatabaseFullException(std::string("Insertion failed because database is full"), addErrMsg);
//	case SQLITE_CANTOPEN:
//		throw CantOpenDBFileException(std::string("Unable to open the database file"), addErrMsg);
//	case SQLITE_PROTOCOL:
//		throw LockProtocolException(std::string("Database lock protocol error"), addErrMsg);
//	case SQLITE_EMPTY:
//		throw InternalDBErrorException(std::string("(Internal Only) Database table is empty"), addErrMsg);
//	case SQLITE_SCHEMA:
//		throw SchemaDiffersException(std::string("The database schema changed"), addErrMsg);
//	case SQLITE_TOOBIG:
//		throw RowTooBigException(std::string("Too much data for one row of a table"), addErrMsg);
//	case SQLITE_CONSTRAINT:
//		throw ConstraintViolationException(std::string("Abort due to constraint violation"), addErrMsg);
//	case SQLITE_MISMATCH:
//		throw DataTypeMismatchException(std::string("Data type mismatch"), addErrMsg);
//	case SQLITE_MISUSE:
//		throw InvalidLibraryUseException(std::string("Library used incorrectly"), addErrMsg);
//	case SQLITE_NOLFS:
//		throw OSFeaturesMissingException(std::string("Uses OS features not supported on host"), addErrMsg);
//	case SQLITE_AUTH:
//		throw AuthorizationDeniedException(std::string("Authorization denied"), addErrMsg);
//	case SQLITE_FORMAT:
//		throw CorruptImageException(std::string("Auxiliary database format error"), addErrMsg);
//	case SQLITE_NOTADB:
//		throw CorruptImageException(std::string("File opened that is not a database file"), addErrMsg);
//	case SQLITE_RANGE:
//		throw InvalidSQLStatementException(std::string("Bind Parameter out of range (Access of invalid position 0? bind starts with 1!)"), addErrMsg);
//	case SQLITE_ROW:
//		break; // sqlite_step() has another row ready
//	case SQLITE_DONE:
//		break; // sqlite_step() has finished executing
//	default:
//		throw SQLiteException(std::string("Unkown error code: ") + Poco::NumberFormatter::format(rc), addErrMsg);
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

}//Namespace ab

