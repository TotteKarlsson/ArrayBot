#ifndef abArduinoUtilsH
#define abArduinoUtilsH
#include "abExporter.h"
#include <string>
//---------------------------------------------------------------------------
using std::string;

int 	AB_CORE getArduinoIPCMessageID(const string& msg);
string  AB_CORE getArduinoIPCMessageName(int cs);

enum AB_IPC_ID
{
        cMakeAPuff            	= 500,
        cSetPufferPuffDuration 	= 501
};

#endif
