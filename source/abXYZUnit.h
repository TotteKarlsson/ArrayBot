#ifndef abXYZUnitH
#define abXYZUnitH
#include "abExporter.h"
#include "abABObject.h"
#include "abUtilities.h"
#include "abDeviceManager.h"
#include "mtkProperties.h"
#include "mtkINIFileProperties.h"
#include "mtkINIFile.h"
#include "abPositions.h"
#include "abMoveSequencer.h"
//---------------------------------------------------------------------------

class APTMotor;
class JoyStick;
class MoveSequencer;
using mtk::IniFileProperties;
using mtk::Property;
using mtk::IniFile;

class AB_CORE XYZUnit : public ABObject
{
	public:
    					        XYZUnit(const string& name, IniFile& iniFile);
    					        ~XYZUnit();
		bool					isActive();

		void					home();
		void					stow();

		void				    shutDown();
		string					getName();
        Positions&				positions(){return mPositions;}
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

        						//!Move absolute moves to pos, regardless of
                                //current position
        bool					moveAbsolute(const ab::Position& pos);
        bool					moveRelative(const ab::Position& pos);

	protected:
		string					mName;
        IniFile&				mIniFile;
        IniFileProperties	    mProperties;
        APTMotor*			    mXMotor;
        APTMotor*			    mYMotor;
        APTMotor*			    mZMotor;
        JoyStick*               mJoyStick;
        Positions				mPositions;
        MoveSequencer			mMoveSequencer;
};
#endif
