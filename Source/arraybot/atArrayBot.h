#ifndef atArrayBotH
#define atArrayBotH
#include "arraybot/atABExporter.h"
#include "atATObject.h"
#include "atXYZUnit.h"
#include "joystick/atArrayBotJoyStick.h"
#include "apt/atPairedMoves.h"
#include "joystick/atJoyStickSettings.h"
#include "process/atProcessSequencer.h"
//---------------------------------------------------------------------------

namespace at
{
    class ArduinoClient;
    //class ArrayBotServer;
    class AT_AB ArrayBot : public ATObject
    {
        public:
    									                    ArrayBot(IniFile& ini, const string& appFolder);
    									                    ~ArrayBot();

    		void 						                    initialize();
            bool						                    applyJoyStickSetting(const string& settingName);
            bool						                    readINIParameters();
            bool						                    writeINIParameters();

    		bool											enableCoverSlipUnit();
    		bool											disableCoverSlipUnit();
    		bool											enableWhiskerUnit();
    		bool											disableWhiskerUnit();

            XYZUnit&					                    getCoverSlipUnit();
            XYZUnit&					                    getWhiskerUnit();
            bool						                    shutDown();

            ArrayBotJoyStick&			                    getJoyStick();
            JoyStickSettings&			                    getJoyStickSettings();

    		bool						                    enableJoyStick();
    		void						                    disableJoyStick();

            												//!Allow buttons to work, while the axes don't
            void											enableJoyStickAxes();
            void											disableJoyStickAxes();

            void						                    stopAll();
            void											homeAll();

            bool						                    isActive();
            bool						                    isShuttingDown();

    		APTMotor*					                    getCoverSlipAngleController();
    		APTMotor*					                    getCameraAngleController();

        	PairedMoves&	 			                    getLiftMoves(){return mLifts;}
            vector<APTMotor*>			                    getAllMotors();
            APTMotor*										getMotorWithName(const string& name);
            APTMotor*										getMotorWithSerial(const string& serial);

        private:
            bool						                    mIsShuttingDown;
            string						                    mAppDataFolder;
            IniFile&					                    mIniFile;
            IniFileProperties  			    				mProperties;
            Property<int>									mJoyStickID;
    		Property<double>								mRightJoyStickXLeftDeadZone;
            Property<double>                                mRightJoyStickXRightDeadZone;
            Property<double>                                mRightJoyStickYLeftDeadZone;
            Property<double>                                mRightJoyStickYRightDeadZone;
            Property<double>                                mLeftJoyStickXLeftDeadZone;
            Property<double>                                mLeftJoyStickXRightDeadZone;
            Property<double>                                mLeftJoyStickYLeftDeadZone;
            Property<double>                                mLeftJoyStickYRightDeadZone;

            ArrayBotJoyStick			                    mJoyStick;
            JoyStickSettings			                    mJSSettings;

            XYZUnit						                    mCoverSlip;
            XYZUnit											mWhisker;

            							                    //!List of Lifts
            PairedMoves					                    mLifts;
    //        ArrayBotServer									mServer;

    };
}

#endif
