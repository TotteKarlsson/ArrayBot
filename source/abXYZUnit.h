#ifndef abXYZUnitH
#define abXYZUnitH
#include "abExporter.h"
#include "abABObject.h"

#include "abUtilities.h"
#include "abDeviceManager.h"
#include "mtkProperties.h"
#include "mtkINIFileProperties.h"
#include "mtkINIFile.h"
#include "abXYZUnitPositions.h"
//---------------------------------------------------------------------------
class APTMotor;
class JoyStick;
using mtk::IniFileProperties;
using mtk::Property;
using mtk::IniFile;

class AB_CORE XYZUnit : public ABObject
{
	public:
    					        XYZUnit(const string& name, IniFile& iniFile);
    					        ~XYZUnit();
		void					home();
		void					stow();

		void				    shutDown();
		string					getName();
        XYZUnitPositions&		positions(){return mPositions;}
        void					enableJoyStick(JoyStick* js);
        void					disableJoyStick();

		bool				    initialize();
        bool					stopAll();

		APTMotor*			    getXMotor();
		APTMotor*			    getYMotor();
		APTMotor*			    getZMotor();

        Property<int>		    mXMotorSerialNr;
        Property<int>		    mYMotorSerialNr;
        Property<int>		    mZMotorSerialNr;

        						//Todo: move the devicemanager to ArrayBot and
                                //use a reference for each class needing to use it
    	DeviceManager	        mDeviceManager;
        bool					moveToPosition(const XYZUnitPosition& pos);

	protected:
		string					mName;
        IniFile&				mIniFile;
        IniFileProperties	    mProperties;
        APTMotor*			    mXMotor;
        APTMotor*			    mYMotor;
        APTMotor*			    mZMotor;
        JoyStick*               mJoyStick;
        XYZUnitPositions		mPositions;
};
#endif
