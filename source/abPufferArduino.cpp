#pragma hdrstop
#include "abPufferArduino.h"
#include <sstream>
//---------------------------------------------------------------------------

using namespace std;
PufferArduino::PufferArduino(int portNr, int baudRate)
:
ArduinoDevice(portNr, baudRate),
mTheLeica(*this)
{

}

bool PufferArduino::setCutPreset(int preset)
{
  	return mTheLeica.setCutPreset(preset);
}
