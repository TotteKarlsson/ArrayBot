#ifndef abUtilitiesH
#define abUtilitiesH
#include "CoreExporter.h"
#include <vector>
#include <string>
#include "mtkStringList.h"
//---------------------------------------------------------------------------
using std::string;
using std::vector;
using mtk::StringList;
struct TLI_DeviceInfo;


///Enum holding Thorlab Device IDS
enum DeviceTypeID {didTCubeDCServo = 83, didLongTravelStage = 45, didTCubeStepperMotor = 80};

///getDeviceSerials populate a Stringlist with serial numbers for
///devices of the type supplied
AB_CORE StringList 	getSerialsForDeviceType(DeviceTypeID deviceID);
AB_CORE	bool        buildDeviceList();
AB_CORE	int         getNumberOfConnectedDevices();

AB_CORE string 		toString(DeviceTypeID val);
AB_CORE string 		toString(const TLI_DeviceInfo& val);
AB_CORE string 		tlError(int errCode);
#endif
