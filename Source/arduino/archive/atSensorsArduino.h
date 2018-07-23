#ifndef atSensorsArduinoH
#define atSensorsArduinoH
#include "atCoreExporter.h"
#include "atArduinoDevice.h"
//---------------------------------------------------------------------------

class AT_ARDUINO SensorsArduino : public ArduinoDevice
{
    public:
                                			SensorsArduino(int portNr, int baudRate = 9600);
			                                ~SensorsArduino(){}
        bool								getStatus();


    protected:


};
#endif
