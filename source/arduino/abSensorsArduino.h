#ifndef abSensorsArduinoH
#define abSensorsArduinoH
#include "abExporter.h"
#include "abArduinoDevice.h"
//---------------------------------------------------------------------------

class AB_CORE SensorsArduino : public ArduinoDevice
{
    public:
                                			SensorsArduino(int portNr, int baudRate = 9600);
			                                ~SensorsArduino(){}
        bool								getStatus();


    protected:


};
#endif
