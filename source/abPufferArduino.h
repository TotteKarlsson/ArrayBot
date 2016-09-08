#ifndef abPufferArduinoH
#define abPufferArduinoH
#include "abExporter.h"
#include "abArduinoDevice.h"
#include "abLeicaUC7Controller.h"
//---------------------------------------------------------------------------

class AB_CORE PufferArduino : public ArduinoDevice
{
    public:
                                PufferArduino(int portNr, int baudRate = 9600);
                                ~PufferArduino(){}
		bool					setCutPreset(int preset);

    protected:
    	LeicaUC7Controller		mTheLeica;


};
#endif
