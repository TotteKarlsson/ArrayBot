#ifndef abDBUtilsH
#define abDBUtilsH
#include "abExporter.h"
#include <string>
//---------------------------------------------------------------------------

namespace ab
{
enum dbSQLKeyword {dbAscending = 0, dbDescending};

std::string AB_CORE toString(dbSQLKeyword kw);


//!MySQL stuff
void AB_CORE handleMySQLException();



//!SQLite stuff
void AB_CORE handleSQLiteException();

}
#endif
