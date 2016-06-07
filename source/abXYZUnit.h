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
#include "abProcessSequencer.h"
//---------------------------------------------------------------------------

class APTMotor;
class ArrayBotJoyStick;
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
        void					attachJoyStick(ArrayBotJoyStick* js);
        void					detachJoyStick();

		bool				    initialize();
        bool					stopAll();

		APTMotor*			    getXMotor();
		APTMotor*			    getYMotor();
		APTMotor*			    getZMotor();

        Property<int>		    mXMotorSerialNr;
        Property<int>		    mYMotorSerialNr;
        Property<int>		    mZMotorSerialNr;

        						//TODO: move the devicemanager to ArrayBot and
                                //use a reference for each class that needs to use it
    	DeviceManager	        mDeviceManager;

        						//!Move absolute moves to pos, regardless of
                                //current position
        bool					moveAbsolute(const ab::Position& pos);
        bool					moveRelative(const ab::Position& pos);

	protected:
		string					mName;
        IniFile&				mIniFile;
        IniFileProperties	    mProperties;

        						//!XYZ stages
        APTMotor*			    mXMotor;
        APTMotor*			    mYMotor;
        APTMotor*			    mZMotor;

        ArrayBotJoyStick*       mJoyStick;
        Positions				mPositions;
        ProcessSequencer 		mMoveSequencer;
};
#endif
