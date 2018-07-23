#ifndef atLightsArduinoH
#define atLightsArduinoH
#include "atCoreExporter.h"
#include "atArduinoDevice.h"
//---------------------------------------------------------------------------

namespace at
{
    class AT_ARDUINO LightsArduino : public ArduinoDevice
    {
        public:
                                    			LightsArduino(int portNr, int baudRate = 9600);
    			                                ~LightsArduino(){}

    		bool								toggleLED();
            bool								turnLEDLightsOn();
            bool								turnLEDLightsOff();
            bool								setLEDDrive(int drive);
            bool								getStatus();

        protected:
            									//!ArduinoLines
    		int 								mLEDLightONLine;
    		int									mLEDLightOFFLine;

    };
}
#endif
