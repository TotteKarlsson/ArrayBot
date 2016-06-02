#ifndef abArrayBotH
#define abArrayBotH
#include "abExporter.h"
#include "abABObject.h"
#include "abXYZUnit.h"
#include "abJoyStick.h"
#include "abAngleController.h"
#include "abCombinedMove.h"
#include "abJoyStickSettings.h"
#include "abJoyStickMessageDispatcher.h"
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
        JoyStick&					getJoyStick();
        JoyStickSettings&			getJoyStickSettings(){return mJSSettings;}

		void						enableJoyStick();
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

    private:
        IniFile&					mIniFile;
        bool						mIsShuttingDown;

        XYZUnit						mCoverSlip;
        XYZUnit						mWhisker;

        AngleController				mCoverSlipAngleController;

        AngleController				mCameraAngleController;
		CombinedMove				mCSLift;

        JoyStick					mJoyStick;
        JoyStickSettings			mJSSettings;

        							//Todo: Make this prettier later
		JoyStickMessageDispatcher 	mJS;

									//!Moving joystick axes
        void 				        onX1AxisMove(int pos);
        void 				        onY1AxisMove(int pos);

        void 				        onX2AxisMove(int pos);
        void 				        onY2AxisMove(int pos);




};

#endif
