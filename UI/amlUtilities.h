#ifndef amlUtilitiesH
#define amlUtilitiesH
//#include "abCoreExporter.h"
#include "amlDataStructures.h"
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

AML_CORE string updateStateOrRegionData(const string& sor);
AML_CORE StringList fixStatesOrRegionsData(const StringList& orders);

#endif
