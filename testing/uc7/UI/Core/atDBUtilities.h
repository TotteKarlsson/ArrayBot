#ifndef atDBUtilitiesH
#define atDBUtilitiesH
#include "atDBCoreExporter.h"
#include "atDBDataStructures.h"
#include "mtkSQLite.h"
#include "mtkStringList.h"

using mtk::SQLite;
using mtk::StringList;

//---------------------------------------------------------------------------
AML_CORE void loadStyles();
AML_CORE void setupApplicationTheme();
AML_CORE void setupLogging();
AML_CORE bool sendAppMessage(ApplicationMessageEnum msg, void* struc = NULL);

#endif
