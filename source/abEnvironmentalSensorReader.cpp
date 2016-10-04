#pragma hdrstop
#include "abEnvironmentalSensorReader.h"
//---------------------------------------------------------------------------

void EnvironmentaSensorReader::addReading(double t, double h, int sensor_id)
{
	mReadings.push_back( SensorReading(t, h, sensor_id));
}

void EnvironmentaSensorReader::purge()
{
	mReadings.clear();
}

vector<SensorReading> EnvironmentaSensorReader::getReadings()
{
	return mReadings;
}

double EnvironmentaSensorReader::getAverageTemperature()
{
	double tAvg = 0;
    for(int i = 0; i < mReadings.size(); i++)
    {
		tAvg += mReadings[i].mTemperature;
    }
    return tAvg / mReadings.size();
}

double EnvironmentaSensorReader::getAverageHumidity()
{
	double hAvg = 0;
    for(int i = 0; i < mReadings.size(); i++)
    {
		hAvg += mReadings[i].mHumidity;
    }
    return hAvg / mReadings.size();
}



