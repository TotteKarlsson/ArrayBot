#ifndef WatchDogServerH
#define WatchDogServerH
#include <string>
#include <vector>
#include "atCoreExporter.h"
#include "dslIniFile.h"
#include "dslIniFileProperties.h"
#include "WatchDogSensor.h"
//---------------------------------------------------------------------------
using dsl::IniFileProperties;
using dsl::IniFile;
using dsl::Property;
using std::string;
using std::vector;

class AT_CORE WatchDogServer
{
	public:
									                WatchDogServer(IniFile& ifile);
									                ~WatchDogServer();
		bool						                addSensor(WatchDogSensor* sensor);
        int							                getNumberOfSensors();
		WatchDogSensor*				                getSensor(int i);
		WatchDogSensor*				                getInbuiltSensor();
		WatchDogSensor*				                getSensorWithID(const string& id);
        void						                setIP(const string& ip);
		bool						                writeIniParameters();
		bool 						                readIniParameters();
        string 						                getOIDRoot(){return mOIDRoot;}

        string                                      SerialOID;
        string                                      AliasOID;
        string                                      AvailableOID;
        string                                      TemperatureOID;
        string                                      HumidityOID;
        string                                      DewPointOID;
        Property<string>&			                getServerIPProperty();
        Property<int>&				                getReadCycleTimeProperty();

    protected:
        IniFile&					                mIniFile;
        IniFileProperties   		                mProperties;
        Property<string>			                mServerIP;
		Property<string>			                mInBuiltSensorID;
		Property<int>				                mLocationID;
		Property<int>				                mReadCycleTime;

    								                //!These OID's are used to query the hardware for values
        string						                mOIDRoot;
        WatchDogSensor				                mInbuiltSensor;
        vector<WatchDogSensor*>		                mSensors;
};


#endif
