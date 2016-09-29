#ifndef abXYZUnitH
#define abXYZUnitH
#include "abExporter.h"
#include "abABObject.h"
#include "abUtilities.h"
#include "apt/abDeviceManager.h"
#include "mtkProperties.h"
#include "mtkINIFileProperties.h"
#include "mtkINIFile.h"
//#include "abPositions.h"
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
    					                XYZUnit(const string& name, IniFile& iniFile, const string& appDataFolder);
    					                ~XYZUnit();

		bool					        isActive();

		bool					        enableJSAxes();
		bool					        disableJSAxes();

		bool					        enableZButtons();
		bool					        disableZButtons();

        void					        attachJoyStick(ArrayBotJoyStick* js);
        void					        detachJoyStick();

		void					        home();
		void					        stow();

		void				            shutDown();
		string					        getName() const;
  //      Positions&				        positions(){return mPositions;}

		virtual bool	  	            initialize();
        virtual bool	  		        stopAll();
        virtual vector<APTMotor*>	    getAllMotors();

		APTMotor*			            getXMotor() const;
		APTMotor*			            getYMotor() const;
		APTMotor*			            getZMotor() const;
        APTMotor*				        getAngleMotor() const;
        APTMotor*				        getMotorWithName(const string& name);
        APTMotor*				        getMotorWithSerial(const string& ser);

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
//        Positions				        mPositions;
};
#endif
