#ifndef UIUtilitiesH
#define UIUtilitiesH
#include "abUIDataStructures.h"
#include "dslStringList.h"

//---------------------------------------------------------------------------
PACKAGE void loadStyles();
PACKAGE void setupApplicationTheme(const string& appRegRoot, string& theme);
PACKAGE bool sendAppMessage(ApplicationMessageEnum msg, void* struc = NULL);

#endif
