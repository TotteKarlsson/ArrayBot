#ifndef abArrayBotH
#define abArrayBotH
#include "abExporter.h"
#include "abABObject.h"
#include "abXYZUnit.h"
#include "abWhiskerUnit.h"
#include "joystick/abArrayBotJoyStick.h"
#include "abPairedMoves.h"
#include "joystick/abJoyStickSettings.h"
#include "abProcessSequencer.h"
//---------------------------------------------------------------------------

class ArduinoClient;
class AB_CORE ArrayBot : public ABObject
{
    public:
									                    ArrayBot(IniFile& ini, const string& appFolder);
									                    ~ArrayBot();

		void 						                    initialize();

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

        void											enableJoyStickAxes();
        void											disableJoyStickAxes();

        void						                    stopAll();

        void						                    initWorkingPosition();

        bool						                    isActive();
        bool						                    isShuttingDown();

		APTMotor*					                    getCoverSlipAngleController();
		APTMotor*					                    getCameraAngleController();

    	PairedMoves&	 			                    getLiftMoves(){return mLifts;}

        bool						                    applyJoyStickSetting(const string& settingName);
        bool						                    readINIParameters();
        bool						                    writeINIParameters();
        vector<APTMotor*>			                    getAllMotors();
        APTMotor*										getMotorWithName(const string& mn);
        APTMotor*										getMotorWithSerial(const string& serial);
        ProcessSequencer&								getProcessSequencer();

        void											setArduinoClient(ArduinoClient* c){mArduinoClient = c;}
        ArduinoClient*									getArduinoClient(){return mArduinoClient;}

    private:
        bool						                    mIsShuttingDown;
        string						                    mAppDataFolder;
        IniFile&					                    mIniFile;
        IniFileProperties  			    				mProperties;

        ArduinoClient*									mArduinoClient;
        Property<int>									mJoyStickID;
        ArrayBotJoyStick			                    mJoyStick;

        JoyStickSettings			                    mJSSettings;

        XYZUnit						                    mCoverSlip;
        WhiskerUnit		 			                    mWhisker;

        							                    //!List of Lifts
        PairedMoves					                    mLifts;
   	    ProcessSequencer  								mProcessSequencer;
};

#endif
