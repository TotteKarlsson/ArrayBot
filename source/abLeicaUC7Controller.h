#ifndef abLeicaUC7ControllerH
#define abLeicaUC7ControllerH
#include "abExporter.h"
#include "abABObject.h"
//---------------------------------------------------------------------------

class PufferArduino;
class AB_CORE LeicaUC7Controller : public ABObject
{
    public:
                                LeicaUC7Controller(PufferArduino& p);
                                ~LeicaUC7Controller(){}
		bool					setCutThicknessPreset(int cutPreset);
		int 					getLastSetCutThicknessPreset(){return mLastSetCutThicknessPreset;}

		bool					setDeltaY(int dy);

    protected:
    	PufferArduino&			mPufferArduino;

                                //!Use the last CutThicknessPresetRequest
                                //!to know wether to increment the section counter or not
                                //!If mLastCutThicknessPresetRequest == 1, then the
                                //!counter is not incremented
        int						mLastSetCutThicknessPreset;
};
#endif
