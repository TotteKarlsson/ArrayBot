#ifndef abPufferArduinoH
#define abPufferArduinoH
#include "abArduinoDevice.h"
#include "abLeicaUC7Controller.h"
//---------------------------------------------------------------------------

//!The puffer arduino class expose a simple interface to control the puffer arduino.
class AB_CORE PufferArduino : public ArduinoDevice
{
    public:
                                PufferArduino(int portNr, int baudRate = 9600);
                                ~PufferArduino(){}

        bool					enablePuffer();
        bool					disablePuffer();

        						//!Enable/disable vaccum
        bool					activateVaccum();
        bool					deActivateVaccum();

		bool					manualPuff();

        bool					setPufferDuration(int ms);
        bool					setPufferValveSpeed(int n);

		bool					setCutThicknessPreset(int preset);

        int						getLastCutThicknessPreset();
		bool					setDeltaY(int dy);
		bool 					getStatus();

		bool					enableDisableSimulator(bool flag);
        bool					setSimulatorSpeed(int ms);

    protected:
    	LeicaUC7Controller		mTheLeica;
};
#endif
