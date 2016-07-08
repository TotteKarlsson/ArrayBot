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
    					                XYZUnit(const string& name, IniFile& iniFile, const string& appFolder);
    					                ~XYZUnit();
        vector<APTMotor*>		        getAllMotors();
		bool					        isActive();

		bool					        enableJSAxes();
		bool					        disableJSAxes();
        void					        attachJoyStick(ArrayBotJoyStick* js);
        void					        detachJoyStick();

		void					        home();
		void					        stow();

		void				            shutDown();
		string					        getName() const;
        Positions&				        positions(){return mPositions;}

		bool				            initialize();
        bool					        stopAll();

		APTMotor*			            getXMotor() const;
		APTMotor*			            getYMotor() const;
		APTMotor*			            getZMotor() const;
        APTMotor*				        getAngleMotor() const;
        APTMotor*				        getMotorWithName(const string& name);

        Property<int>		            mXMotorSerialNr;
        Property<int>		            mYMotorSerialNr;
        Property<int>		            mZMotorSerialNr;
	    Property<int>		            mAngleMotorSerialNr;

        						        //TODO: move the devicemanager to ArrayBot and
                                        //use a reference for each class that needs to use it
    	DeviceManager	                mDeviceManager;


	protected:
		string					        mName;

        						        //!App datafolder is where sequence files are saved
        string					        mAppDataFolder;
        IniFile&				        mIniFile;
        IniFileProperties	            mProperties;

        						        //!XYZ stages
        APTMotor*			            mXMotor;
        APTMotor*			            mYMotor;
        APTMotor*			            mZMotor;

        						        //!Angle controller
        APTMotor*			            mAngleMotor;

        ArrayBotJoyStick*               mJoyStick;
        Positions				        mPositions;
//        ProcessSequencer 		        mProcessSequencer;
};
#endif
