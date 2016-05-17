#ifndef abArrayBotH
#define abArrayBotH
#include "abExporter.h"
#include "abABObject.h"
#include "abXYZUnit.h"
#include "abJoyStick.h"
#include "abCoverSlipAngleController.h"
#include "abCombinedMove.h"
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
        void						assignWindowHandle(int Handle);
		void						enableWhiskerJoyStick();
		void						enableCoverSlipJoyStick();
		void						disableJoyStick();
        void						stopAll();
        void						initWorkingPosition();
        void						stow();
        void						home();
        bool						isActive();
        bool						isShuttingDown();
		CoverSlipAngleController&	getAngleController();
    	CombinedMove&				getCombinedMove(){return mCSLift;}

    private:
        IniFile&					mIniFile;
        bool						mIsShuttingDown;
    	CombinedMove				mCSLift;
        XYZUnit						mCoverSlip;
        XYZUnit						mWhisker;
        CoverSlipAngleController	mCSAngleController;
        JoyStick					mJoyStick;
};

#endif
