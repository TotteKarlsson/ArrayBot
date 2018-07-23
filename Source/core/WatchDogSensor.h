#ifndef WatchDogSensorH
#define WatchDogSensorH
#include "atCoreExporter.h"
#include "dslConstants.h"
//---------------------------------------------------------------------------
using namespace dsl;

class WatchDogServer;

class AT_CORE WatchDogSensor
{
	friend WatchDogServer;
	public:

					                        WatchDogSensor(const string& id = gEmptyString, int location = 0);
					                        ~WatchDogSensor();
		string		                        getDeviceID();
		string		                        getAlias();
        void								setAlias(const string& a){mAlias = a;}
        int			                        getInstanceNr(){return mInstance;}

        void		                        update(const string& alias, double t, double h, double d, bool isPresent);
        void 		                        assignSubRootOID(const string& rootOID);

        double		                        getTemperature();
        double		                        getHumidity();
        double		                        getDewPoint();
        void		                        setTemperature(double v){mTemp = v;}
        void		                        setHumidity(double v){mHumidity = v;}
        void		                        setDewPoint(double v){mDewPoint = v;}

		bool		                        isPresent();
        void								isPresent(bool isit){mIsPresent = isit;}

        int									getSubRootOID(){return mSubRootOID;}
        int									getLocationID(){return mLocationID;}
        void 								setLocationID(int loc){mLocationID = loc;}
	protected:
    	int 		                        mSubRootOID;

        			                        //The instance number in the OID tree is an enumeration, i.e. sensor 1, sensor 2 etc..
        int			                        mInstance;

		int                                 mLocationID;

    	string		                        mDeviceID;
		bool		                        mIsPresent;
    	string		                        mAlias;
        double 		                        mTemp;
        double		                        mHumidity;
        double 		                        mDewPoint;
};

#endif
