#ifndef abArrayBotH
#define abArrayBotH
#include "abExporter.h"
#include "abABObject.h"
#include "abXYZUnit.h"
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

    private:
        IniFile&					mIniFile;
    	CombinedMoveParameters		mCSLift;
        XYZUnit						mCoverSlip;
        XYZUnit						mWhisker;



};

#endif
