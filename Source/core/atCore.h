#ifndef atCoreH
#define atCoreH
#include "atCoreExporter.h"
#include <string>

#define MOTOR_WARNING_MESSAGE 	"MOTOR_WARNING_MESSAGE"
#define INFO_MESSAGE_DIALOG 	"INFO_MESSAGE_DIALOG"

using std::string;
namespace at
{
    typedef unsigned int uint;
	AT_CORE string 				getAPIVersion();
	AT_CORE const unsigned int 	getABCoreMessageID(const string& msg);
	AT_CORE void 				initABCoreLib();
}

#endif
