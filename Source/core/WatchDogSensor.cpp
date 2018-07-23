#pragma hdrstop
#include "WatchDogSensor.h"
//---------------------------------------------------------------------------

WatchDogSensor::WatchDogSensor(const string& id, int location)
:
mDeviceID(id),
mInstance(0),
mSubRootOID(-1),
mLocationID(location),
mIsPresent(false)
{}

WatchDogSensor::~WatchDogSensor()
{
}

double WatchDogSensor::getTemperature()
{
	return mTemp;
}

double WatchDogSensor::getHumidity()
{
	return mHumidity;
}

double WatchDogSensor::getDewPoint()
{
	return mDewPoint;
}

bool WatchDogSensor::isPresent()
{
	return mIsPresent;
}

void WatchDogSensor::update(const string& alias, double t, double h, double d, bool isPresent)
{
	mAlias = alias;
    mTemp = t;
    mHumidity = h;
    mDewPoint = d;
    mIsPresent = isPresent;
}

string WatchDogSensor::getDeviceID()
{
	return mDeviceID;
}

string WatchDogSensor::getAlias()
{
	return mAlias;
}
