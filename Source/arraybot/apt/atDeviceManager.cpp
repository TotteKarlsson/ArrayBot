#pragma hdrstop
#include <windows.h>
#include "thirdparty/thorlabs/Thorlabs.MotionControl.TCube.StepperMotor.h"
#include "atDeviceManager.h"
#include "dslLogger.h"
#include "dslUtils.h"
#include "core/atUtils.h"
#include "atTCubeDCServo.h"
#include "atTCubeStepperMotor.h"
#include "atLongTravelStage.h"
#include "atBenchTopStepperMotor.h"
//---------------------------------------------------------------------------

namespace at
{
AT_AB string 		toString(DeviceTypeID value);
AT_AB string 		toString(const TLI_DeviceInfo& val);
AT_AB StringList 	getSerialsForDeviceType(DeviceTypeID deviceID);
AT_AB DeviceTypeID  getDeviceTypeID(const string& id);
//AT_CORE DeviceTypeID getDeviceTypeID(const string& level);


using namespace std;
using namespace dsl;

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
    if(!buildDeviceList())
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
    st << pm.getInfo();
    return st;
}

int DeviceManager::getNumberOfConnectableDevices() const
{
	return at::getNumberOfConnectedDevices();
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

    Log(lInfo) <<"There are "<<getNumberOfConnectableDevices()<<" available device(s).";

    //LTS devices
    StringList serials(getSerialsForDeviceType(didLongTravelStage));
    if(serials.count())
    {
	    Log(lDebug) <<"Connecting devices of type "<<at::toString(didLongTravelStage);
        for(uint i = 0; i < serials.count(); i++)
        {
            if(!connectDevice(toInt(serials[i])))
            {
			    Log(lDebug) <<"Failed to connect devices of type "<<at::toString(didLongTravelStage)<<" with serial: "<<serials[i];
            }
        }
    }

    //TCubeStepperMotors
    serials.clear();
    serials.appendList(StringList(getSerialsForDeviceType(didTCubeStepperMotor)));
    if(serials.count())
    {
	    Log(lDebug) <<"Connecting devices of type "<<at::toString(didTCubeStepperMotor);
        for(uint i = 0; i < serials.count(); i++)
        {
            if(!connectDevice(toInt(serials[i])))
            {
			    Log(lDebug) <<"Failed to connect devices of type "<<at::toString(didTCubeStepperMotor)<<" with serial: "<<serials[i];
            }
        }
    }

    //TCubeDCServos
    serials.clear();
    serials.appendList(StringList(getSerialsForDeviceType(didTCubeDCServo)));
    if(serials.count())
    {
        Log(lDebug) <<"Connecting devices of type "<<at::toString(didTCubeDCServo);
        for(uint i = 0; i < serials.count(); i++)
        {
            if(!connectDevice(toInt(serials[i])))
            {
			    Log(lDebug) <<"Failed to connect devices of type "<<at::toString(didTCubeDCServo)<<" with serial: "<<serials[i];
            }
        }
    }

    //BenchTopStepperMotors
	serials.clear();
    serials.appendList(getSerialsForDeviceType(didBenchTopStepperMotor));
    if(serials.count())
    {
	    Log(lDebug) <<"Connecting devices of type "<<at::toString(didBenchTopStepperMotor);
        for(uint i = 0; i < serials.count(); i++)
        {
            if(!connectDevice(toInt(serials[i])))
            {
			    Log(lDebug) <<"Failed to connect devices of type "<<at::toString(didBenchTopStepperMotor)<<" with serial: "<<serials[i];
            }
        }
    }

	return getNumberOfConnectedDevices();
}

APTDevice* DeviceManager::connectDevice(int serial)
{
    if(serial != -1)
    {
    	Log(lInfo) <<"Connecting device with serial "<<serial;
    }
    else
    {
        return NULL;
    }

    //First get device info so we know what to create
    TLI_DeviceInfo deviceInfo;

    // get device info from device
    int res = TLI_GetDeviceInfo(toString(serial).c_str(), &deviceInfo);
    if(res == 0)
    {
        Log(lError) << "MotorType for device with serial: "<<serial<<" is: "<<deviceInfo.motorType;
	    Log(lError) << "Failed getting device info for device with serial:"<<serial;
        return NULL;
    }

    Log(lInfo) <<"Device info: "<< ::at::toString(deviceInfo);

    //Create and open the device
    APTDevice* device = NULL;

    switch(deviceInfo.typeID)
    {
        case didTCubeDCServo:
            Log(lInfo) << "Creating a "<<at::toString(didTCubeDCServo)<<" device";
            device = new TCubeDCServo(serial);
        break;

        case didTCubeStepperMotor:
            Log(lInfo) << "Creating a "<<at::toString(didTCubeStepperMotor)<<" device";
            device = new TCubeStepperMotor(serial);
        break;

        case didLongTravelStage:
            Log(lInfo) << "Creating a "<<at::toString(didLongTravelStage)<<" device";
            device = new LongTravelStage(serial);
        break;

        case didBenchTopStepperMotor:
            Log(lInfo) << "Creating a "<<at::toString(didBenchTopStepperMotor)<<" device";
            device = new BenchTopStepperMotor(serial);
        break;

        default:
			Log(lError) << "Device of type: "<<dsl::toString(deviceInfo.typeID)<<" was not created";
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
        serials.append(dsl::toString((*mDevicesIter).first));
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

bool buildDeviceList()
{
    // Build list of connected device
    return (TLI_BuildDeviceList() == 0) ? true : false;
}

int getNumberOfConnectedDevices()
{
	return TLI_GetDeviceListSize();
}

StringList getSerialsForDeviceType(DeviceTypeID deviceID)
{
	StringList serials;

    // Build list of connected device
//    if (TLI_BuildDeviceList() == 0)
	{
        // get device list size
        short n = TLI_GetDeviceListSize();
        if(n == 0)
        {
        	Log(lInfo) << "There are no open devices available";
        }

        // get serial numbers
        char serialNos[250];
        TLI_GetDeviceListByTypeExt(serialNos, 250, deviceID);

         // output list of matching devices
		serials = StringList(serialNos ,',');
     }
	return serials;
}

DeviceTypeID getDeviceTypeID(const string& id)
{
    string sid = toUpperCase(id);
    if (sid == "UNKNOWN")  					return didUnknown;
    if (sid == "LONGTRAVELSTAGE")   		return didLongTravelStage;
    if (sid == "TCUBESTEPPERMOTOR") 		return didTCubeStepperMotor;
    if (sid == "TCUBEDCSERVO")            	return didTCubeDCServo;
    if (sid == "BENCHTOPSTEPPERMOTOR")     	return didBenchTopStepperMotor;
    return didUnknown;
}

string toString(DeviceTypeID value)
{
	switch(value)
    {
    	case didTCubeDCServo:             	return "TCube DC Servo";
		case didLongTravelStage:          	return "Long Travel Stage";
		case didTCubeStepperMotor:        	return "TCube Stepper Motor";
		case didBenchTopStepperMotor:     	return "Benchtop Stepper Motor";
		default:
            Log(lWarning) <<"The devicetype ID\" "<<value<<"\" is not defined";
        	return "Device type is not defined";
    }
}

string toString(const TLI_DeviceInfo& val)
{
	stringstream str;
    str
    <<"Device Type ID: "<<val.typeID<<"\t"
    <<"Description: "	<<val.description<<"\t"
	<<"Serial: "		<<val.serialNo<<"\t"
	<<"Is Known Type: " <<val.isKnownType<<"\t";

    return str.str();
}


}
