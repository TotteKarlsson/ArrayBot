#ifndef atXYZUnitH
#define atXYZUnitH
#include "arraybot/atABExporter.h"
#include "atATObject.h"
#include "atUtils.h"
#include "apt/atDeviceManager.h"
#include "dslProperties.h"
#include "dslINIFileProperties.h"
#include "dslINIFile.h"
//#include "atPositions.h"
//---------------------------------------------------------------------------

using dsl::IniFileProperties;
using dsl::Property;
using dsl::IniFile;
using at::DeviceManager;

namespace at
{
    class APTMotor;
    class ArrayBotJoyStick;
    class MoveSequencer;
    class AT_AB XYZUnit : public ATObject
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
}
#endif
