#ifndef atCoverSlipAngleControllerH
#define atCoverSlipAngleControllerH
#include "arraybot/atABExporter.h"
#include "atATObject.h"
#include "dslIniFile.h"
#include "dslProperties.h"
#include "dslINIFileProperties.h"
#include "atDeviceManager.h"
#include <string>
//---------------------------------------------------------------------------

using std::string;
using dsl::IniFile;
using dsl::IniFileProperties;
using dsl::Property;
class APTMotor;

class AT_AB CoverSlipAngleController : public ATObject
{
	public:
      							            CoverSlipAngleController(const string& name, IniFile& iniFile);
     							            ~CoverSlipAngleController();

		bool				                initialize();
		bool 					            isActive();
		void 					            shutDown();
		string					            getName() const;
        void					            setAngle(double a);
        double					            getAngle();
		void					            stop();
		APTMotor*				            getMotor();

        Property<int>		                mMotorSerial;
        Property<double>  	                mAngle;
        Property<string>   	                mName;
    	DeviceManager	                    mDeviceManager;

    private:
    	APTMotor*				            mAngleMotor;
        IniFile&			                mIniFile;
        IniFileProperties	                mProperties;
        int									mAngleOffset;
};

#endif
