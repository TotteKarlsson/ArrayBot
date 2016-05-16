#ifndef abArrayBotH
#define abArrayBotH
#include "abExporter.h"
#include "abABObject.h"
#include "abXYZUnit.h"
#include "abJoyStick.h"
//---------------------------------------------------------------------------

struct CombinedMoveParameters
{

};

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

    private:
        IniFile&					mIniFile;
    	CombinedMoveParameters		mCSLift;
        XYZUnit						mCoverSlip;
        XYZUnit						mWhisker;
        JoyStick					mJoyStick;
};

#endif
