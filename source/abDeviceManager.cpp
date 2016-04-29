#pragma hdrstop
#include "abDeviceManager.h"
#include "mtkLogger.h"
#include "mtkUtils.h"
#include "abUtilities.h"
#include "abTCubeDCServo.h"
#include "Thorlabs.MotionControl.IntegratedStepperMotors.h"
//---------------------------------------------------------------------------

using namespace std;
using namespace mtk;

DeviceManager::DeviceManager()
{}

DeviceManager::~DeviceManager()
{
    disConnectAll();
}

string DeviceManager::getInfo() const
{
    stringstream info;
//    info<<setw(50)<<left<<"Number of loaded devices:"          <<getNumberOfPlugins()<<"\n";
//    info<<setw(50)<<left<<"Number of created device objects:"  <<mPluginObjects.size()<<"\n";
//    if(getNumberOfDevices())
//    {
//        info<<setw(25)<<left<<"Plugin Libraries"<<"\n";
//        mPluginsIter = mPlugins.begin();
//        while(mPluginsIter != mPlugins.end())
//        {
//            PluginLib pl = (*mPluginsIter).second;
//            info<<"  "<<setw(25)<<left<< getFileNameNoExtension(pl->getPath())<<"\n";
//            ++mPluginsIter;
//        }
//    }
    return info.str();
}

ostream& operator << (ostream& st, DeviceManager& pm)
{
    st<<pm.getInfo();
    return st;
}

int DeviceManager::getNumberOfConnectableDevices() const
{
	return ::getNumberOfConnectedDevices();
}

APTDevice* DeviceManager::getFirst() const
{
    mDevicesIter = mDevices.begin();
    if(mDevicesIter != mDevices.end())
    {
        return (*mDevicesIter).second;
    }
    return NULL;
}

APTDevice* DeviceManager::getCurrent() const
{
    if(mDevicesIter != mDevices.end())
    {
        return (*mDevicesIter).second;
    }
    return NULL;
}

APTDevice* DeviceManager::getNext() const
{
    if(mDevicesIter != mDevices.end())
    {
        mDevicesIter++;
        if(mDevicesIter != mDevices.end())
        {
            return (*mDevicesIter).second;
        }
    }
    return NULL;
}

APTDevice* DeviceManager::getPrevious() const
{
    if(mDevicesIter != mDevices.end())
    {
        mDevicesIter--;
        if(mDevicesIter != mDevices.end())
        {
            return (*mDevicesIter).second;
        }
    }
    return NULL;
}

int DeviceManager::connectAllDevices()
{
	//Get serials for all connectable devices
    if(!buildDeviceList())
    {
    	Log(lError) <<"Failed building device list";
        return 0;
    }

    Log(lInfo) <<"There are "<<getNumberOfConnectableDevices()<<" available devices.";
    StringList serials(getSerialsForDeviceType(didTCubeDCServo));

    //... other devices

    //Connect devices
    Log(lDebug) <<"Connecting devices of type "<<toString(didTCubeDCServo);
    for(int i = 0; i < serials.count(); i++)
    {
		APTDevice* device = connectDevice(toInt(serials[i]));

    }

	return getNumberOfConnectedDevices();
}

APTDevice* DeviceManager::connectDevice(int serial)
{
    Log(lDebug) <<"Connecting device with serial "<<serial;
    //First get device info so we know what to create
    TLI_DeviceInfo deviceInfo;

    // get device info from device
    int res = TLI_GetDeviceInfo(toString(serial).c_str(), &deviceInfo);
    if(res == 0)
    {
	    Log(lInfo) <<"Failed getting device info";
    }

    Log(lInfo) <<"Device info: "<< ::toString(deviceInfo);

    //Create and open the device
    APTDevice* device = NULL;

    switch(deviceInfo.typeID)
    {
        case didTCubeDCServo:
            Log(lInfo) << "Creating a "<<toString(didTCubeDCServo)<<" device";
            device = new TCubeDCServo(serial);
        break;
    }

    //Add device to internal map
    mDevices[serial] = device;
    if(!device->connect())
    {
        //Flash LED
        device->identify();
    }
    return device;
}

bool DeviceManager::disConnectAll()
{
    return true;
}

bool DeviceManager::disConnect(APTDevice* device)
{
    if(!device)
    {
        return disConnectAll();
    }

    bool result(false);
    return result;
}

APTDevice* DeviceManager::getDevice(int serial)
{
    return mDevices[serial];
}

StringList DeviceManager::getDeviceSerials() const
{
    StringList serials;
    for(mDevicesIter = mDevices.begin(); mDevicesIter != mDevices.end(); mDevicesIter++)
    {
        serials.append(toString((*mDevicesIter).first));
    }

    return serials;
}

int DeviceManager::getNumberOfConnectedDevices() const
{
    return mDevices.size();
}
