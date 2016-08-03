#ifndef abArrayBotH
#define abArrayBotH
#include "abExporter.h"
#include "abABObject.h"
#include "abXYZUnit.h"
#include "abArrayBotJoyStick.h"
#include "abPairedMoves.h"
#include "abJoyStickSettings.h"
#include "abProcessSequencer.h"
//---------------------------------------------------------------------------

class AB_CORE ArrayBot : public ABObject
{
    public:
									                    ArrayBot(IniFile& ini, const string& appFolder);
									                    ~ArrayBot();

		void 						                    initialize();
		bool 						                    switchJoyStick();

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
        ProcessSequencer&								getProcessSequencer();


    private:
        bool						                    mIsShuttingDown;
        string						                    mAppDataFolder;
        IniFile&					                    mIniFile;
        IniFileProperties  			    				mProperties;
        ArrayBotJoyStick			                    mJoyStick;
        Property<int>									mJoyStickID;

        JoyStickSettings			                    mJSSettings;

        XYZUnit						                    mCoverSlip;
        XYZUnit						                    mWhisker;

        							                    //!List of Lifts
        PairedMoves					                    mLifts;
   	    ProcessSequencer  								mProcessSequencer;
};

#endif
