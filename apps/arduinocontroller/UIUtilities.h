#ifndef UIUtilitiesH
#define UIUtilitiesH
#include "abUIDataStructures.h"
#include "mtkSQLite.h"
#include "mtkStringList.h"

using mtk::SQLite;
using mtk::StringList;
#define AML_CORE
//---------------------------------------------------------------------------
AML_CORE void loadStyles();
AML_CORE void setupApplicationTheme();
AML_CORE void setupLogging();

AML_CORE bool sendAppMessage(ApplicationMessageEnum msg, void* struc = NULL);


#endif
