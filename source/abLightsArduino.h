#ifndef abLightsArduinoH
#define abLightsArduinoH
#include "abExporter.h"
#include "abArduinoDevice.h"
//---------------------------------------------------------------------------

class AB_CORE LightsArduino : public ArduinoDevice
{
    public:
                                LightsArduino(int portNr, int baudRate = 9600);
                                ~LightsArduino(){}

    protected:

};
#endif
