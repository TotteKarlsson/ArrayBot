#ifndef UIUtilitiesH
#define UIUtilitiesH
#include "abUIDataStructures.h"
#include "dslSQLite.h"
#include "dslStringList.h"

using dsl::SQLite;
using dsl::StringList;
#define AML_CORE
//---------------------------------------------------------------------------
AML_CORE void loadStyles();
AML_CORE void setupApplicationTheme();
AML_CORE void setupLogging();

AML_CORE bool sendAppMessage(ApplicationMessageEnum msg, void* struc = NULL);


#endif
