#pragma hdrstop
#include "abDeviceManager.h"
#include "mtkLogger.h"
#include "mtkUtils.h"
#include "abUtilities.h"
#include "abTCubeDCServo.h"
#include "abTCubeStepperMotor.h"
#include "abLongTravelStage.h"
#include "abThorlabStructs.h"
//---------------------------------------------------------------------------

using namespace std;
using namespace mtk;

DeviceManager::DeviceManager()
{
	buildDeviceList();
}

DeviceManager::~DeviceManager()
{
    disConnectAll();
}

bool DeviceManager::reBuildDeviceList()
{
    if(!::buildDeviceList())
    {
    	Log(lError) <<"Failed re-building device list";
        return false;
    }
	return true;
}

bool DeviceManager::disConnectAll()
{
    for(mDevicesIter = mDevices.begin(); mDevicesIter != mDevices.end(); mDevicesIter++)
    {
		APTDevice* dev = mDevicesIter->second;
        if(dev)
        {
        	dev->disconnect();

            //Todo: implement graceful shutdown of all devices
            delete dev;
        }
    }
    mDevices.clear();
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

    //TCubeDCServos
    StringList serials(getSerialsForDeviceType(didTCubeDCServo));
    if(serials.count())
    {
        Log(lDebug) <<"Connecting devices of type "<<toString(didTCubeDCServo);
        for(u_int i = 0; i < serials.count(); i++)
        {
            APTDevice* device = connectDevice(toInt(serials[i]));
        }
    }

    //LTS devices
    Log(lDebug) <<"Connecting devices of type "<<toString(didLongTravelStage);
    StringList lts_serials(getSerialsForDeviceType(didLongTravelStage));
    if(lts_serials.count())
    {
        for(u_int i = 0; i < lts_serials.count(); i++)
        {
            APTDevice* device = connectDevice(toInt(lts_serials[i]));
        }
    }

    //LTS devices
    Log(lDebug) <<"Connecting devices of type "<<toString(didTCubeStepperMotor);
    StringList tcsm_serials(getSerialsForDeviceType(didTCubeStepperMotor));
    if(tcsm_serials.count())
    {
        for(u_int i = 0; i < tcsm_serials.count(); i++)
        {
            APTDevice* device = connectDevice(toInt(tcsm_serials[i]));
        }
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
	    Log(lError) <<"Failed getting device info for device with serial:"<<serial;
		Log(lError) <<"Device with serial "<<serial<<" was not connected";
        return NULL;
    }

    Log(lDebug3) <<"Device info: "<< ::toString(deviceInfo);

    //Create and open the device
    APTDevice* device = NULL;

    switch(deviceInfo.typeID)
    {
        case didTCubeDCServo:
            Log(lInfo) << "Creating a "<<toString(didTCubeDCServo)<<" device";
            device = new TCubeDCServo(serial);
        break;

        case didTCubeStepperMotor:
            Log(lDebug3) << "Creating a "<<toString(didTCubeStepperMotor)<<" device";
            device = new TCubeStepperMotor(serial);
        break;

        case didLongTravelStage:
            Log(lDebug3) << "Creating a "<<toString(didLongTravelStage)<<" device";
            device = new LongTravelStage(serial);
        break;

        default:
			Log(lError) << "Device of type: "<<toString(deviceInfo.typeID)<<" was not created";
    }

	if(device)
    {
        //Add device to internal map
        mDevices[serial] = device;
        if(device->connect())
        {
            //Flash LED
            device->identify();
        }
    }
    return device;
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

string DeviceManager::getInfo() const
{
    stringstream info;
    info << "No info yet...";
    return info.str();
}

