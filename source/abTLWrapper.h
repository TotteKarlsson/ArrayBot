#ifndef abTLWrapperH
#define abTLWrapperH
#include "CoreExporter.h"
#include <map>
#include <string>
//---------------------------------------------------------------------------
//#include "Thorlabs.MotionControl.IntegratedStepperMotors.h"



using std::map;
using std::string;

class AB_CORE ThorLabsData
{
    public:
							ThorLabsData();
		string				getDeviceTypeName(int id);
	private:
		map<int, string> 	mDeviceIDMap;
};

////Wrappers around thorlabs C API
//AB_CORE int                 buildDeviceList();
//AB_CORE int                 getDeviceListSize();
//AB_CORE int                 getDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);
//AB_CORE int                 buildDeviceList(void);
//AB_CORE int                 getDeviceListSize();
//AB_CORE int                 getDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);
//AB_CORE int                 getDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);
//AB_CORE int                 getDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);
//AB_CORE int                 getDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);
//AB_CORE void                close(char const * serialNo);
//AB_CORE void                identify(char const * serialNo);
//AB_CORE WORD                getLEDswitches(char const * serialNo);
//AB_CORE DWORD               getFirmwareVersion(char const * serialNo);
//AB_CORE DWORD               getSoftwareVersion(char const * serialNo);
//AB_CORE void                setCalibrationFile(char const * serialNo, char const *filename, bool enabled);
//AB_CORE bool                loadSettings(char const * serialNo);
//AB_CORE int  		        getPoSition(char const * serialNo);
//AB_CORE unsigned int        getHomingVelocity(char const * serialNo);
//AB_CORE int                 moveRelative(char const * serialNo, int displacement);
//AB_CORE int                 setJogStepSize(char const * serialNo, unsigned int stepSize);
//AB_CORE int                 moveJog(char const * serialNo, MOT_TravelDirection jogDirection);
//AB_CORE int                 moveAtVelocity(char const * serialNo, MOT_TravelDirection direction);
//AB_CORE int                 stopImmediate(char const * serialNo);
//AB_CORE int                 stopProfiled(char const * serialNo);
//AB_CORE long                getBacklash(char const * serialNo);
//AB_CORE int                 setPositionCounter(char const * serialNo, long count);
//AB_CORE MOT_LimitsSoftwareApproachPolicy  ISC_GetSoftLimitMode(char const * serialNo);
//AB_CORE void                setLimitsSoftwareApproachPolicy(char const * serialNo, MOT_LimitsSoftwareApproachPolicy limitsSoftwareApproachPolicy);
//AB_CORE int                 getButtonParams(char const * serialNo, MOT_ButtonModes * buttonMode, int * leftButtonPosition, int * rightButtonPosition, int * timeout);
//AB_CORE int                 getVelParamsBlock(const char * serialNo, MOT_VelocityParameters  *velocityParams);
//AB_CORE int                 setVelParamsBlock(const char * serialNo, MOT_VelocityParameters *velocityParams);
//AB_CORE int                 setMoveAbsolutePosition(const char * serialNo, int position);
//AB_CORE int                 setMoveRelativeDistance(const char * serialNo, int distance);
//AB_CORE int                 getHomingParamsBlock(const char * serialNo, MOT_HomingParameters *homingParams);
//AB_CORE int                 setHomingParamsBlock(const char * serialNo, MOT_HomingParameters *homingParams);
//AB_CORE int                 getJogParamsBlock(const char * serialNo, MOT_JogParameters *jogParams);
//AB_CORE int                 setJogParamsBlock(const char * serialNo, MOT_JogParameters *jogParams);
//AB_CORE int                 getBowIndex(const char * serialNo);
//AB_CORE int                 requestPosition(char const * serialNo);
//AB_CORE int                 requestStatus(char const * serialNo);
//AB_CORE long                pollingDuration(char const * serialNo);
//AB_CORE int                 requestSettings(char const * serialNo);
//AB_CORE MOT_TravelModes  	getMotorTravelMode(char const * serialNo);
//AB_CORE int  				setMotorParAms(char const * serialNo, long stepsPerRev, long gearBoxRatio, float pitch);
//AB_CORE int  				getMotorParAms(char const * serialNo, long *stepsPerRev, long *gearBoxRatio, float *pitch);
#endif
