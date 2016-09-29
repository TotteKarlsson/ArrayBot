#ifndef ibUtilitiesH
#define ibUtilitiesH
#include "ibCoreExporter.h"
#include "ibDataStructures.h"
#include "mtkSQLite.h"
#include "mtkStringList.h"

using mtk::SQLite;
using mtk::StringList;

//---------------------------------------------------------------------------
IB_CORE void loadStyles();
IB_CORE void setupApplicationTheme();
IB_CORE void setupLogging();
IB_CORE bool sendAppMessage(ApplicationMessageEnum msg, void* struc = NULL);


#endif
