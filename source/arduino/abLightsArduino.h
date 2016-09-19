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

		bool								toggleLED();
        bool								turnLEDLightsOn();
        bool								turnLEDLightsOff();

		bool								toggleCoax();
        bool								turnCoaxLightOn();
        bool								turnCoaxLightOff();

        bool								getStatus();


    protected:
        									//!ArduinoLines
		int 								mLEDLightONLine;
		int									mLEDLightOFFLine;

		int 								mCoaxLightONLine;
		int									mCoaxLightOFFLine;


};
#endif
