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
    					        XYZUnit(JoyStick* js);
    					        ~XYZUnit();
		bool				    initialize();
		APTMotor*			    getXMotor();
		APTMotor*			    getYMotor();
		APTMotor*			    getZMotor();

        IniFileProperties	    mProperties;
        Property<int>		    mXMotorSerialNr;
        Property<int>		    mYMotorSerialNr;
        Property<int>		    mZMotorSerialNr;
    	DeviceManager	        mDeviceManager;

	protected:

        APTMotor*			    mXMotor;
        APTMotor*			    mYMotor;
        APTMotor*			    mZMotor;
        JoyStick*               mJoyStick;
        IniFile					mIniFile;
};
#endif
