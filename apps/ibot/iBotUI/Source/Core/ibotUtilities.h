#ifndef ibotUtilitiesH
#define ibotUtilitiesH
#include "ibCoreExporter.h"
#include "ibDataStructures.h"
#include "dslSQLite.h"
#include "dslStringList.h"

using dsl::SQLite;
using dsl::StringList;

//---------------------------------------------------------------------------
IB_CORE void loadStyles();
IB_CORE void setupApplicationTheme();
IB_CORE void setupLogging();
IB_CORE bool sendAppMessage(ApplicationMessageEnum msg, void* struc = NULL);


#endif
