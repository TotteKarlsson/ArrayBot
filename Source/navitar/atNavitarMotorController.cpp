#pragma hdrstop
#include "atNavitarMotorController.h"
#include "dslLogger.h"
#include "poco/DateTime.h"
#include "dslUtils.h"

using namespace dsl;
using namespace std;

namespace at
{
    enum NavitarMotorEnum {nmZoom = 1, nmFocus};
    //---------------------------------------------------------------------------
    using namespace dsl;
    using Poco::DateTime;

    //---------------------------------------------------------------------------
    NavitarMotorController::NavitarMotorController()
    :
    mMotorControllerHandle(0),
    mZoom( *this, nmZoom),
    mFocus(*this, nmFocus)
    {
    }

    //---------------------------------------------------------------------------
    NavitarMotorController::~NavitarMotorController()
    {
    }

    NavitarMotor& NavitarMotorController::getZoom()
    {
    	return mZoom;
    }

    NavitarMotor& NavitarMotorController::getFocus()
    {
    	return mFocus;
    }

    //---------------------------------------------------------------------------
    bool NavitarMotorController::connect()
    {
        //Check for connected devices
        int res = USBFindUSBinterfaces();
        Log(lInfo) <<"Return value from Navitar API: USBFindUSBinterfaces "<<res;

    	Log(lDebug) <<"Connecting motor controller with ID: "<<1;
    	mMotorControllerHandle = USBConnectionConnect(1, DEF_MOTOR_CONTROLLER);

        if(mMotorControllerHandle == 256)
        {
            Log(lInfo) <<"FAILED to connect to Navitar Motor controller";
            mMotorControllerHandle = 0;
            return false;
        }

    	return true;
    }

    //---------------------------------------------------------------------------
    bool NavitarMotorController::disConnect()
    {
    	int res = USBConnectionDisconnect(mMotorControllerHandle);
        mMotorControllerHandle = 0;
        return true;
    }

    //---------------------------------------------------------------------------
    bool NavitarMotorController::isConnected()
    {
        return ((mMotorControllerHandle > 0) && mMotorControllerHandle != 256) ? true : false;
    }

    //---------------------------------------------------------------------------
    int	NavitarMotorController::write(const int& reg, long value)
    {
    	if(mMotorControllerHandle)
        {
    		int res = USBConnectionWrite(mMotorControllerHandle, reg, &value);
            return res;
        }
        return 0;
    }

    //---------------------------------------------------------------------------
    int	NavitarMotorController::read(const int& reg, long& value)
    {
    	if(mMotorControllerHandle)
        {
    		int res = USBConnectionRead(mMotorControllerHandle, reg, &value);
            return res;
        }
        return 0;
    }

    //---------------------------------------------------------------------------
    bool NavitarMotorController::home()
    {
    	mZoom.home();
        mFocus.home();
        return true;
    }

    //---------------------------------------------------------------------------
    string NavitarMotorController::getProductID()
    {
        if(!mMotorControllerHandle)
        {
        	return "UNDEFINED PRODUCT ID";
        }

    	long val;
        int res = USBConnectionRead(mMotorControllerHandle, REG_SYS_PRODUCTID, &val);
        Log(lDebug) <<"Reading Product ID:" << res;
        Log(lDebug) <<"Read result:" << val;

        if(val == 0x4001)
        {
        	return "Motor Controller";
        }
        else if(val == 0x4000)
        {
        	return "BrightLight Controller";
        }
        else
        {
        	return "UNDEFINED";
        }
    }

    //---------------------------------------------------------------------------
    string NavitarMotorController::getDriverSoftwareBuildDate()
    {
        if(!mMotorControllerHandle)
        {
        	return "UNDEFINED SW BUILD DATE";
        }

    	long val;
        int res = USBConnectionRead(mMotorControllerHandle, REG_SYS_VERSIONDATE, &val);
        Log(lDebug) <<"Reading version date:" << res<<", "<< val;
    	return parseDate(val);
    }

    //---------------------------------------------------------------------------
    string NavitarMotorController::getHardwareVersion()
    {
        if(!mMotorControllerHandle)
        {
        	return "UNDEFINED HW VERSION";
        }

    	long val;
        int res = USBConnectionRead(mMotorControllerHandle, REG_SYS_VERSIONHW, &val);
        Log(lDebug) <<"Reading hardware version:" << res<<", "<< val;
    	return parseVersion(val);
    }

    //---------------------------------------------------------------------------
    string NavitarMotorController::getSoftwareVersion()
    {
    	long val;
        int res = USBConnectionRead(mMotorControllerHandle, REG_SYS_VERSIONSW, &val);
        Log(lDebug) <<"Result and value from USBConnectionRead:" << res<<", "<< val;
    	return parseVersion(val);
    }

    //---------------------------------------------------------------------------
    string NavitarMotorController::parseVersion(long val)
    {
    	int major 	= (int) (((uint) val & 0xff000000) >> 24);
        int minor	= (int) (((uint) val & 0xff0000) >> 16);
        int rev 	= (int) (((uint) val & 0xff00) >> 8);
        int bug 	= (int) (( uint) val & 0xff);

    	stringstream str;
        str<<major<<"."<<minor<<"."<<rev<<"."<<bug;
    	return str.str();
    }

    //---------------------------------------------------------------------------
    string NavitarMotorController::parseDate(long val)
    {
    	int major 	= (int) (((uint) val & 0xff000000) >> 24);
        int minor	= (int) (((uint) val & 0xff0000) >> 16);
        int rev 	= (int) (((uint) val & 0xff00) >> 8);
        int bug 	= (int) (( uint) val & 0xff);

        DateTime dt(rev + 2000, major, minor);
    	return Poco::DateTimeFormatter::format(dt, "%n/%f/%Y");
    }

    bool NavitarMotorController::setPreset(int zoom, int focus)
    {
        mZoom.setPosition(zoom);
        mFocus.setPosition(focus);
        return true;
    }

    void NavitarMotorController::setZoom(int z)
    {
    	mZoom.setPosition(z);
    }

    void NavitarMotorController::zoomIn(int val)
    {
    	mZoom.addToPosition(val);
    }

    void NavitarMotorController::zoomOut(int val)
    {
    	mZoom.addToPosition(-1 * val);
    }

    void NavitarMotorController::setFocus(int f)
    {
    	mFocus.setPosition(f);
    }

    void NavitarMotorController::focusIn(int val)
    {
    	mFocus.addToPosition(val);
    }

    void NavitarMotorController::focusOut(int val)
    {
    	mFocus.addToPosition(-1 * val);
    }


    void NavitarMotorController::setFocusAndZoom(int f, int z)
    {
    	mFocus.setPosition(f);
    	mZoom.setPosition(z);
    }

}
