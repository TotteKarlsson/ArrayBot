#ifndef abUtilitiesH
#define abUtilitiesH
#include "abExporter.h"
#include <vector>
#include <string>
#include "mtkStringList.h"
#include "mtkProperty.h"
#include "mtkTypeInfo.h"
#include "mtkIniFile.h"
//---------------------------------------------------------------------------
using std::string;
using std::vector;
using mtk::StringList;
using mtk::Property;
using mtk::IniFile;
struct TLI_DeviceInfo;


///Enum holding Thorlab Device IDS
enum DeviceTypeID
{
	didUnknown=0,
    didLongTravelStage = 45,
    didTCubeStepperMotor = 80,
    didTCubeDCServo = 83
};

AB_CORE DeviceTypeID getDeviceTypeID(const string& level);


///getDeviceSerials populate a Stringlist with serial numbers for
///devices of the type supplied
AB_CORE StringList 	getSerialsForDeviceType(DeviceTypeID deviceID);
AB_CORE	bool        buildDeviceList();
AB_CORE	int         getNumberOfConnectedDevices();

AB_CORE string 		toString(DeviceTypeID val);
AB_CORE string 		toString(const TLI_DeviceInfo& val);
AB_CORE string 		tlError(int errCode);


//AB_CORE std::string toString(const DeviceTypeID& lvl);

template<> inline
std::string Property< DeviceTypeID >::getValueAsString() const
{
    return mtk::toString(getValue());
}

template<> inline
bool Property<DeviceTypeID>::write(IniFile* iniFile, const string& section)
{
    if(iniFile == NULL)
    {
        return false;
    }

    string toWrite;
    toWrite = mtk::toString(getValue());
    iniFile->writeString(mKey, toWrite, "", section);
    return true;
}

template<> inline
bool Property<DeviceTypeID>::read(IniFile* iniFile, const string& section)
{
    if(&iniFile == NULL)
    {
        return false;
    }

    string val(iniFile->readString(mKey, section, mtk::toString(mDefaultValue)));

    DeviceTypeID tempVal = getDeviceTypeID(val);

    mWasRead = iniFile->wasItFound();
    setValue( mWasRead ? tempVal : mDefaultValue);
    return mWasRead;
}

template<> inline
bool Property<DeviceTypeID>::assignValueFromString(const string& v)
{
    return false;
}

template<> inline
string Property<DeviceTypeID>::getTypeName() const
{
    return "DeviceTypeID";
}



#endif
