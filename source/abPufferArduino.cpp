#pragma hdrstop
#include "abPufferArduino.h"
#include <sstream>
#include "mtkLogger.h";
//---------------------------------------------------------------------------

using namespace mtk;
using namespace std;

PufferArduino::PufferArduino(int portNr, int baudRate)
:
ArduinoDevice(portNr, baudRate),
mTheLeica(*this)
{}

bool PufferArduino::setCutPreset(int preset)
{
  	return mTheLeica.setCutPreset(preset);
}

bool PufferArduino::setDeltaY(int dy)
{
  	return mTheLeica.setDeltaY(dy);
}

bool PufferArduino::manualPuff()
{
	Log(lInfo) << "Sending puff command";
    bool res = send("p");
	return res;
}

bool PufferArduino::enablePuffer()
{
	Log(lInfo) << "Sending puffer enable request";
	return send("e");
}

bool PufferArduino::disablePuffer()
{
	return false;
}

bool PufferArduino::enableDisableSimulator(bool flag)
{
    mSS.str("");
	mSS << "S" << flag;
	return send(mSS.str());
}

bool PufferArduino::setSimualorSpeed(int ms)
{
    mSS.str("");
	mSS << "s"<<ms;
	return send(mSS.str());

}
