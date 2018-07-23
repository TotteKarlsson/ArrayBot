#ifndef atUtilsH
#define atUtilsH
#include "atCoreExporter.h"
#include <vector>
#include <string>
#include "dslStringList.h"
#include "dslProperty.h"
#include "dslTypeInfo.h"
#include "dslIniFile.h"
//---------------------------------------------------------------------------

namespace at
{

using std::string;
using std::vector;
using dsl::StringList;
using dsl::Property;
using dsl::IniFile;

//!We are using an enum for process type in order to save/retrieve different processes from XML
enum ProcessType
{
	ptBaseType = 0,
    ptParallel,
    ptAbsoluteMove,
    ptArduinoServerCommand,
    ptTimeDelay,
    ptStopAndResume,
    ptArrayCamRequest,
    ptArrayBotRequest,
    ptMoveCoverSlipAtAngle,
    ptHomeMotor,
    ptUnknown
};

AT_CORE string 			toString(ProcessType tp);
AT_CORE ProcessType 	toProcessType(const string& str);
AT_CORE int 			extractCoverSlipID(const string& bc);

//!Logic operators, used in triggers
enum LogicOperator {loLargerThan = 0, loSmallerThan, loLargerThanOrEqual, loSmallerThanOrEqual, loEqualTo, loUndefined};

AT_CORE string 			toString(LogicOperator o);
AT_CORE LogicOperator 	toLogicOperator(const string& p);

						//!Thorlab errors
AT_CORE string 			tlError(int errCode);

}


#endif
