#ifndef EnvironmentalSensorReadThreadH
#define EnvironmentalSensorReadThreadH
#include <functional>
#include <string>
#include "dslThread.h"
#include "core/WatchDogServer.h"
//---------------------------------------------------------------------------

using namespace dsl;
using std::string;

class EnvironmentalSensorReadThread : public dsl::Thread
{
	typedef boost::function<void(int, int)> Callback;
	public:
								EnvironmentalSensorReadThread(const string& executable = "c:\\usr\\bin\\snmpget.exe");
		void					assignCallBacks(Callback one, Callback two, Callback three);
        void					assignServer(WatchDogServer* aServer);
        virtual void            run();

    protected:
        bool					mIsPresent;
        string 					mAlias;
    	double					mTemperature;
    	double					mHumidity;
    	double					mDewPoint;
		WatchDogServer*			mServer;
    	string 				    mExecutable;
        string					getAliasOID(WatchDogSensor* sensor);
        string					getPresentOID(WatchDogSensor* sensor);
        string					getTempOID(WatchDogSensor* sensor);
        string					getHumidityOID(WatchDogSensor* sensor);
        string					getDewPointOID(WatchDogSensor* sensor);

	    Callback 			    onEnter;
	    Callback 			    onProgress;
	    Callback 			    onExit;
		bool					querySensor(WatchDogSensor* s);
		int 					parseOutput(const string& s, WatchDogSensor* sensor);
};





#endif
