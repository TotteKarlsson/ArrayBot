#ifndef abArrayBotH
#define abArrayBotH
#include "abExporter.h"
#include "abABObject.h"
#include "abXYZUnit.h"
#include "abArrayBotJoyStick.h"
#include "abAngleController.h"
#include "abCombinedMove.h"
#include "abJoyStickSettings.h"
//---------------------------------------------------------------------------

class AB_CORE ArrayBot : public ABObject
{
    public:
									ArrayBot(IniFile& ini);
									~ArrayBot();
		void 						initialize();

        XYZUnit&					getCoverSlipUnit();
        XYZUnit&					getWhiskerUnit();
        bool						shutDown();

        ArrayBotJoyStick&			getJoyStick();
        JoyStickSettings&			getJoyStickSettings();

		bool						enableJoyStick();
		void						disableJoyStick();
        void						stopAll();

        void						initWorkingPosition();

        void						stow();
        void						home();
        bool						isActive();
        bool						isShuttingDown();

		AngleController&			getCoverSlipAngleController();
		AngleController&			getCameraAngleController();

    	CombinedMove&				getCombinedMove(){return mCSLift;}
        bool						applyJoyStickSetting(const string& settingName);
        bool						readINIParameters();
        bool						writeINIParameters();

    private:
        bool						mIsShuttingDown;
        IniFile&					mIniFile;

        ArrayBotJoyStick			mJoyStick;
        JoyStickSettings			mJSSettings;

        XYZUnit						mCoverSlip;
        XYZUnit						mWhisker;

        AngleController				mCoverSlipAngleController;

        AngleController				mCameraAngleController;
		CombinedMove				mCSLift;
};

#endif
