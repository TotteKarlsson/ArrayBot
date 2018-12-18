#pragma hdrstop
#include "atAPTDevice.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------


namespace at
{
APTDevice::APTDevice(int serial)
    :
    mSerial(dsl::toString(serial)),
    mIsConnected(false),
    mDeviceTypeID(didUnknown),
    mName("<none>")
{
    mProperties.setSectionName(dsl::toString(serial));
    mProperties.add((BaseProperty*) &mName.setup("NAME", 			"<none>", true));
}

APTDevice::~APTDevice()
{}

void APTDevice::setName(const string& name)
{
    mName = name;
}

string APTDevice::getName() const
{
    return mName.getValue();
}

string APTDevice::getSerial() const
{
    return mSerial.getValue();
}

bool APTDevice::isConnected() const
{
    return mIsConnected;
}

bool APTDevice::loadProperties(IniFile& iniFile)
{
    Log(lDebug) << "Loading properties for APT device with serial: "<<mSerial;
    mProperties.setIniFile(&iniFile);
    mProperties.read();

    Log(lDebug) << "Applying properties";
    applyProperties();
    return true;
}

bool APTDevice::writeProperties(IniFile& iniFile)
{
    Log(lDebug) << "Writing properties for APT device with serial: "<<mSerial;
    mProperties.setIniFile(&iniFile);
    mProperties.write();
    return true;
}

}
