#ifndef abArrayBotH
#define abArrayBotH
#include "abExporter.h"
#include "abABObject.h"
#include "abXYZUnit.h"
#include "abArrayBotJoyStick.h"
#include "abPairedMoves.h"
#include "abJoyStickSettings.h"
//---------------------------------------------------------------------------

class AB_CORE ArrayBot : public ABObject
{
    public:
									                    ArrayBot(IniFile& ini, const string& appFolder);
									                    ~ArrayBot();

		void 						                    initialize();

        XYZUnit&					                    getCoverSlipUnit();
        XYZUnit&					                    getWhiskerUnit();
        bool						                    shutDown();

        ArrayBotJoyStick&			                    getJoyStick();
        JoyStickSettings&			                    getJoyStickSettings();

		bool						                    enableJoyStick();
		void						                    disableJoyStick();
        void						                    stopAll();

        void						                    initWorkingPosition();

        void						                    stow();
        void						                    home();
        bool						                    isActive();
        bool						                    isShuttingDown();

		APTMotor*					                    getCoverSlipAngleController();
		APTMotor*					                    getCameraAngleController();

    	PairedMoves&	 			                    getLiftMoves(){return mLifts;}

        bool						                    applyJoyStickSetting(const string& settingName);
        bool						                    readINIParameters();
        bool						                    writeINIParameters();
        vector<APTMotor*>			                    getAllMotors();

    private:
        bool						                    mIsShuttingDown;
        string						                    mAppDataFolder;
        IniFile&					                    mIniFile;
        ArrayBotJoyStick			                    mJoyStick;
        JoyStickSettings			                    mJSSettings;

        XYZUnit						                    mCoverSlip;
        XYZUnit						                    mWhisker;

        							                    //!List of Lifts
        PairedMoves					                    mLifts;
};

#endif
