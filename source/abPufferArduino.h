#ifndef abPufferArduinoH
#define abPufferArduinoH
#include "abExporter.h"
#include "abArduinoDevice.h"
//---------------------------------------------------------------------------

class AB_CORE PufferArduino : public ArduinoDevice
{
    public:
                                PufferArduino(int portNr, int baudRate = 9600);
                                ~PufferArduino(){}

    protected:

};
#endif
