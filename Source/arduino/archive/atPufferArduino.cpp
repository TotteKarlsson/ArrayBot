#pragma hdrstop
#include "atPufferArduino.h"
#include <sstream>
#include "dslLogger.h";
//---------------------------------------------------------------------------

using namespace dsl;
using namespace std;

PufferArduino::PufferArduino(int portNr, int baudRate)
:
ArduinoDevice(portNr, baudRate),
mTheLeica(*this)
{}

bool PufferArduino::setCutThicknessPreset(int preset)
{
  	return mTheLeica.setCutThicknessPreset(preset);
}

int	PufferArduino::getLastCutThicknessPreset()
{
	return mTheLeica.getLastSetCutThicknessPreset();
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

bool PufferArduino::setPufferDuration(int ms)
{
	Log(lInfo) << "Setting puffer duration";
    mSS.str("");
	mSS << "d" << ms;
    return  send(mSS.str());
}

bool PufferArduino::setPufferValveSpeed(int n)
{
	Log(lInfo) << "Setting puffer valve speed";
    mSS.str("");
	mSS << "v" << n;
    return  send(mSS.str());
}

bool PufferArduino::enablePuffer()
{
	Log(lInfo) << "Sending puffer enable request";
	return send("e");
}

bool PufferArduino::disablePuffer()
{
	Log(lInfo) << "Sending puffer disable request";
	return send("a");
}

bool PufferArduino::enableDisableSimulator(bool flag)
{
    mSS.str("");
	mSS << "S" << flag;
	return send(mSS.str());
}

bool PufferArduino::setSimulatorSpeed(int ms)
{
    mSS.str("");
	mSS << "s"<<ms;
	return send(mSS.str());
}

bool PufferArduino::getStatus()
{
	Log(lInfo) << "Requesting puffer arduino status";
	return send("i");
}
