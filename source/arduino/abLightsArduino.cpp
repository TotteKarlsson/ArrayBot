#pragma hdrstop
#include "abLightsArduino.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------
using namespace mtk;


LightsArduino::LightsArduino(int portNr, int baudRate)
:
ArduinoDevice(portNr, baudRate),
mLEDLightONLine(3),
mLEDLightOFFLine(4),
mCoaxLightONLine(1),
mCoaxLightOFFLine(2)
{}

bool LightsArduino::turnLEDLightsOn()
{
	Log(lInfo) << "Turning on LEDs";
	return send(mLEDLightONLine);
}

bool LightsArduino::turnLEDLightsOff()
{
	Log(lInfo) << "Turning off LEDs";
	return send(mLEDLightOFFLine);
}

bool LightsArduino::turnCoaxLightOn()
{
	Log(lInfo) << "Turning on Coax light";
	return send(mCoaxLightONLine);
}

bool LightsArduino::turnCoaxLightOff()
{
	Log(lInfo) << "Turning off Coax light";
	return send(mCoaxLightOFFLine);
}

bool LightsArduino::toggleLED()
{
	static bool switcher(false);
    switcher = !switcher;
    return (switcher) ? send(mLEDLightONLine) :	send(mLEDLightOFFLine);
}

bool LightsArduino::toggleCoax()
{
	static bool switcher(false);
    switcher = !switcher;
    return (switcher) ? send(mCoaxLightONLine) : send(mCoaxLightOFFLine);
}

bool LightsArduino::getStatus()
{
	Log(lInfo) << "Requesting sensor arduino status";
	return send("i");
}
