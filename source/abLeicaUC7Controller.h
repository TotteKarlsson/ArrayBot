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
		bool					setCutPreset(int cutPreset);

    protected:
    	PufferArduino&			mPufferArduino;
};
#endif
