#ifndef UIUtilitiesH
#define UIUtilitiesH
#include <windows.h>
#include "abUIDataStructures.h"
#include "mtkStringList.h"

#define PACKAGE __declspec(package)
//---------------------------------------------------------------------------
PACKAGE void loadStyles();
PACKAGE void setupApplicationTheme(const string& appRegRoot, string& theme);
PACKAGE void setupLogging(const string& logFileLocation, const string& logFileName);
PACKAGE bool sendAppMessage(ApplicationMessageEnum msg, void* struc = NULL);

#endif
