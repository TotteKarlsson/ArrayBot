#ifndef abXYZUnitH
#define abXYZUnitH
#include "CoreExporter.h"
#include "abABObject.h"
#include "mtkProperties.h"
#include "abUtilities.h"
#include "abDeviceManager.h"
#include "mtkINIFileProperties.h"
#include "mtkINIFile.h"

//---------------------------------------------------------------------------
class APTMotor;
class JoyStick;
using mtk::IniFileProperties;
using mtk::Property;
using mtk::IniFile;

class AB_CORE XYZUnit : public ABObject
{
	public:
    					        XYZUnit(const string& name, JoyStick* js, IniFile& iniFile);
    					        ~XYZUnit();
		bool				    initialize();
        bool					stopAll();

		APTMotor*			    getXMotor();
		APTMotor*			    getYMotor();
		APTMotor*			    getZMotor();


        Property<int>		    mXMotorSerialNr;
        Property<int>		    mYMotorSerialNr;
        Property<int>		    mZMotorSerialNr;
    	DeviceManager	        mDeviceManager;

	protected:
        IniFileProperties	    mProperties;
        APTMotor*			    mXMotor;
        APTMotor*			    mYMotor;
        APTMotor*			    mZMotor;
        JoyStick*               mJoyStick;
        IniFile&				mIniFile;
};
#endif
