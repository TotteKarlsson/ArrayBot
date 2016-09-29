#ifndef abDBUtilsH
#define abDBUtilsH
#include "abExporter.h"
#include <string>
//---------------------------------------------------------------------------

enum dbSQLKeyword {dbAscending = 0, dbDescending};

std::string AB_CORE toString(dbSQLKeyword kw);
#endif
