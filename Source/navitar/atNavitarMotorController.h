#ifndef atNavitarMotorControllerH
#define atNavitarMotorControllerH
#include "thirdparty/navitar/navusbAPI.h"
#include <string>
#include "atATObject.h"
#include "atNavitarMotor.h"
//---------------------------------------------------------------------------

using std::string;

namespace at
{
    //!The NavitarMotorControl class is a Wrapper class for the Navitar USB motor controller API
    class AT_NAVITAR NavitarMotorController : public ATObject
    {
       	friend NavitarMotor;
    	public:
    							            NavitarMotorController();
    							            ~NavitarMotorController();
    		bool				            connect();
            bool				            disConnect();
            bool				            isConnected();

    		bool				            home();

            NavitarMotor&                   getZoom();
            void							setZoom(int z);
            void							zoomIn(int val);
            void							zoomOut(int val);

            NavitarMotor&                   getFocus();
            void							setFocus(int f);
            void							focusIn(int val);
            void							focusOut(int val);

            void							setFocusAndZoom(int f, int z);
    		string				            getProductID();
    		string				            getDriverSoftwareBuildDate();
            string                          getHardwareVersion();
            string                          getSoftwareVersion();
            int								getHandle(){return mMotorControllerHandle;}
            bool							setPreset(int zoom, int focus);

    	protected:
        	int					            mMotorControllerHandle;
            NavitarMotor		            mZoom;
    		NavitarMotor		            mFocus;

     		string 				            parseVersion(long val);
     		string 				            parseDate(long val);
            int								write(const int& reg, long value);
            int								read(const int& reg, long& v);
    };
}


#endif
