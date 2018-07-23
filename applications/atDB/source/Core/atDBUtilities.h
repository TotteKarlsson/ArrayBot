#ifndef atDBUtilitiesH
#define atDBUtilitiesH
#include "atDBCoreExporter.h"
#include "atDBDataStructures.h"

//---------------------------------------------------------------------------
ATDB_CORE void loadStyles();
ATDB_CORE void setupApplicationTheme();
ATDB_CORE void setupLogging();
ATDB_CORE bool sendAppMessage(ApplicationMessageEnum msg, void* struc = NULL);

#endif
