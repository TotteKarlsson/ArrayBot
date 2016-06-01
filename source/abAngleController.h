#ifndef abAngleControllerH
#define abAngleControllerH
#include "abExporter.h"
#include "abABObject.h"
#include "mtkIniFile.h"
#include "mtkProperties.h"
#include "mtkINIFileProperties.h"
#include "abDeviceManager.h"
#include <string>
//---------------------------------------------------------------------------

using std::string;
using mtk::IniFile;
using mtk::IniFileProperties;
using mtk::Property;
class APTMotor;
class JoyStick;

//!An angle controller is an object that
//controls a motor that controls an angle.

class AB_CORE AngleController : public ABObject
{
	public:
      							            AngleController(const string& name, IniFile& iniFile);
     							            ~AngleController();

		bool				                initialize();
		bool 					            isActive();
		void 					            shutDown();
		string					            getName() const;
        void					            setAngle(double a);
        double					            getAngle();
		void					            stop();
		APTMotor*				            getMotor();
		void								enableJoyStick(JoyStick* js);
		void								disableJoyStick();
        Property<int>		                mMotorSerial;
        Property<double>  	                mAngle;
        Property<int>						mAngleOffset;
        Property<string>   	                mName;
    	DeviceManager	                    mDeviceManager;

    private:
    	APTMotor*				            mMotor;
        JoyStick*               			mJoyStick;
        IniFile&			                mIniFile;
        IniFileProperties	                mProperties;

};

#endif
