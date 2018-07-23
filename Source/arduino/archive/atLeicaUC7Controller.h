#ifndef atLeicaUC7ControllerH
#define atLeicaUC7ControllerH
#include "atCoreExporter.h"
#include "atATObject.h"
//---------------------------------------------------------------------------

//!The LeicaUC7 controller gives a client the possibility to execute actions on the UC7's
//UI. This is done internally in the 'Leica Arduino' by automating the mouse on the UC7.

class PufferArduino;
class AT_ARDUINO LeicaUC7Controller : public ATObject
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
