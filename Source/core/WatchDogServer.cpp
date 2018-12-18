#pragma hdrstop
#include "WatchDogServer.h"
#include "WatchDogSensor.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------
using namespace dsl;

WatchDogServer::WatchDogServer(IniFile& ifile)
:
mIniFile(ifile),
mServerIP(""),
mInBuiltSensorID(""),
mOIDRoot("1.3.6.1.4.1.21239.5.1"),
SerialOID("1.2"),
AliasOID("1.3"),
AvailableOID("1.4"),
TemperatureOID("1.5"),
HumidityOID("1.6"),
DewPointOID("1.7"),
mLocationID(0),
mReadCycleTime(0)
{
    mProperties.setSectionName("WATCHDOG_SERVER");
	mProperties.add((BaseProperty*)  &mServerIP.setup(				"SERVER_IP",    	 		"192.168.123.123"));
	mProperties.add((BaseProperty*)  &mInBuiltSensorID.setup(		"INBUILT_SENSOR_ID",    	"-1"));
	mProperties.add((BaseProperty*)  &mLocationID.setup(			"LOCATION_ID",    			-1));
	mProperties.add((BaseProperty*)  &mReadCycleTime.setup(			"READ_CYCLE_TIME",    		0));
	mProperties.setIniFile(&mIniFile);
}

WatchDogServer::~WatchDogServer()
{}

Property<string>& WatchDogServer::getServerIPProperty()
{
	return mServerIP;
}

Property<int>& WatchDogServer::getReadCycleTimeProperty()
{
	return mReadCycleTime;
}

//Rename this to, readAndSetup
bool WatchDogServer::readIniParameters()
{
    mProperties.read();

	//Create the servers inbuilt sensor
    mInbuiltSensor.mDeviceID = mInBuiltSensorID;
    mInbuiltSensor.mSubRootOID = 2;
    mInbuiltSensor.mInstance = 1;
    mInbuiltSensor.setLocationID(mLocationID);
    addSensor(&mInbuiltSensor);

    //Check for external sensors
    StringList secs = mIniFile.getListOfSections();
    for(int i = 0; i < secs.count(); i++)
    {
    	if(startsWith("WATCHDOG_EXTERNAL_SENSOR", secs[i]))
        {
        	IniSection* sec = mIniFile.getSection(secs[i]);
            WatchDogSensor* sensor = new WatchDogSensor();
            sensor->mDeviceID	= sec->getKey("SENSOR_ID")->mValue;
            sensor->mInstance 	= dsl::toInt(sec->getKey("INSTANCE_ID_IN_TREE")->mValue);
            sensor->mLocationID = dsl::toInt(sec->getKey("LOCATION_ID")->mValue);
            sensor->mSubRootOID = 9;
            addSensor(sensor);
        }
    }
    return true;
}

bool WatchDogServer::writeIniParameters()
{
    return mProperties.write();
}

void WatchDogServer::setIP(const string& ip)
{
	mServerIP = ip;
}

bool WatchDogServer::addSensor(WatchDogSensor* sensor)
{
	mSensors.push_back(sensor);
    return true;
}

int WatchDogServer::getNumberOfSensors()
{
	return mSensors.size();
}

WatchDogSensor*	WatchDogServer::getSensor(int i)
{
	return mSensors[i];
}

WatchDogSensor*	WatchDogServer::getInbuiltSensor()
{
	return &mInbuiltSensor;
}

WatchDogSensor*	WatchDogServer::getSensorWithID(const string& id)
{
	for(int i = 0; i < mSensors.size(); i++)
    {
    	if(mSensors[i] && mSensors[i]->getDeviceID() == id)
        {
        	return mSensors[i];
        }
    }
    return NULL;
}
