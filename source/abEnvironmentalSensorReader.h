#ifndef abEnvironmentalSensorReaderH
#define abEnvironmentalSensorReaderH
#include "abExporter.h"
#include "abABObject.h"
#include <utility>
#include <vector>
//---------------------------------------------------------------------------

using std::vector;

//A sensor reading is two doubles and an ID for the sensor
struct SensorReading
{
	SensorReading(double t, double h, int id) : mTemperature(t), mHumidity(h), mSensorID(id){}
	double mTemperature;
	double mHumidity;
    int    mSensorID;
};

//!The EnvironmentaSensorReader class are populated by one sensor at a time
class AB_CORE EnvironmentaSensorReader : public ABObject
{
    public:
					                EnvironmentaSensorReader(int nrOfSensors = 3) : mNrOfSensors(3){}
					                ~EnvironmentaSensorReader(){}

		int							getNumberOfSensors(){return mNrOfSensors;}
		int							getNumberOfReadings(){return mReadings.size();}
        void						purge();
		void						addReading(double t, double h, int sensor);

		vector<SensorReading>       getReadings();

		double				        getAverageTemperature();
		double				        getAverageHumidity();

    protected:
    	int							mNrOfSensors;
		vector<SensorReading> 		mReadings;

};
#endif
