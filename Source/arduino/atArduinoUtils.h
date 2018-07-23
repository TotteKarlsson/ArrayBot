#ifndef atArduinoUtilsH
#define atArduinoUtilsH
#include "atCoreExporter.h"
#include <string>
#include "atArduinoExporter.h"
//---------------------------------------------------------------------------
using std::string;

int 	AT_ARDUINO getArduinoIPCMessageID(const string& msg);
string  AT_ARDUINO getArduinoIPCMessageName(int cs);

enum AB_IPC_ID
{
        cMakeAPuff            	= 500,
        cSetPufferPuffDuration 	= 501
};

#endif
